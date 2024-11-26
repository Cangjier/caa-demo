
#ifndef __TIDY_IO_DIRECTORY_H__
#define __TIDY_IO_DIRECTORY_H__
#include "Tidy_Macro.h"
#include <vector>
#include "Tidy_String.h"
#include "Tidy_IO_DirectoryInfo.h"

namespace Tidy
{
    class DateTime;
    namespace IO
    {
        class DirectoryInfo;
        class  Directory
        {
        public:
            static DirectoryInfo GetParent(LocaleString path);
#undef CreateDirectory
            static DirectoryInfo CreateDirectory(LocaleString path);

            static LocaleString TryCreateDirectory(LocaleString path);
            
            static bool Exists(LocaleString path);
            
            static void SetCreationTime(LocaleString path, DateTime creationTime);
            
            static DateTime GetCreationTime(LocaleString path);
            
            static std::vector<LocaleString> GetFiles(LocaleString path);
            
            static std::vector<LocaleString> GetDirectories(LocaleString path);
            
            static void Move(LocaleString sourceDirName, LocaleString destDirName);
            
            static void Move(LocaleString sourceDirName, LocaleString destDirName, bool recursive);
            
            static void Delete(LocaleString path, bool recursive);
            
            static LocaleString GetDocumentDirectory();
            
            static LocaleString GetUserProfileDirectory();
            
            static LocaleString GetProgramFilesDirectory(int platform);
            
            static LocaleString GetProgramDataDirectory();
            
            static LocaleString GetTemporaryDirectory();
            
            static LocaleString GenerateTemporaryDirectory();
            
            static LocaleString GetModuleDirectory();
        };

    }
}
#endif