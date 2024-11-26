
#ifndef __TIDY_BYTES_H__
#define __TIDY_BYTES_H__
#include "Tidy_Macro.h"
namespace Tidy
{
  class  Bytes
  {
  public:
    Bytes(){
        Target = SUPPORT_NULLPTR;
        Length = 0;
    }
    
    Bytes(unsigned char *target, size_t length){
        Target = target;
        Length = length;
    }

    static Bytes New(size_t length) {
        return Bytes(new unsigned char[length], length);
    }

    unsigned char *Target;
    
    size_t Length;
    
    void Release(){
        if(Target != SUPPORT_NULLPTR){
            delete[] Target;
            Target = SUPPORT_NULLPTR;
        }
    }
    
    bool IsNullOrEmpty(){
        return Target == SUPPORT_NULLPTR || Length == 0;
    }
  };
}
#endif