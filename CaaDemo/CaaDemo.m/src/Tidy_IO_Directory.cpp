
#include "Tidy_IO_Directory.h"
#ifdef _MSC_VER
#include "windows.h"
#include <shlobj.h>
#include <direct.h>
#include <io.h>
#endif

#include <stdio.h>
#include "Tidy_IO_File.h"
#include "Tidy_IO_Path.h"
#include "Tidy_IO_DirectoryInfo.h"
#include "Tidy_DateTime.h"
#include "Tidy_ID.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

using namespace Tidy;
using namespace IO;

DirectoryInfo Directory::GetParent(LocaleString path)
{
	size_t found = path.Target.find_last_of('/');
	if (found != std::string::npos)
	{
		std::string parentPath = path.Target.substr(0, found);
		return DirectoryInfo(parentPath);
	}
	return DirectoryInfo("");
}
#undef CreateDirectory
DirectoryInfo Directory::CreateDirectory(LocaleString path)
{
	if (CreateDirectoryA(path.Target.c_str(), NULL) != 0)
	{
		return DirectoryInfo(path.Target);
	}
	return DirectoryInfo("");
}

LocaleString IO::Directory::TryCreateDirectory(LocaleString path)
{
	LocaleString parent = Path::GetDirectoryName(path);
	if (!Exists(parent)) {
		TryCreateDirectory(parent);
	}
	if (!Exists(path)) {
		CreateDirectory(path);
	}
	return path;
}

bool Directory::Exists(LocaleString path)
{
	DWORD attributes = GetFileAttributesA(path.Target.c_str());
	return (attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_DIRECTORY));
}

FILETIME _DateTimeToFileTime(DateTime value)
{
	ULARGE_INTEGER uli;
#if NOTSUPPORT_CHRONO
    uli.QuadPart = static_cast<ULONGLONG>(value.Target)*1000*1000*10 + 116444736000000000ULL; // 100 ns intervals from 1/1/1601 to 1/1/1970
#else
	uli.QuadPart = static_cast<ULONGLONG>(value.Target.time_since_epoch().count()) + 116444736000000000ULL; // 100 ns intervals from 1/1/1601 to 1/1/1970
#endif
	FILETIME ft;
	ft.dwLowDateTime = uli.LowPart;
	ft.dwHighDateTime = uli.HighPart;
	return ft;
}

void Directory::SetCreationTime(LocaleString path, DateTime creationTime)
{
	HANDLE hFile = CreateFileA(path.Target.c_str(), FILE_WRITE_ATTRIBUTES, 0, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		FILETIME ftCreationTime = _DateTimeToFileTime(creationTime);
		SetFileTime(hFile, &ftCreationTime, NULL, NULL);
		CloseHandle(hFile);
	}
}

DateTime Directory::GetCreationTime(LocaleString path)
{
	HANDLE hFile = CreateFileA(path.Target.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	DateTime creationTime;
	if (hFile != INVALID_HANDLE_VALUE)
	{
		FILETIME ftCreationTime;
		GetFileTime(hFile, &ftCreationTime, NULL, NULL);
		ULARGE_INTEGER uli;
		uli.LowPart = ftCreationTime.dwLowDateTime;
		uli.HighPart = ftCreationTime.dwHighDateTime;
        #if NOTSUPPORT_CHRONO
            creationTime.Target = (long long)((uli.QuadPart - 116444736000000000ULL)/10000000); // 100 ns intervals from 1/1/1601 to 1/1/1970
        #else
            creationTime.Target = std::chrono::system_clock::time_point(std::chrono::duration<long long, std::ratio<1, 10000000>>(uli.QuadPart - 116444736000000000ULL)); // 100 ns intervals from 1/1/1601 to 1/1/1970
        #endif
		
		CloseHandle(hFile);
	}
	return creationTime;
}

std::vector<LocaleString> Directory::GetFiles(LocaleString path)
{
	std::vector<LocaleString> files;
	WIN32_FIND_DATAA fd;
	HANDLE hFind = FindFirstFileA((path.Target + "\\*").c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
			{
				files.push_back(path.Target + "\\" + fd.cFileName);
			}
		} while (FindNextFileA(hFind, &fd));
		FindClose(hFind);
	}
	return files;
}

std::vector<LocaleString> Directory::GetDirectories(LocaleString path)
{
	std::vector<LocaleString> directories;
	WIN32_FIND_DATAA fd;
	HANDLE hFind = FindFirstFileA((path.Target + "\\*").c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && (strcmp(fd.cFileName, ".") != 0) && (strcmp(fd.cFileName, "..") != 0))
			{
				directories.push_back(path.Target + "\\" + fd.cFileName);
			}
		} while (FindNextFileA(hFind, &fd));
		FindClose(hFind);
	}
	return directories;
}

void Directory::Move(LocaleString sourceDirName, LocaleString destDirName)
{
	MoveFileExA(sourceDirName.Target.c_str(), destDirName.Target.c_str(), MOVEFILE_REPLACE_EXISTING);
}

void Directory::Move(LocaleString sourceDirName, LocaleString destDirName, bool recursive)
{
	MoveFileExA(sourceDirName.Target.c_str(), destDirName.Target.c_str(), MOVEFILE_REPLACE_EXISTING);

	if (recursive)
	{
		std::vector<LocaleString> files = GetFiles(sourceDirName);
        for(size_t i = 0; i < files.size(); i++)
        {
            MoveFileExA(files[i].Target.c_str(), (destDirName + "\\" + Path::GetFileName(files[i])).Target.c_str(), MOVEFILE_REPLACE_EXISTING);
        }
		std::vector<LocaleString> directories = GetDirectories(sourceDirName);
        for(size_t i = 0; i < directories.size(); i++){
            Move(directories[i], destDirName + "\\" + Path::GetFileName(directories[i]), true);
        }
	}

	
}

void Directory::Delete(LocaleString path, bool recursive)
{
	if (recursive)
	{
		std::vector<LocaleString> files = GetFiles(path);
        for(size_t i = 0; i < files.size(); i++)
        {
            DeleteFileA(files[i].Target.c_str());
        }

		std::vector<LocaleString> directories = GetDirectories(path);
        for(size_t i = 0; i < directories.size(); i++)
        {
            Delete(directories[i], recursive);
        }
	}

	RemoveDirectoryA(path.Target.c_str());
}

LocaleString Directory::GetDocumentDirectory()
{
#ifdef _MSC_VER
#if _MSC_VER <= 1800
    return Path::Combine(GetUserProfileDirectory(), "Documents");
#else
    PWSTR myDocsPath = SUPPORT_NULLPTR;
	if (SHGetKnownFolderPath(FOLDERID_Documents, 0, SUPPORT_NULLPTR, &myDocsPath) == S_OK) {
		std::wstring result(myDocsPath);
		CoTaskMemFree(myDocsPath);
		return result;
	}
	else {
		return "";
	}
#endif
	
#endif
	return "";
}

LocaleString Directory::GetUserProfileDirectory()
{
#ifdef _MSC_VER
	char* documentPath = SUPPORT_NULLPTR;
	if (_dupenv_s(&documentPath, SUPPORT_NULLPTR, "USERPROFILE") == 0 && documentPath != SUPPORT_NULLPTR) {
		std::string path = documentPath;
		free(documentPath);
		return path;
	}
#endif
	return "";
}

LocaleString Directory::GetProgramFilesDirectory(int platform)
{
#ifdef _MSC_VER
	char programFilesPath[MAX_PATH];
	if (platform == 32 || platform == 86) {
		if (SHGetFolderPathA(NULL, CSIDL_PROGRAM_FILESX86, NULL, 0, programFilesPath) == S_OK) {
			return programFilesPath;
		}
		else {
			return "";
		}
	}
	else if (platform == 64) {
		if (SHGetFolderPathA(NULL, CSIDL_PROGRAM_FILES, NULL, 0, programFilesPath) == S_OK) {
			return programFilesPath;
		}
		else {
			return "";
		}
	}
	else{
		return "";
	}
#else
	return "";
#endif
}

LocaleString Directory::GetProgramDataDirectory()
{
#ifdef _MSC_VER
	char programDataPath[MAX_PATH];
	if (SHGetFolderPathA(NULL, CSIDL_COMMON_APPDATA, NULL, 0, programDataPath) == S_OK) {
		return programDataPath;
	}
	else {
		return "";
	}
#else
	return "";
#endif
}

LocaleString Directory::GetTemporaryDirectory()
{
#ifdef _MSC_VER
	char tempPath[MAX_PATH];
	DWORD result = GetTempPathA(MAX_PATH, tempPath);
	if (result > 0 && result < MAX_PATH) {
		char longTempPath[MAX_PATH];
		GetLongPathNameA(tempPath, longTempPath, MAX_PATH);
		return longTempPath;
	}
	else {
		return "";
	}
#endif // _MSC_VER
	return "";

}

LocaleString Directory::GenerateTemporaryDirectory()
{
	LocaleString result = GetTemporaryDirectory() + ID::GeneratePathName();
	CreateDirectory(result);
	return result;
}

LocaleString Directory::GetModuleDirectory()
{
	return Path::GetDirectoryName(Path::GetModulePath());
}
