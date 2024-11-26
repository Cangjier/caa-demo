
#include "Tidy_IO_Path.h"
#include "Tidy_ID.h"
#include "Tidy_IO_Directory.h"
#ifdef _MSC_VER
#include "windows.h"
#include <shlobj.h>
#include <direct.h>
#include <io.h>
#endif

using namespace Tidy;
using namespace IO;

UTF8String Path::GetDirectoryName(UTF8String value)
{
	std::vector<UTF8String> splits;
	splits.push_back("/");
	splits.push_back("\\");
	int Index = value.LastIndexOf(splits);
	if (Index == -1)return UTF8String("");
	else
	{
		return value.SubString(0, Index);
	}
}

UTF8String Path::GetFileName(UTF8String value)
{
	std::vector<UTF8String> splits;
	splits.push_back("/");
	splits.push_back("\\");
	int Index = value.LastIndexOf(splits);
	if (Index == -1)return value;
	else return value.SubString(Index + 1);
}

UTF8String Path::GetFileExtension(UTF8String value)
{
	UTF8String name = GetFileName(value);
	int Index = name.LastIndexOf(".");
	if (Index == -1)return "";
	else return name.SubString(Index);
}

UTF8String Path::GetFileNameWithoutExtension(UTF8String value)
{
	UTF8String name = GetFileName(value);
	int Index = name.LastIndexOf(".");
	if (Index == -1)return name;
	else return name.SubString(0, Index);
}

UTF8String Path::ReFileNameWithoutExtension(UTF8String value,UTF8String nameWithoutExtension)
{
	return GetDirectoryName(value) + GetSplitChar(value) + nameWithoutExtension + GetFileExtension(value);
}

UTF8String Path::ReFileName(UTF8String value,UTF8String name)
{
	return GetDirectoryName(value) + GetSplitChar(value) + name;
}

UTF8String Path::ReFileExtension(UTF8String value,UTF8String extension)
{
	if (!extension.StartsWith("."))
	{
		extension = "." + extension;
	}
	return GetDirectoryName(value) + GetSplitChar(value) + GetFileNameWithoutExtension(value) + extension;
}

UTF8String Path::ReDirectoryName(UTF8String value,UTF8String directory)
{
	return directory + GetSplitChar(value) + GetFileName(value);
}

UTF8String Path::GetSplitChar(UTF8String value)
{
	if (value.Contains("/"))return "/";
	else return "\\";
}

UTF8String IO::Path::GetSplitChar(std::vector<UTF8String> values)
{
    for(size_t i = 0; i < values.size(); i++)
    {
        if (values[i].Contains("/"))return "/";
        else if (values[i].Contains("\\"))return "\\";
    }
	return "\\";
}

LocaleString IO::Path::GenerateTemporaryPath()
{
#ifdef _MSC_VER
	char tempPath[MAX_PATH];
	DWORD result = GetTempPathA(MAX_PATH, tempPath);
	if (result > 0 && result < MAX_PATH) {
		char tempFileName[MAX_PATH];
		UINT uniqueNum = GetTempFileNameA(tempPath, "temp", 0, tempFileName);

		if (uniqueNum != 0) {
			return tempFileName;
		}
		else {
			return "";
		}
	}
	else {
		return "";
	}
#endif // _MSC_VER
	return "";
}

#ifdef GetTempPath
#undef GetTempPath
#endif

#ifdef CreateDirectory
#undef CreateDirectory
#endif

LocaleString IO::Path::GenerateTemporaryDirectory()
{
	LocaleString tempDirectory = Combine(GetTempPath(),ID::GenerateGUID());
	Directory::CreateDirectory(tempDirectory);
	return tempDirectory;
}


#ifdef GetTempFileName
#undef GetTempFileName
#endif
LocaleString IO::Path::GetTempFileName()
{
	return GenerateTemporaryPath();
}

LocaleString IO::Path::GetTempPath()
{
	#ifdef _MSC_VER
	char tempPath[MAX_PATH];
	DWORD result = GetTempPathA(MAX_PATH, tempPath);
	if (result > 0 && result < MAX_PATH) {
		return tempPath;
	}
	else {
		return "";
	}
	#else
	return "";
	#endif // _MSC_VER
	
}

bool IO::Path::IsEqual(UTF8String first, UTF8String second)
{
	UTF8String firstPath = "";
	for (int i = 0; i < first.Length(); i++)
	{
		if (first[i] == '\\')firstPath.Append("/");
		else firstPath.Append(first[i]);
	}
	firstPath = firstPath.Trim();
	UTF8String secondPath = "";
	for (int i = 0; i < second.Length(); i++)
	{
		if (second[i] == '\\')secondPath.Append("/");
		else secondPath.Append(second[i]);
	}
	secondPath = secondPath.Trim();
	return firstPath == secondPath;
}

HMODULE TidyIO_Path_GetModuleHandleByFunction(void* func) {
	HMODULE hModule = NULL;
	GetModuleHandleExW(
		GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
		(LPCWSTR)func,
		&hModule
	);
	return hModule;
}

LocaleString IO::Path::GetModulePath()
{
	return GetModulePath(TidyIO_Path_GetModuleHandleByFunction);
}

LocaleString IO::Path::GetModulePath(void* func)
{
	HMODULE hModule = TidyIO_Path_GetModuleHandleByFunction(func);
	if (hModule != SUPPORT_NULLPTR) {
		char modulePath[MAX_PATH];
		DWORD result = GetModuleFileNameA(hModule, modulePath, MAX_PATH);
		if (result > 0 && result < MAX_PATH) {
			return modulePath;
		}
		else {
			return "";
		}
	}
	else {
		return "";
	}
}

#ifdef _MSC_VER
#if _MSC_VER <= 1800
LocaleString IO::Path::Combine(LocaleString directory, LocaleString subPath)
{
	UTF8String splitChar = GetSplitChar(UTF8String::Vector(directory, subPath));
	return directory.TrimEnd("\\/") + splitChar + subPath.TrimStart("\\/");
}

LocaleString IO::Path::Combine(LocaleString directory, LocaleString subPath1, LocaleString subPath2)
{
	UTF8String splitChar = GetSplitChar(UTF8String::Vector(directory, subPath1, subPath2));
	return directory.TrimEnd("\\/") + splitChar + subPath1.Trim("\\/") + splitChar + subPath2.TrimStart("\\/");
}

LocaleString IO::Path::Combine(LocaleString directory, LocaleString subPath1, LocaleString subPath2, LocaleString subPath3)
{
	UTF8String splitChar = GetSplitChar(UTF8String::Vector(directory, subPath1, subPath2, subPath3));
	return directory.TrimEnd("\\/") + splitChar + subPath1.Trim("\\/") + splitChar + subPath2.Trim("\\/") + splitChar + subPath3.TrimStart("\\/");
}

LocaleString IO::Path::Combine(LocaleString directory, LocaleString subPath1, LocaleString subPath2, LocaleString subPath3, LocaleString subPath4)
{
	UTF8String splitChar = GetSplitChar(UTF8String::Vector(directory, subPath1, subPath2, subPath3, subPath4));
	return directory.TrimEnd("\\/") + splitChar + subPath1.Trim("\\/") + splitChar + subPath2.Trim("\\/") + splitChar + subPath3.Trim("\\/") + splitChar + subPath4.TrimStart("\\/");
}
#endif
#endif