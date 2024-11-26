
#ifndef __TIDY_IO_DIRECTORYINFO_H__
#define __TIDY_IO_DIRECTORYINFO_H__
#include "Tidy_Macro.h"
#include "Tidy_String.h"
namespace Tidy
{
    namespace IO
    {
        class FileInfo;
        
        class  DirectoryInfo
        {
        public:
            DirectoryInfo(LocaleString target);

            LocaleString Target;
            
            void Create();
            
            DirectoryInfo Parent();
            
            bool Exists();
            
            std::vector<FileInfo> GetFiles();
            
            std::vector<FileInfo> GetAllFiles();
            
            std::vector<DirectoryInfo> GetDirectories();
            
            void Delete();
            
            static DirectoryInfo MyDocument();

            LocaleString operator+(LocaleString &right)
            {
                return Target + right;
            }

    private:
            static void GetFiles(LocaleString directory, std::vector<FileInfo> &files);

            static DirectoryInfo Create(LocaleString path);
        };
    }
}

#endif