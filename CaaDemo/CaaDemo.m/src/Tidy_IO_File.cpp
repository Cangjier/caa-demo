#include <fstream>
#include <iostream>
#include <fstream>
#include "Tidy_IO_File.h"
#include "Tidy_IO_Path.h"
#include "Tidy_IO_Directory.h"

using namespace Tidy;
using namespace IO;

bool File::Exists(LocaleString path)
{
#ifdef _MSC_VER
#if _MSC_VER <= 1800
	WIN32_FIND_DATA findFileData;
	HANDLE hFind = FindFirstFile(path.ToWString().c_str(), &findFileData);

	if (hFind != INVALID_HANDLE_VALUE) {
		FindClose(hFind);
		return true;
	}
	return false;
#else
	struct stat Buffer;
	return (stat(path.ToChars(), &Buffer) == 0);
#endif

#else
	return false;
#endif //_MSC_VER
}

void IO::File::Copy(LocaleString sourcePath, LocaleString destPath)
{
	std::ifstream source(sourcePath.Target.c_str(), std::ios::binary);
	std::ofstream dest(destPath.Target.c_str(), std::ios::binary);

	if (source && dest)
	{
		dest << source.rdbuf();
	}
}

void IO::File::Copy(LocaleString sourcePath, LocaleString destPath, bool overwrite)
{
	if (!overwrite && std::ifstream(destPath.Target.c_str()))
	{
		return;
	}
	Copy(sourcePath, destPath);
}

void IO::File::Delete(LocaleString path)
{
	if (std::remove(path.Target.c_str()) == 0)
	{
		std::cout << "File deleted successfully." << std::endl;
	}
	else
	{
		std::cerr << "Failed to delete file." << std::endl;
	}
}

void IO::File::CreateEmptyFile(LocaleString path)
{
	std::ofstream file(path.Target.c_str());
	if (!file)
	{
		std::cerr << "Failed to create file." << std::endl;
	}
	file.close();
}

std::string IO::File::ReadAllText(LocaleString path)
{
	std::ifstream file(path.Target.c_str());
	if (file)
	{
		std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		return contents;
	}
	else
	{
		std::cerr << "Failed to read file." << std::endl;
		return "";
	}
}

UTF8String IO::File::ReadAllText(LocaleString path, const Encoding& encoding)
{
	if (encoding != Encoding::UTF8) {
		return StringUtil::To(ReadAllText(path), encoding, Encoding::UTF8);
	}
	else {
		return ReadAllText(path);
	}
}

Bytes IO::File::ReadAllBytes(LocaleString path)
{
	std::ifstream file(path.Target.c_str(), std::ios::binary);
	if (!file.is_open()) {
		return Bytes();
	}
	file.seekg(0, std::ios::end);
	std::streampos fileSize = file.tellg();
	file.seekg(0, std::ios::beg);
	unsigned char* data= new unsigned char[fileSize];
	file.read(reinterpret_cast<char*>(data), fileSize);
	Tidy::Bytes bytes(data, static_cast<std::size_t>(fileSize));
	file.close();
	return bytes;
}

bool IO::File::WriteAllText(LocaleString path, const std::string& contents)
{
	std::ofstream file(path.Target.c_str());
	if (file)
	{
		file << contents;
		return true;
	}
	else
	{
		return false;
	}
}

bool IO::File::WriteAllText(LocaleString path, const UTF8String& contents, const Encoding& encoding)
{
	if (encoding != Encoding::UTF8) {
		return WriteAllText(path, StringUtil::To(contents.Target, Encoding::UTF8, encoding));
	}
	else {
		return WriteAllText(path, contents.Target);
	}
}

std::vector<std::string> IO::File::ReadAllLines(LocaleString path)
{
	std::vector<std::string> lines;
	std::ifstream file(path.Target.c_str());
	if (file)
	{
		std::string line;
		while (std::getline(file, line))
		{
			lines.push_back(line);
		}
	}
	else
	{
		std::cerr << "Failed to read file." << std::endl;
	}
	return lines;
}

std::vector<UTF8String> IO::File::ReadAllLines(LocaleString path, const Encoding& encoding)
{
	std::vector<UTF8String> lines;
	std::ifstream file(path.Target.c_str());
	if (file)
	{
		std::string line;
		while (std::getline(file, line))
		{
			if (encoding != Encoding::UTF8) {
				lines.push_back(StringUtil::To(line, encoding.Target, Encoding::UTF8.Target));
			}
			else
			{
				lines.push_back(line);
			}
		}
	}
	else
	{
		std::cerr << "Failed to read file." << std::endl;
	}
	return lines;
}

void IO::File::WriteAllLines(LocaleString path, const std::vector<std::string>& lines)
{
	std::ofstream file(path.Target.c_str());
	if (file)
	{
        for(size_t i = 0; i < lines.size(); i++)
        {
            file << lines[i];
            if(i != lines.size() - 1)
            {
                file << std::endl;
            }
        }
	}
	else
	{
		std::cerr << "Failed to write file." << std::endl;
	}
}

void IO::File::WriteAllLines(LocaleString path, const std::vector<UTF8String>& lines, const Encoding& encoding)
{
	std::ofstream file(path.Target.c_str());
	if (file)
	{
        for(size_t i = 0; i < lines.size(); i++)
        {
            if (encoding != Encoding::UTF8) {
                file << StringUtil::To(lines[i].Target, Encoding::UTF8.Target, encoding.Target) << std::endl;
            }
            else {
                file << lines[i].Target << std::endl;
            }
        }
	}
	else
	{
		std::cerr << "Failed to write file." << std::endl;
	}
}

bool IO::File::AppendAllText(LocaleString path, const std::string& contents)
{
	std::ofstream file(path.Target.c_str(), std::ios::app);
	if (file)
	{
		file << contents;
		return true;
	}
	else
	{
		return false;
	}
}

bool IO::File::AppendAllText(LocaleString path, const UTF8String& contents, const Encoding& encoding)
{
	std::ofstream file(path.Target.c_str(), std::ios::app);
	if (file)
	{
		if (encoding != Encoding::UTF8) {
			file << StringUtil::To(contents.Target, Encoding::UTF8, encoding);
		}
		else {
			file << contents.Target;
		}
		return true;
	}
	else
	{
		return false;
	}
}
