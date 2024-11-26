
#include "Tidy_StringCommon.h"
#if defined(_MSC_VER) && _MSC_VER < 1600
#include <sstream>
namespace std {
    std::string to_string(int value) {
        std::stringstream ss;
        ss << value;
        return ss.str();
    }
    
    std::string to_string(unsigned int value) {
        std::stringstream ss;
        ss << value;
        return ss.str();
    }

    std::string to_string(long value) {
        std::stringstream ss;
        ss << value;
        return ss.str();
    }

    std::string to_string(unsigned long value) {
        std::stringstream ss;
        ss << value;
        return ss.str();
    }

    std::string to_string(long long value) {
        std::stringstream ss;
        ss << value;
        return ss.str();
    }

    std::string to_string(unsigned long long value) {
        std::stringstream ss;
        ss << value;
        return ss.str();
    }

    std::string to_string(float value) {
        std::stringstream ss;
        ss << value;
        return ss.str();
    }

    std::string to_string(double value) {
        std::stringstream ss;
        ss << value;
        return ss.str();
    }

    int stoi(const std::string& str) {
        int result = 0;
        std::istringstream iss(str);
        iss >> result;
        return result;
    }

    long stol(const std::string& str) {
        long result = 0;
        std::istringstream iss(str);
        iss >> result;
        return result;
    }

    long long stoll(const std::string& str) {
        long long result = 0;
        std::istringstream iss(str);
        iss >> result;
        return result;
    }

    float stof(const std::string& str) {
        float result = 0;
        std::istringstream iss(str);
        iss >> result;
        return result;
    }

    double stod(const std::string& str) {
        double result = 0;
        std::istringstream iss(str);
        iss >> result;
        return result;
    }
}
#endif