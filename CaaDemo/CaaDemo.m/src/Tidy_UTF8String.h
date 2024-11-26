#ifndef __TIDY_UTF8STRING_H__
#define __TIDY_UTF8STRING_H__
#include "Tidy_Macro.h"
#include <string>
#include <vector>
#include "Tidy_StringUtil.h"
#include "Tidy_StringCommon.h"

#ifndef SUPPORT_NULLPTR
    #if defined(_MSC_VER) && _MSC_VER >= 1600
        #define SUPPORT_NULLPTR nullptr
    #else
        #define SUPPORT_NULLPTR NULL
    #endif
#endif

#ifndef SUPPORT_STD_STRINGSTREAM
    #ifdef _MSC_VER
        #if _MSC_VER >= 1400
            #define SUPPORT_STD_STRINGSTREAM 1
        #else
            #define SUPPORT_STD_STRINGSTREAM 0
        #endif
    #else
        #define SUPPORT_STD_STRINGSTREAM 1
    #endif

    #if SUPPORT_STD_STRINGSTREAM
        #include <sstream>
    #endif
#endif

#ifndef SUPPORT_EXPLICIT
#ifdef _MSC_VER
    #if _MSC_VER >= 1800
        #define SUPPORT_EXPLICIT explicit
    #else
        #define SUPPORT_EXPLICIT
    #endif
#endif
#endif

#ifndef SUPPORT_INT64
    #ifdef _MSC_VER
        #if _MSC_VER <= 1800
            #define SUPPORT_INT64 __int64
        #else
            #define SUPPORT_INT64 std::int64_t
        #endif
    #else
        #define SUPPORT_INT64 std::int64_t
    #endif
#endif

#ifndef SUPPORT_STD_OSTRINGSTREAM
    #if _MSC_VER >= 1400
        #define SUPPORT_STD_OSTRINGSTREAM 1
    #else
        #define SUPPORT_STD_OSTRINGSTREAM 0
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

#ifndef SUPPORT_RVALUE_REFERENCES
    #ifdef _MSC_VER
        #if _MSC_VER >= 1800
            #define SUPPORT_RVALUE_REFERENCES 1
        #else
            #define SUPPORT_RVALUE_REFERENCES 0
        #endif
    #endif
#endif

#ifndef SUPPORT_STD_FUNCTION
    #ifdef _MSC_VER
        #if _MSC_VER >= 1800
            #define SUPPORT_STD_FUNCTION 1
        #else
            #define SUPPORT_STD_FUNCTION 0
        #endif
    #endif
#endif

#if SUPPORT_STD_FUNCTION
    #include <functional>
#endif
#include "Tidy_LocaleString.h"
namespace Tidy {
class LocaleString;
}
#include "Tidy_GBKString.h"
namespace Tidy {
class GBKString;
}
namespace Tidy {
class  UTF8String {
public:
    std::string Target;
    int TargetEncoding;
    UTF8String() {
        this->Target = "";
        this->TargetEncoding = 65001;
    }
    UTF8String(const wchar_t* target) {
        this->TargetEncoding = 65001;
        if (target == SUPPORT_NULLPTR) {
            this->Target = "";
        } else {
            this->Target = StringUtil::To(target, TargetEncoding);
        }
    }
#if SUPPORT_STD_WSTRING
        UTF8String(const std::wstring& target) {
        this->TargetEncoding = 65001;
        this->Target = StringUtil::To(target.c_str(), TargetEncoding);
    }
#endif
    UTF8String(const std::string& target) {
        this->TargetEncoding = 65001;
        this->Target = target;
    }
    UTF8String(const char* target) {
        this->TargetEncoding = 65001;
        if (target == SUPPORT_NULLPTR) {
            this->Target = "";
        } else {
            this->Target = target;
        }
    }
    UTF8String(char* target) {
        this->TargetEncoding = 65001;
        if (target == SUPPORT_NULLPTR) {
            this->Target = "";
        } else {
            this->Target = target;
        }
    }
#if SUPPORT_STD_STRINGSTREAM
    UTF8String(const std::stringstream& target) {
        this->TargetEncoding = 65001;
        std::ostringstream ss;
        ss << target.rdbuf();
        this->Target = ss.str();
    }
#endif
    SUPPORT_EXPLICIT UTF8String(int target) {
        this->TargetEncoding = 65001;
        this->Target = std::to_string(target);
    }
    SUPPORT_EXPLICIT UTF8String(long target) {
        this->TargetEncoding = 65001;
        this->Target = std::to_string(target);
    }
    SUPPORT_EXPLICIT UTF8String(SUPPORT_INT64 target) {
        this->TargetEncoding = 65001;
        this->Target = std::to_string(target);
    }
    SUPPORT_EXPLICIT UTF8String(SUPPORT_INT64 value, const UTF8String& base) {
        this->TargetEncoding = 65001;
        this->Target = std::string();
        int baseLength = base.Length();
        while (true) {
            SUPPORT_INT64 next = value / baseLength;
            SUPPORT_INT64 mod = value % baseLength;
            Insert(0, base[(int)mod]);
            if (next == 0) {
                break;
            }
            value = next;
        }
    }
    SUPPORT_EXPLICIT UTF8String(unsigned short target) {
        this->TargetEncoding = 65001;
        this->Target = std::to_string(target);
    }
    SUPPORT_EXPLICIT UTF8String(unsigned int target) {
        this->TargetEncoding = 65001;
        this->Target = std::to_string(target);
    }
    SUPPORT_EXPLICIT UTF8String(unsigned long long target) {
        this->TargetEncoding = 65001;
        this->Target = std::to_string(target);
    }
    SUPPORT_EXPLICIT UTF8String(double target) {
        this->TargetEncoding = 65001;
#if SUPPORT_STD_OSTRINGSTREAM
        std::ostringstream out;
        out.precision(14);
        out << std::fixed << target;
        this->Target = out.str();
#else
        this->Target = std::to_string(target);
#endif
    }
    SUPPORT_EXPLICIT UTF8String(char target) {
        this->TargetEncoding = 65001;
        this->Target = std::string();
        this->Target.append(1, target);
    }
    SUPPORT_EXPLICIT UTF8String(float target) {
        this->TargetEncoding = 65001;
        this->Target = std::to_string(target);
    }
    SUPPORT_EXPLICIT UTF8String(bool target) {
        this->TargetEncoding = 65001;
        this->Target = target ? "true" : "false";
    }
    UTF8String(const LocaleString& target);
#if SUPPORT_RVALUE_REFERENCES
    UTF8String(const LocaleString&& target);
#endif
    UTF8String(const GBKString& target);
#if SUPPORT_RVALUE_REFERENCES
    UTF8String(const GBKString&& target);
#endif
    static UTF8String HexBase() {
        return "0123456789ABCDEF";
    }
    static UTF8String Hex(SUPPORT_INT64 value) {
        return UTF8String(value, HexBase());
    }
    static UTF8String FromPointer(void* value) {
        return "0x"+Hex(reinterpret_cast<SUPPORT_INT64>(value));
}
    const char* ToChars() const {
        return this->Target.c_str();
    }
    char* Clone() const {
        char* result = new char[this->Target.size() + 1];
        memset(result, 0, this->Target.size() + 1);
        strcpy(result, this->Target.c_str());
        return result;
    }
#if SUPPORT_STD_WSTRING
    std::wstring ToWString() const {
    return StringUtil::To(Target, TargetEncoding);
    }
#endif
    int Length() const {
        return (int)this->Target.length();
    }
    UTF8String SubString(int start, int length = -1) const {
    if (length == -1)
        return Target.substr(start);
    else
        return Target.substr(start, length);
    }
     UTF8String& Insert(int index, const UTF8String& value) {
        this->Target.insert(index, value.Target);
        return *this;
    }
    int IndexOf(const UTF8String& value, int start = 0) const {
        size_t result = this->Target.find(value.Target, start);
        if (result == std::string::npos) {
            return -1;
        }
        return (int)result;
    }
    int LastIndexOf(const UTF8String& value, int start = -1) const {
        start = start == -1 ? std::string::npos : start;
        size_t result = this->Target.rfind(value.Target, start);
        if (result == std::string::npos) {
            return -1;
        }
        return (int)result;
    }

int LastIndexOf(const std::vector<UTF8String>& values, int start = -1) const {
    start = start == -1 ? std::string::npos : start;
    int result = -1;
    for (size_t i = 0; i < values.size(); i++) {
        const UTF8String& value = values[i];
        int index = LastIndexOf(value, start);
        if (index != -1) {
            if (index > result) {
                result = index;
            }
        }
    }
    return result;
}
    UTF8String Replace(const UTF8String& oldValue, const UTF8String& newValue) const {
        std::string temp = Target;
        std::string oldString = oldValue.Target;
        std::string newString = newValue.Target;
        std::string::size_type index = 0;
        std::string::size_type newLength = newString.size();
        std::string::size_type oldLength = oldString.size();
        index = temp.find(oldString, index);
        while ((index != std::string::npos))
        {
            temp.replace(index, oldLength, newString);
            index = temp.find(oldString, (index + newLength));
        }
        return temp;
    }
    UTF8String Replace(const std::vector<UTF8String>& oldValues, const std::vector<UTF8String>& newValues) const {
        UTF8String result = Target;
        for (size_t i = 0; i < oldValues.size(); i++) {
            result = result.Replace(oldValues[i], newValues[i]);
        }
        return result;
    }
    UTF8String& Append(const UTF8String& value) {
        this->Target.append(value.Target);
        return *this;
    }

    UTF8String& Append(const std::vector<UTF8String>& values) {
        for(size_t i = 0; i < values.size(); i++) {
            this->Target.append(values[i].Target);
        }
        return *this;
    }
    UTF8String& AppendLine(const UTF8String& value) {
        this->Target.append(value.Target);
        this->Target.append("\r\n");
        return *this;
    }
    UTF8String& AppendLine() {
        this->Target.append("\r\n");
        return *this;
    }
    UTF8String MiddleValue(const UTF8String& startValue, const UTF8String& endValue, int index = 0) const {
        size_t offset = 0;
        for (int i = 0; i <= index; i++)
        {
            size_t startIndex = Target.find(startValue.Target, offset);
            if (startIndex == std::string::npos)
            {
                return "";
            }
            size_t endIndex = Target.find(endValue.Target, offset + startValue.Length());
            if (endIndex == std::string::npos)
            {
                return "";
            }
            if (i == index)
            {
                return Target.substr(startIndex + (int)startValue.Length(), endIndex - startIndex - (int)startValue.Length());
            }
            else
            {
                offset = endIndex + endValue.Length();
            }
        }
        return "";
    }
    int MiddleCount(const UTF8String& startValue, const UTF8String& endValue) const {
        size_t offset = 0;
        int count = 0;
        while (true)
        {
            size_t startIndex = Target.find(startValue.Target, offset);
            if (startIndex == std::string::npos)
            {
                return count;
            }
            size_t endIndex = Target.find(endValue.Target, offset + startValue.Length());
            if (endIndex == std::string::npos)
            {
                return count;
            }
            offset = endIndex + endValue.Length();
            count++;
        }
        return count;
    }
    static UTF8String Repeat(const UTF8String value, int count) {
        UTF8String result;
        for (int i = 0; i < count; i++) {
            result.Append(value);
        }
        return result;
    }
    UTF8String Repeat(int count) const {
        UTF8String result;
        for (int i = 0; i < count; i++) {
            result.Append(*this);
        }
        return result;
    }
    UTF8String Trim(const UTF8String& chars = " ") const {
        std::string result = Target;
        std::string trimChars = chars.Target;
        // Trim from the beginning  
        std::string::iterator it = result.begin();
        while (it != result.end() && trimChars.find(*it) != std::string::npos) {
            ++it;
        }
        result.erase(result.begin(), it);

        // Trim from the end  
        std::reverse_iterator<std::string::iterator> rit = result.rbegin();
        while (rit != result.rend() && trimChars.find(*rit) != std::string::npos) {
            ++rit;
        }
        result.erase(rit.base(), result.end());

        return result;
    }
    UTF8String TrimStart(const UTF8String& chars = " ") const {
        std::string result = Target;
        std::string trimChars = chars.Target;
        size_t pos = result.find_first_not_of(trimChars);
        if (pos != std::string::npos) {
            return result.substr(pos);
        }
        else {
            return ""; // 如果整个字符串都是由要删除的字符组成，则返回空字符串  
        }
    }
    UTF8String TrimEnd(const UTF8String& chars = " ") const {
        std::string result = Target;
        std::string trimChars = chars.Target;

        std::reverse_iterator<std::string::iterator> rit = result.rbegin();
        while (rit != result.rend() && trimChars.find(*rit) != std::string::npos) {
            ++rit;
        }
        result.erase(rit.base(), result.end());

        return result;
    }
    UTF8String OnlyNumber() const {
        UTF8String result;
        for(size_t i = 0; i < Target.size(); i++) {
            if(Target[i] >= '0' && Target[i] <= '9') {
                result.Append(Target[i]);
            }
        }
        return result;
    }

    UTF8String RemoveChars(const UTF8String& chars) const {
        UTF8String result;
        for(size_t i = 0; i < Target.size(); i++) {
            if(chars.IndexOf(Target[i]) == -1) {
                result.Append(Target[i]);
            }
        }
        return result;
    }
    bool IsEmpty() const {
        return Target.empty();
    }
    UTF8String Remove(int start, int length = -1) const {
        std::string result = Target;
			if (length == -1)
			{
				result.erase(start);
			}
			else
			{
				result.erase(start, length);
			}
			return result;
    }
    bool StartsWith(const UTF8String& value) const {
        return Target.find(value.Target) == 0;
    }
    bool EndsWith(const UTF8String& value) const {
        return Target.rfind(value.Target) == (Target.size() - value.Length());
    }
    bool Contains(const UTF8String& value) const {
        return Target.find(value.Target) != std::string::npos;
    }
    UTF8String FillEnd(int length, const UTF8String& value) const {
        UTF8String result = Target;
        while (result.Length() < length)
        {
            result.Append(value);
        }
        return result;
    }
    UTF8String FillStart(int length, const UTF8String& value) const {
        UTF8String result = Target;
        while (result.Length() < length)
        {
            result.Insert(0, value);
        }
        return result;
    }
    UTF8String Format(const UTF8String& value0) const {
        return Replace("{0}", value0);
    }
    UTF8String Format(const UTF8String& value0, const UTF8String& value1) const {
        return Replace("{0}", value0).Replace("{1}", value1);
    }
    UTF8String Format(const UTF8String& value0, const UTF8String& value1, const UTF8String& value2) const {
        return Replace("{0}", value0).Replace("{1}", value1).Replace("{2}", value2);
    }
    UTF8String Format(const UTF8String& value0, const UTF8String& value1, const UTF8String& value2, const UTF8String& value3) const {
        return Replace("{0}", value0).Replace("{1}", value1).Replace("{2}", value2).Replace("{3}", value3);
    }
    UTF8String Format(const UTF8String& value0, const UTF8String& value1, const UTF8String& value2, const UTF8String& value3, const UTF8String& value4) const {
        return Replace("{0}", value0).Replace("{1}", value1).Replace("{2}", value2).Replace("{3}", value3).Replace("{4}", value4);
    }
    UTF8String Format(const UTF8String& value0, const UTF8String& value1, const UTF8String& value2, const UTF8String& value3, const UTF8String& value4, const UTF8String& value5) const {
        return Replace("{0}", value0).Replace("{1}", value1).Replace("{2}", value2).Replace("{3}", value3).Replace("{4}", value4).Replace("{5}", value5);
    }
    UTF8String Format(const UTF8String& value0, const UTF8String& value1, const UTF8String& value2, const UTF8String& value3, const UTF8String& value4, const UTF8String& value5, const UTF8String& value6) const {
        return Replace("{0}", value0).Replace("{1}", value1).Replace("{2}", value2).Replace("{3}", value3).Replace("{4}", value4).Replace("{5}", value5).Replace("{6}", value6);
    }
    UTF8String Format(const UTF8String& value0, const UTF8String& value1, const UTF8String& value2, const UTF8String& value3, const UTF8String& value4, const UTF8String& value5, const UTF8String& value6, const UTF8String& value7) const {
        return Replace("{0}", value0).Replace("{1}", value1).Replace("{2}", value2).Replace("{3}", value3).Replace("{4}", value4).Replace("{5}", value5).Replace("{6}", value6).Replace("{7}", value7);
    }
    UTF8String Format(const UTF8String& value0, const UTF8String& value1, const UTF8String& value2, const UTF8String& value3, const UTF8String& value4, const UTF8String& value5, const UTF8String& value6, const UTF8String& value7, const UTF8String& value8) const {
        return Replace("{0}", value0).Replace("{1}", value1).Replace("{2}", value2).Replace("{3}", value3).Replace("{4}", value4).Replace("{5}", value5).Replace("{6}", value6).Replace("{7}", value7).Replace("{8}", value8);
    }
    UTF8String& Clear() {
        this->Target.clear();
        return *this;
    }

    bool IsNumber() const {
        if (Target.empty()) {
            return false;
        }
        for(size_t i = 0; i < Target.size(); i++) {
            if (Target[i] < '0' || Target[i] > '9') {
                return false;
            }
        }
        return true;
    }

    int ToInt() const {
        try {
            return std::stoi(Target);
        } catch (...) {
            throw new std::exception("String is not a number.");
        }
    }
    
    float ToFloat() const {
        try {
            return std::stof(Target);
        } catch (...) {
            throw new std::exception("String is not a number.");
        }
    }

    double ToDouble() const {
        try {
            return std::stod(Target);
        } catch (...) {
            throw new std::exception("String is not a number.");
        }
    }

    SUPPORT_INT64 ToInt64() const {
        try {
            return std::stoll(Target);
        } catch (...) {
            throw new std::exception("String is not a number.");
        }
    }
    bool IsTrue() const {
        return ToLower() == "true";
    }
    bool IsFalse() const {
        return ToLower() == "false";
    }
    bool ToBool() const {
        if (ToLower() == "true") {
            return true;
        } else if (ToLower() == "false") {
            return false;
        } else {
            throw new std::exception("String is not a boolean.");
        }
    }
    std::string ToStdString(unsigned int encodingPage) const {
        return StringUtil::To(Target, TargetEncoding, encodingPage);
    }

    UTF8String ToLower() const {
        std::string result = "";
        for(size_t i = 0; i < Target.size(); i++) {
            result.append(1, tolower(Target[i]));
        }
        return result;
    }

    UTF8String ToUpper() const {
        std::string result = "";
        for(size_t i = 0; i < Target.size(); i++) {
            result.append(1, toupper(Target[i]));
        }
        return result;
    }
    std::vector<UTF8String> Split(const UTF8String& chars) const {
        std::vector<UTF8String> result;
        std::string temp = Target;
        std::string splitChars = chars.Target;
        size_t index = 0;
        while (true)
        {
            size_t nextIndex = temp.find(splitChars, index);
            if (nextIndex == std::string::npos)
            {
                result.push_back(temp.substr(index));
                break;
            }
            result.push_back(temp.substr(index, nextIndex - index));
            index = nextIndex + splitChars.size();
        }
        return result;
    }
    
    UTF8String Intersect(const UTF8String& value) const {
        std::string result;
        for(size_t i = 0; i < Target.size(); i++) {
            if(value.Contains(Target[i])) {
                result.append(1, Target[i]);
            }
        }
        return result;
    }
#if SUPPORT_STD_FUNCTION
        UTF8String Map(std::function<UTF8String(UTF8String)> func) const {
        UTF8String result;
        for (char item : Target)
        {
            result.Append(func(item));
        }
        return result;
        }
        #endif
    UTF8String operator[](int index) const {
        return Target[index];
    }
    UTF8String& operator=(const UTF8String& value) {
        this->TargetEncoding = 65001;
        if(this != &value) {
            this->Target = value.Target;
        }
        return *this;
    }
    UTF8String operator+(const char* value) const {
        return Target + value;
    }
    UTF8String operator+(const std::string& value) const {
        return Target + value;
    }
    UTF8String operator+(const UTF8String& value) const {
        return Target + value.Target;
    }
#if SUPPORT_RVALUE_REFERENCES
    UTF8String operator+(const UTF8String&& value) const {
        return Target + value.Target;
    }
#endif
    UTF8String operator+(int value) const {
        return Target + std::to_string(value);
    }
    UTF8String operator+(long value) const {
        return Target + std::to_string(value);
    }
    UTF8String operator+(SUPPORT_INT64 value) const {
        return Target + std::to_string(value);
    }
    UTF8String operator+(unsigned int value) const {
        return Target + std::to_string(value);
    }
    UTF8String operator+(float value) const {
        return Target + std::to_string(value);
    }
    UTF8String operator+(double value) const {
        return Target + std::to_string(value);
    }
    UTF8String operator+(bool value) const {
        return Target + (value ? "true" : "false");
    }
    UTF8String operator+(char value) const {
        std::string result = Target;
        result.append(1, value);
        return result;
    }
    friend UTF8String operator+(const char* left, const UTF8String& right) {
        return left + right.Target;
    }
    friend UTF8String operator+(const std::string& left, const UTF8String& right) {
        return left + right.Target;
    }
    bool operator==(const UTF8String& value) const {
        return Target == value.Target;
    }
    bool operator==(const char* value) const {
        return Target == value;
    }
    bool operator==(const std::string& value) const {
        return Target == value;
    }
    friend bool operator==(const char* left, const UTF8String& right) {
        return left == right.Target;
    }
    friend bool operator==(const std::string& left, const UTF8String& right) {
        return left == right.Target;
    }
    bool operator!=(const UTF8String& value) const {
        return Target != value.Target;
    }
    bool operator!=(const char* value) const {
        return Target != value;
    }
    bool operator!=(const std::string& value) const {
        return Target != value;
    }
    friend bool operator!=(const char* left, const UTF8String& right) {
        return left != right.Target;
    }
    friend bool operator!=(const std::string& left, const UTF8String& right) {
        return left != right.Target;
    }
    bool operator<(const UTF8String& value) const {
        return Target < value.Target;
    }
    bool operator>(const UTF8String& value) const {
        return Target > value.Target;
    }
    friend std::ostream& operator<<(std::ostream& out, const UTF8String& value) {
        out << value.Target;
        return out;
    }
    static UTF8String Join(const std::vector<UTF8String>& values, const UTF8String& separator) {
        UTF8String result;
        for (size_t i = 0; i < values.size(); i++) {
            if (i != 0) {
                result.Append(separator);
            }
            result.Append(values[i]);
        }
        return result;
    }
    static std::vector<UTF8String> Vector(const UTF8String& value0) {
        std::vector<UTF8String> result;
        result.push_back(value0);
        return result;
    }
    static std::vector<UTF8String> Vector(const UTF8String& value0, const UTF8String& value1) {
        std::vector<UTF8String> result;
        result.push_back(value0);
        result.push_back(value1);
        return result;
    }
    static std::vector<UTF8String> Vector(const UTF8String& value0, const UTF8String& value1, const UTF8String& value2) {
        std::vector<UTF8String> result;
        result.push_back(value0);
        result.push_back(value1);
        result.push_back(value2);
        return result;
    }
    static std::vector<UTF8String> Vector(const UTF8String& value0, const UTF8String& value1, const UTF8String& value2, const UTF8String& value3) {
        std::vector<UTF8String> result;
        result.push_back(value0);
        result.push_back(value1);
        result.push_back(value2);
        result.push_back(value3);
        return result;
    }
    static std::vector<UTF8String> Vector(const UTF8String& value0, const UTF8String& value1, const UTF8String& value2, const UTF8String& value3, const UTF8String& value4) {
        std::vector<UTF8String> result;
        result.push_back(value0);
        result.push_back(value1);
        result.push_back(value2);
        result.push_back(value3);
        result.push_back(value4);
        return result;
    }
    static std::vector<UTF8String> Vector(const UTF8String& value0, const UTF8String& value1, const UTF8String& value2, const UTF8String& value3, const UTF8String& value4, const UTF8String& value5) {
        std::vector<UTF8String> result;
        result.push_back(value0);
        result.push_back(value1);
        result.push_back(value2);
        result.push_back(value3);
        result.push_back(value4);
        result.push_back(value5);
        return result;
    }
    static std::vector<UTF8String> Vector(const UTF8String& value0, const UTF8String& value1, const UTF8String& value2, const UTF8String& value3, const UTF8String& value4, const UTF8String& value5, const UTF8String& value6) {
        std::vector<UTF8String> result;
        result.push_back(value0);
        result.push_back(value1);
        result.push_back(value2);
        result.push_back(value3);
        result.push_back(value4);
        result.push_back(value5);
        result.push_back(value6);
        return result;
    }
    static std::vector<UTF8String> Vector(const UTF8String& value0, const UTF8String& value1, const UTF8String& value2, const UTF8String& value3, const UTF8String& value4, const UTF8String& value5, const UTF8String& value6, const UTF8String& value7) {
        std::vector<UTF8String> result;
        result.push_back(value0);
        result.push_back(value1);
        result.push_back(value2);
        result.push_back(value3);
        result.push_back(value4);
        result.push_back(value5);
        result.push_back(value6);
        result.push_back(value7);
        return result;
    }
    static std::vector<UTF8String> Vector(const UTF8String& value0, const UTF8String& value1, const UTF8String& value2, const UTF8String& value3, const UTF8String& value4, const UTF8String& value5, const UTF8String& value6, const UTF8String& value7, const UTF8String& value8) {
        std::vector<UTF8String> result;
        result.push_back(value0);
        result.push_back(value1);
        result.push_back(value2);
        result.push_back(value3);
        result.push_back(value4);
        result.push_back(value5);
        result.push_back(value6);
        result.push_back(value7);
        result.push_back(value8);
        return result;
    }
    static std::vector<UTF8String> Vector(const UTF8String& value0, const UTF8String& value1, const UTF8String& value2, const UTF8String& value3, const UTF8String& value4, const UTF8String& value5, const UTF8String& value6, const UTF8String& value7, const UTF8String& value8, const UTF8String& value9) {
        std::vector<UTF8String> result;
        result.push_back(value0);
        result.push_back(value1);
        result.push_back(value2);
        result.push_back(value3);
        result.push_back(value4);
        result.push_back(value5);
        result.push_back(value6);
        result.push_back(value7);
        result.push_back(value8);
        result.push_back(value9);
        return result;
    }
};
};
#endif