#include "Tidy_ID.h"
#include <iostream>
#include <random>
#include "Tidy_DateTime.h"
#ifdef _MSC_VER
#include <iomanip>
#include <windows.h>
#else
#include <uuid/uuid.h>
#endif // _MSC_VER

namespace Tidy {
	UTF8String ID::GenerateID(const UTF8String& base, int length)
	{
#if _MSC_VER <= 1500
		UTF8String result;
		for (int i = 0; i < length; i++) {
			result.Append(base[rand() % base.Length()]);
		}
		return result;
#else

		static std::mt19937 gen(std::random_device{}());
		std::uniform_int_distribution<> dist(0, base.Length() - 1);
		UTF8String result;
		for (int i = 0; i < length; i++) {
			result.Append(base[dist(gen)]);
		}
		return result;
#endif
		
	}

	UTF8String ID::GenerateID(int length)
	{
		static UTF8String base = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		return GenerateID(base,length);
	}

	UTF8String ID::ConvertToID(SUPPORT_INT64 value)
	{
		static UTF8String base = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		return UTF8String(value,base);
	}

	UTF8String ID::GeneratePathName()
	{
		return GenerateID(4);
	}

	UTF8String ID::GenerateGUID()
	{
#ifdef _MSC_VER
		GUID guid;
		CoCreateGuid(&guid);

		std::stringstream ss;
		ss << std::hex
			<< std::setfill('0') << std::setw(8) << guid.Data1
			<< "-"
			<< std::setfill('0') << std::setw(4) << guid.Data2
			<< "-"
			<< std::setfill('0') << std::setw(4) << guid.Data3
			<< "-"
			<< std::setfill('0') << std::setw(2);
		for (int i = 0; i < 8; i++) {
			ss << std::hex << static_cast<int>(guid.Data4[i]);
		}

		return ss.str();
#else
		uuid_t uuid;
		uuid_generate(uuid);

		char uuid_str[37];
		uuid_unparse(uuid, uuid_str);

		return uuid_str;
#endif
	}
}

