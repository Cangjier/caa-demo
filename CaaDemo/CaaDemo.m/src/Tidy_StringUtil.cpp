#include "Tidy_StringUtil.h"
#ifdef _MSC_VER
#include "windows.h"
#elif __linux__
#include <iostream>
#include <string>
#include <cwchar>
#include <iconv.h>
#endif
using namespace Tidy;
unsigned int StringUtil::GetLocale() {
#ifdef _MSC_VER
    return GetACP();
#elif __linux__
    return 65001;
#endif
}
std::string StringUtil::To(const std::string &value, unsigned int fromCodePage, unsigned int toCodePage) {
#ifdef _MSC_VER
	int length = MultiByteToWideChar(fromCodePage, 0, value.c_str(), -1, NULL, 0);
	wchar_t* wchars = new wchar_t[length + 1];
	memset(wchars, 0, length * 2 + 2);
	MultiByteToWideChar(fromCodePage, 0, value.c_str(), -1, wchars, length);
	length = WideCharToMultiByte(toCodePage, 0, wchars, -1, NULL, 0, NULL, NULL);
	char* str = new char[length + 1];
	memset(str, 0, length + 1);
	WideCharToMultiByte(toCodePage, 0, wchars, -1, str, length, NULL, NULL);
	std::string strTemp(str);
	if (wchars) delete[] wchars;
	if (str) delete[] str;
	return strTemp;
#else
	std::string result;

	iconv_t converter = iconv_open(std::to_string(toCodePage).c_str(), std::to_string(fromCodePage).c_str());

	if (converter == (iconv_t)-1) {
		std::cout << "Failed to open converter." << std::endl;
		return result;
	}

	size_t inBytesLeft = value.size();
	size_t outBytesLeft = value.size() * 4;

	char* inBuf = const_cast<char*>(value.data());
	char* outBuf = new char[outBytesLeft];
	char* outBufStart = outBuf;

	if (iconv(converter, &inBuf, &inBytesLeft, &outBuf, &outBytesLeft) == (size_t)-1) {
		std::cout << "Failed to convert the string." << std::endl;
	}
	else {
		result.assign(outBufStart, outBytesLeft - outBytesLeft);
		std::cout << "Conversion successful." << std::endl;
	}

	delete[] outBufStart;
	iconv_close(converter);

	return result;
#endif
}
std::string StringUtil::To(const wchar_t *value, unsigned int toCodePage) {
#ifdef _MSC_VER
	int length = WideCharToMultiByte(toCodePage, 0, value, -1, SUPPORT_NULLPTR, 0, SUPPORT_NULLPTR, SUPPORT_NULLPTR);
	if (length == 0) {
		return std::string();
	}
	std::string result(length - 1, '\0');
	WideCharToMultiByte(toCodePage, 0, value, -1, &result[0], length, SUPPORT_NULLPTR, SUPPORT_NULLPTR);
	return result;
#elif __linux__
	std::string result;
	iconv_t conv = iconv_open(std::to_string(toCodePage).c_str(), "wchar_t");
	if (conv == (iconv_t)-1) {
		return result;
	}
	size_t inSize = wcslen(value) * sizeof(wchar_t);
	size_t inBytesLeft = inSize;
    
	size_t outSize = inSize * 2;
	size_t outBytesLeft = outSize;
    
	char* outBuffer = new char[outSize];
	char* outPtr = outBuffer;

	const char* inPtr = reinterpret_cast<const char*>(value);
	if (iconv(conv, &inPtr, &inBytesLeft, &outPtr, &outBytesLeft) == (size_t)-1) {
    
		delete[] outBuffer;
		iconv_close(conv);
		return result;
	}
    
	result.assign(outBuffer, outSize - outBytesLeft);

	delete[] outBuffer;
	iconv_close(conv);

	return result;
#else
	return "";
#endif
}
#if SUPPORT_STD_WSTRING
std::wstring StringUtil::To(const std::string &value, unsigned int fromCodePage) {
        int length = MultiByteToWideChar(fromCodePage, 0, value.c_str(), -1, NULL, 0);
if (length == 0)
{
	return L"";
}

std::wstring result(length - 1, L'\0');
if (MultiByteToWideChar(fromCodePage, 0, value.c_str(), -1, &result[0], length) == 0)
{
	return L"";
}

return result;
}
#endif