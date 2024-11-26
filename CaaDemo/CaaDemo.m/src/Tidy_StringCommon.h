

#ifndef SUPPORT_STD_TOSTRING
#define SUPPORT_STD_TOSTRING
#include <string>
#if defined(_MSC_VER) && _MSC_VER < 1600
namespace std {
    std::string to_string(int value);
    
    std::string to_string(unsigned int value);

    std::string to_string(long value);

    std::string to_string(unsigned long value);

    std::string to_string(long long value);

    std::string to_string(unsigned long long value);

    std::string to_string(float value);

    std::string to_string(double value);

    int stoi(const std::string& str);

    long stol(const std::string& str);

    long long stoll(const std::string& str);

    float stof(const std::string& str);

    double stod(const std::string& str);
}
    #endif
#endif