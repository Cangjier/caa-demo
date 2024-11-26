
#include "Tidy_IO_DirectoryInfo.h"

#ifdef _MSC_VER
#include "windows.h"
#include <shlobj.h>
#include <direct.h>
#include <io.h>
#endif

#include <stdio.h>
#include <iostream>
#include "Tidy_IO_FileInfo.h"
#include "Tidy_IO_Path.h"

using namespace Tidy;
using namespace IO;

DirectoryInfo::DirectoryInfo(LocaleString target)
{
	Target = target;
}

DirectoryInfo DirectoryInfo::Create(LocaleString path)
{
	DirectoryInfo result = DirectoryInfo(path);
#ifdef _MSC_VER
	if (mkdir(path.ToChars()) == -1)
	{
		//error
	}
#endif // _MSC_VER
	return result;
}

void DirectoryInfo::Create()
{
	if (!Parent().Exists())
	{
		Parent().Create();
	}
	if (!Exists())
	{
		Create(Target);
	}
}

DirectoryInfo DirectoryInfo::Parent()
{
	return DirectoryInfo(Path::GetDirectoryName(Target));
}

bool DirectoryInfo::Exists()
{
#ifdef _MSC_VER
	DWORD ftyp = GetFileAttributesA(Target.ToChars());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;  //something is wrong with your path!  

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;   // this is a directory!  
#endif // _MSC_VER
	return false;    // this is not a directory!  
}

std::vector<FileInfo> DirectoryInfo::GetFiles()
{
	std::vector<FileInfo> result;
#ifdef _MSC_VER
	intptr_t hFile = 0;
	struct _finddata_t fileinfo;
	std::string p;
	if ((hFile = _findfirst((Target + "\\*").ToChars(), &fileinfo)) != -1)
	{
		while (true)
		{
			if (!(fileinfo.attrib & _A_SUBDIR))
			{
				result.push_back(Target + "\\" + fileinfo.name);
			}
			if (_findnext(hFile, &fileinfo) != 0)
			{
				break;
			}
		}
		_findclose(hFile);
	}
#endif // _MSC_VER
	return result;
}

std::vector<FileInfo> DirectoryInfo::GetAllFiles()
{
	std::vector<FileInfo> result;
	GetFiles(Target, result);
	return result;
}

std::vector<DirectoryInfo> DirectoryInfo::GetDirectories()
{
	std::vector<DirectoryInfo> result;
#ifdef _MSC_VER
	intptr_t hFile = 0;
	struct _finddata_t fileinfo;
	std::string p;
	if ((hFile = _findfirst((Target + "\\*").ToChars(), &fileinfo)) != -1)
	{
		while (true)
		{
			if ((fileinfo.attrib & _A_SUBDIR) && strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
			{
				result.push_back(Target + "\\" + fileinfo.name);
			}
			if (_findnext(hFile, &fileinfo) != 0)
			{
				break;
			}
		}
		_findclose(hFile);
	}
#endif // _MSC_VER
	return result;
}

void DirectoryInfo::Delete()
{
#ifdef _MSC_VER
	RemoveDirectoryA(Target.ToChars());
#endif // _MSC_VER
}

DirectoryInfo DirectoryInfo::MyDocument()
{
#ifdef _MSC_VER
	CHAR my_documents[MAX_PATH];
	HRESULT result = SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents);
	return DirectoryInfo(my_documents);
#else
	return path("");
#endif // _MSC_VER

}

void DirectoryInfo::GetFiles(LocaleString path, std::vector<FileInfo>& result)
{
#ifdef _MSC_VER
	intptr_t hFile = 0;
	struct _finddata_t fileinfo;
	std::string p;
	if ((hFile = _findfirst((path + "\\*").ToChars(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					GetFiles(path + "\\" + fileinfo.name, result);
				}
			}
			else
			{
				result.push_back(path + "\\" + fileinfo.name);
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
	else
	{
		//error
	}
#endif // _MSC_VER
}
