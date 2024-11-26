
#ifndef __TIDY_ID_H__
#define __TIDY_ID_H__
#include "Tidy_Macro.h"
#include "Tidy_UTF8String.h"
namespace Tidy {
class  ID
{
public:
    static UTF8String GenerateID(const UTF8String &base, int length);

    static UTF8String GenerateID(int length);

    static UTF8String ConvertToID(SUPPORT_INT64 value);
    
    static UTF8String GeneratePathName();
    
    static UTF8String GenerateGUID();
};
}
#endif