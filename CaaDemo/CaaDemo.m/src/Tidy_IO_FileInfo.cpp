
#include "Tidy_IO_FileInfo.h"
#ifdef _MSC_VER
#include <windows.h>
#endif //_MSC_VER
#include <fstream>
#include <iostream>
#include <fstream>
#include "Tidy_IO_Path.h"
#include "Tidy_IO_DirectoryInfo.h"

using namespace Tidy;
using namespace IO;

#ifdef _MSC_VER
time_t FileTimeToTimeT(const FILETIME& ft)
{  
	const ULONGLONG secondsBetween1601And1970 = 11644473600ULL;
	const ULONGLONG hundredNanosInSecond = 10000000ULL;

	ULARGE_INTEGER fileTimeInteger;
	fileTimeInteger.LowPart = ft.dwLowDateTime;
	fileTimeInteger.HighPart = ft.dwHighDateTime;
     
	ULARGE_INTEGER timeTInteger;
	timeTInteger.QuadPart = (fileTimeInteger.QuadPart / hundredNanosInSecond) - secondsBetween1601And1970;

	return static_cast<time_t>(timeTInteger.QuadPart);
}
#endif

FileInfo::FileInfo()
{
	Target = "";
}

FileInfo::FileInfo(LocaleString target)
{
	Target = target;
}

LocaleString FileAttributes::ReadAttribute(LocaleString name)
{
	LocaleString result;
#ifdef _MSC_VER
	DWORD Handle;
	DWORD Size = GetFileVersionInfoSizeA((LPCSTR)Target.ToChars(), &Handle);
	if (Size == 0)return "";
	BYTE* VersionData = new BYTE[Size];
	GetFileVersionInfoA((LPCSTR)Target.ToChars(), Handle, Size, (void*)VersionData);
	UINT QuerySize;
	DWORD* TransTable;
	if (!VerQueryValueA(VersionData, "\\VarFileInfo\\Translation", (void**)&TransTable, &QuerySize))
	{
		return "";
	}
	DWORD CharSet = MAKELONG(HIWORD(TransTable[0]), LOWORD(TransTable[0]));
	char Tmp[256];
	sprintf_s(Tmp, 256, "\\StringFileInfo\\%08lx\\%s", CharSet, name.ToChars());
	LPVOID Data;
	if (!VerQueryValueA((void*)VersionData, Tmp, &Data, &QuerySize))
	{
		result = (char*)Data;
	}
	delete[] VersionData;
#endif //_MSC_VER

	return result;
}

DirectoryInfo FileInfo::Parent()
{
	return DirectoryInfo(Path::GetDirectoryName(Target));
}

LocaleString FileInfo::Name()
{
	return Path::GetFileName(Target);
}

LocaleString FileInfo::Extension()
{
	return Path::GetFileExtension(Target);
}

LocaleString FileInfo::NameWithoutExtension()
{
	return Path::GetFileNameWithoutExtension(Target);
}

int FileInfo::Size()
{
#ifdef _MSC_VER
#if _MSC_VER<=1800
	HANDLE hFile = CreateFileA(Target.ToChars(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE) {
		return 0;
	}

	LARGE_INTEGER fileSize;
	GetFileSizeEx(hFile, &fileSize);
	long long result = fileSize.QuadPart;
	CloseHandle(hFile);
	return result;
#else
	struct stat result;
	if (stat(Target.ToChars(), &result) == 0)
	{
		return  result.st_size;
	}
	else
	{
		return 0;
	}
#endif
	
	
#else
	return 0;
#endif //_MSC_VER

}

void FileInfo::ReName(LocaleString name)
{
	MoveTo(Path::ReFileName(Target,name));
}

void FileInfo::MoveTo(LocaleString destPath)
{
#ifdef _MSC_VER
	if (rename(Target.ToChars(), destPath.ToChars()) != 0)
	{
		//error
	}
#endif //_MSC_VER
}

void FileInfo::Delete()
{
#ifdef _MSC_VER
	if (remove(Target.ToChars()) != 0)
	{
		//error
	}
#endif //_MSC_VER
}

void FileInfo::CopyTo(LocaleString DestPath)
{
#ifdef _MSC_VER
	CopyFileA(Target.ToChars(), DestPath.ToChars(), false);
#endif //_MSC_VER
}

DateTime IO::FileInfo::GetLastModifiedTime()
{
#ifdef _MSC_VER
#if _MSC_VER <= 1800
	HANDLE hFile = CreateFileA(Target.ToChars(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE) {
		return 0;
	}

	FILETIME lastWriteTime;
	GetFileTime(hFile, NULL, NULL, &lastWriteTime);
	CloseHandle(hFile);
	return DateTime(FileTimeToTimeT(lastWriteTime));
#else
	struct stat result;
	if (stat(Target.ToChars(), &result) == 0)
	{
		return DateTime(result.st_mtime);
	}
	else
	{
		return 0;
	}
#endif
#else
	return 0;
#endif //_MSC_VER
}
