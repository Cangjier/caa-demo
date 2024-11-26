
#ifndef __TIDY_ENCODING_H__
#define __TIDY_ENCODING_H__
#include "Tidy_Macro.h"
namespace Tidy
{
    class UTF8String;
    class  Encoding
    {
    public:
        Encoding();

        Encoding(unsigned int Target);

        unsigned int Target;

    public:
        UTF8String Name();
        
        bool operator==(const Encoding &other) const
        {
            return Target == other.Target;
        }

        operator unsigned int() const
        {
            return Target;
        }

    public:
    
        static Encoding UTF8;
        
        static Encoding Locale;
        
        static Encoding GBK;
    };
}
#endif