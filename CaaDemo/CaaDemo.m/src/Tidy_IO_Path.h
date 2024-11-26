
#ifndef __TIDY_IO_PATH_H__
#define __TIDY_IO_PATH_H__
#include "Tidy_Macro.h"
#include "Tidy_String.h"
namespace Tidy
{
    namespace IO
    {
        class  Path
        {
        public:
            static UTF8String GetDirectoryName(UTF8String value);
            
            static UTF8String GetFileName(UTF8String value);
            
            static UTF8String GetFileExtension(UTF8String value);
            
            static UTF8String GetFileNameWithoutExtension(UTF8String value);
            
            static UTF8String ReFileNameWithoutExtension(UTF8String value, UTF8String nameWithoutExtension);
            
            static UTF8String ReFileName(UTF8String value, UTF8String name);
            
            static UTF8String ReFileExtension(UTF8String value, UTF8String Extension);
            
            static UTF8String ReDirectoryName(UTF8String value, UTF8String directory);
            
            static UTF8String GetSplitChar(UTF8String value);
            
            static UTF8String GetSplitChar(std::vector<UTF8String> values);
            
            static LocaleString GenerateTemporaryPath();
            
            static LocaleString GenerateTemporaryDirectory();

#ifdef GetTempFileName
#undef GetTempFileName
#endif

            static LocaleString GetTempFileName();

#ifdef GetTempPath
#undef GetTempPath
#endif

            static LocaleString GetTempPath();
            
            static bool IsEqual(UTF8String first, UTF8String second);
            
            static LocaleString GetModulePath();
            
            static LocaleString GetModulePath(void *func);
#ifdef _MSC_VER
#if _MSC_VER <= 1800
            static LocaleString Combine(LocaleString directory, LocaleString subPath);

            static LocaleString Combine(LocaleString directory, LocaleString subPath1, LocaleString subPath2);

            static LocaleString Combine(LocaleString directory, LocaleString subPath1, LocaleString subPath2, LocaleString subPath3);

            static LocaleString Combine(LocaleString directory, LocaleString subPath1, LocaleString subPath2, LocaleString subPath3, LocaleString subPath4);
#else
            static LocaleString Combine(LocaleString arg)
            {
                return arg;
            }

            template <typename... Args>
            static LocaleString Combine(const LocaleString &arg, Args... args)
            {
                UTF8String splitChar = GetSplitChar(UTF8String::Vector(arg, args...));
                return arg.TrimEnd("\\/") + splitChar + Combine(args...);
            }
#endif
#else
            static LocaleString Combine(LocaleString arg)
            {
                return arg;
            }

            template <typename... Args>
            static LocaleString Combine(const LocaleString &arg, Args... args)
            {
                UTF8String splitChar = GetSplitChar(UTF8String::Vector(arg, args...));
                return arg.TrimEnd("\\/") + splitChar + Combine(args...);
            }
#endif
        };
    }
}
#endif