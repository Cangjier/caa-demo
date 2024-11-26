
#ifndef __TIDY_IO_FILE_H__
#define __TIDY_IO_FILE_H__
#include "Tidy_Macro.h"
#include <vector>
#include <map>
#include "Tidy_LocaleString.h"
#include "Tidy_UTF8String.h"
#include "Tidy_GBKString.h"
#include "Tidy_Bytes.h"
#include "Tidy_IO_FileInfo.h"
#include "Tidy_Encoding.h"

namespace Tidy
{
    namespace IO
    {
        class Path;
        class Directory;

        class  File
        {
        public:
            static bool Exists(LocaleString path);
            
            static void Copy(LocaleString sourcePath, LocaleString destPath);
            
            static void Copy(LocaleString sourcePath, LocaleString destPath, bool overwrite);

            static void Delete(LocaleString path);
            
            static void CreateEmptyFile(LocaleString path);
            
            static std::string ReadAllText(LocaleString path);
            
            static UTF8String ReadAllText(LocaleString path, const Encoding& encoding);
            
            static Bytes ReadAllBytes(LocaleString path);
            
            static bool WriteAllText(LocaleString path, const std::string& contents);
            
            static bool WriteAllText(LocaleString path, const UTF8String& contents, const Encoding& encoding);
            
            static std::vector<std::string> ReadAllLines(LocaleString path);
            
            static std::vector<UTF8String> ReadAllLines(LocaleString path, const Encoding& encoding);
            
            static void WriteAllLines(LocaleString path, const std::vector<std::string>& lines);
            
            static void WriteAllLines(LocaleString path, const std::vector<UTF8String>& lines, const Encoding& encoding);
            
            static bool AppendAllText(LocaleString path, const std::string& contents);
            
            static bool AppendAllText(LocaleString path, const UTF8String& contents, const Encoding& encoding);
        };
    }
}
#endif