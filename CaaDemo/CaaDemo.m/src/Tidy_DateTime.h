
#ifndef __TIDY_DATETIME_H__
#define __TIDY_DATETIME_H__
#include "Tidy_Macro.h"
#include <ctime>
#include "Tidy_UTF8String.h"
#ifndef NOTSUPPORT_CHRONO
#if defined(_MSC_VER) && _MSC_VER <= 1800
#define NOTSUPPORT_CHRONO 1

#else
#define NOTSUPPORT_CHRONO 0
#include <chrono>
#endif
#endif
namespace Tidy
{
	class  DateTimeInfomation
	{
	public:
		DateTimeInfomation()
		{
			Year = 0;
			Month = 0;
			Day = 0;
			Week = 0;
			Hour = 0;
			Minute = 0;
			Second = 0;
		}
		int Year;
		int Month;
		int Day;
		int Week;
		int Hour;
		int Minute;
		int Second;
	};

	class TimeSpan;
	class  DateTime
	{
	public:
		DateTime()
		{
#if NOTSUPPORT_CHRONO
			Target = time_t();
#else
			Target = std::chrono::system_clock::now();
#endif
		}

		DateTime(time_t target)
		{
#if NOTSUPPORT_CHRONO
			this->Target = target;
#else
			this->Target = std::chrono::system_clock::from_time_t(target);
#endif
		}

#if NOTSUPPORT_CHRONO
#else
		DateTime(std::chrono::system_clock::time_point target)
		{
			this->Target = target;
		}
#endif
		

		DateTime(int year, int month, int day, int hour, int minute, int second)
		{
			std::time_t timeLong;
			std::time(&timeLong);
			std::tm localTime = *std::localtime(&timeLong);
			localTime.tm_year = year - 1900;
			localTime.tm_mon = month - 1;
			localTime.tm_mday = day;
			localTime.tm_hour = hour;
			localTime.tm_min = minute;
			localTime.tm_sec = second;
#if NOTSUPPORT_CHRONO
			this->Target = std::mktime(&localTime);
#else
			this->Target = std::chrono::time_point<std::chrono::system_clock>(std::chrono::duration<long long, std::ratio<1, 1>>(std::mktime(&localTime)));
#endif	
		}

#if NOTSUPPORT_CHRONO
		std::time_t Target;
#else
		std::chrono::system_clock::time_point Target;
#endif

		std::time_t time_t()
		{
#if NOTSUPPORT_CHRONO
			return Target;
#else
			return std::chrono::system_clock::to_time_t(Target);
#endif
		}

		std::tm LocalTime()
		{
			std::time_t temp = time_t();
			return *std::localtime(&temp);
		}

		std::tm UTCTime()
		{
			std::time_t temp = time_t();
			return *std::gmtime(&temp);
		}

		static DateTime Now()
		{
#if NOTSUPPORT_CHRONO
			return DateTime(std::time(SUPPORT_NULLPTR));
#else
			return DateTime(std::chrono::system_clock::now());
#endif
		}

		static long long GetMillisecondsSinceMidnight();

		DateTimeInfomation Infomation()
		{
			DateTimeInfomation result;
			std::tm time = LocalTime();
			result.Year = 1900 + time.tm_year;
			result.Month = 1 + time.tm_mon;
			result.Day = time.tm_mday;
			result.Week = time.tm_wday;
			result.Hour = time.tm_hour;
			result.Minute = time.tm_min;
			result.Second = time.tm_sec;
			return result;
		}

		int Year()
		{
			return Infomation().Year;
		}

		int Month()
		{
			return Infomation().Month;
		}

		int Day()
		{
			return Infomation().Day;
		}

		int Week()
		{
			return Infomation().Week;
		}

		int Hour()
		{
			return Infomation().Hour;
		}

		int Minute()
		{
			return Infomation().Minute;
		}

		int Second()
		{
			return Infomation().Second;
		}

		DateTime AddMilliseconds(double value);

		DateTime AddSeconds(double value);

		DateTime AddMinutes(double value);

		DateTime AddHours(double value);

		DateTime AddDays(double value);

		DateTime AddWeeks(double value);

		UTF8String ToString(UTF8String format = "yyyy/MM/dd HH:mm:ss");

		TimeSpan operator-(const DateTime &right);

		DateTime operator+(const TimeSpan &right);
	};
}
#endif