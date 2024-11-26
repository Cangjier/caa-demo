
#include "Tidy_DateTime.h"
#include "Tidy_TimeSpan.h"
using namespace Tidy;

long long DateTime::GetMillisecondsSinceMidnight()
{
#if NOTSUPPORT_CHRONO
	SYSTEMTIME st;
	GetLocalTime(&st);
	return st.wHour * 60 * 60 * 1000 + st.wMinute * 60 * 1000 + st.wSecond * 1000 + st.wMilliseconds;
#else
	auto now = std::chrono::system_clock::now();
	auto current_date = std::chrono::system_clock::to_time_t(now);
	struct std::tm* time_info = std::localtime(&current_date);
	time_info->tm_hour = 0;
	time_info->tm_min = 0;
	time_info->tm_sec = 0;
	auto midnight = std::chrono::system_clock::from_time_t(std::mktime(time_info));
	auto milliseconds_since_midnight = std::chrono::duration_cast<std::chrono::milliseconds>(now - midnight).count();
	return milliseconds_since_midnight;
#endif
}

DateTime DateTime::AddMilliseconds(double value)
{
#if NOTSUPPORT_CHRONO
	return Target + (long long)(value / 1000);
#else
	return Target + std::chrono::system_clock::time_point::duration((long long)(value * (long long)10000));
#endif
}

DateTime DateTime::AddSeconds(double value)
{
#if NOTSUPPORT_CHRONO
	return Target + (long long)value;
#else
	return Target + std::chrono::system_clock::time_point::duration((long long)(value * (long long)10000000));
#endif
	
}

DateTime DateTime::AddMinutes(double value)
{
#if NOTSUPPORT_CHRONO
	return Target + (long long)(value * 60);
#else
	return Target + std::chrono::system_clock::time_point::duration((long long)(value * (long long)60 * 10000000));
#endif
	
}

DateTime DateTime::AddHours(double value)
{
#if NOTSUPPORT_CHRONO
	return Target + (long long)(value * 60 * 60);
#else
	return Target + std::chrono::system_clock::time_point::duration((long long)(value * (long long)60 * 60 * 10000000));
#endif
}

DateTime DateTime::AddDays(double value)
{
#if NOTSUPPORT_CHRONO
	return Target + (long long)(value * 24 * 60 * 60);
#else
	return Target + std::chrono::system_clock::time_point::duration((long long)(value * (long long)24 * 60 * 60 * 10000000));
#endif
}

DateTime DateTime::AddWeeks(double value)
{
#if NOTSUPPORT_CHRONO
	return Target + (long long)(value * 7 * 24 * 60 * 60);
#else
	return Target + std::chrono::system_clock::time_point::duration((long long)(value * (long long)7 * 24 * 60 * 60 * 10000000));
#endif
}

UTF8String DateTime::ToString(UTF8String format)
{
	DateTimeInfomation Info = Infomation();
	return format.
		Replace("yyyy", Info.Year).
		Replace("MM", UTF8String(Info.Month).FillStart(2, "0")).
		Replace("dd", UTF8String(Info.Day).FillStart(2, "0")).
		Replace("HH", UTF8String(Info.Hour).FillStart(2, "0")).
		Replace("mm", UTF8String(Info.Minute).FillStart(2, "0")).
		Replace("ss", UTF8String(Info.Second).FillStart(2, "0"));
}

TimeSpan DateTime::operator-(const DateTime& right)
{
	return Target - right.Target;
}

DateTime DateTime::operator+(const TimeSpan& right)
{
	return Target + right.Target;
}
