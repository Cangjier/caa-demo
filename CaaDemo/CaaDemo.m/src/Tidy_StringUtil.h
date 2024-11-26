#ifndef __TIDY_STRING_UTIL_H__
#define __TIDY_STRING_UTIL_H__

#ifndef SUPPORT_NULLPTR
    #if defined(_MSC_VER) && _MSC_VER >= 1600
        #define SUPPORT_NULLPTR nullptr
    #else
        #define SUPPORT_NULLPTR NULL
    #endif
#endif

#ifndef SUPPORT_STD_WSTRING
    #ifdef _MSC_VER
        #if _MSC_VER >= 1200
            #define SUPPORT_STD_WSTRING 1
        #else
            #define SUPPORT_STD_WSTRING 0
        #endif
    #else
        #define SUPPORT_STD_WSTRING 1
    #endif
    #if SUPPORT_STD_WSTRING
        // #include <wstring>
    #endif
#endif

#include "Tidy_Macro.h"
#include <string>
#include <vector>
namespace Tidy {
    class  StringUtil {
    public:
    static unsigned int GetLocale();
    static std::string To(const std::string &value, unsigned int fromCodePage, unsigned int toCodePage);
    static std::string To(const wchar_t *value, unsigned int toCodePage);
#if SUPPORT_STD_WSTRING
    static std::wstring To(const std::string &value, unsigned int fromCodePage);
#endif
    };
};
#endif