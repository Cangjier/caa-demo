
#ifndef __TIDY_TIMESPAN_H__
#define __TIDY_TIMESPAN_H__
#include "Tidy_Macro.h"
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
	class  TimeSpan
	{
	public:
#if NOTSUPPORT_CHRONO
		TimeSpan(long long target);
#else
		TimeSpan(std::chrono::system_clock::duration target);
#endif

		TimeSpan(double hour, double minute, double second);

		TimeSpan(double day, double hour, double minute, double second);

#if NOTSUPPORT_CHRONO
		long long Target;
#else
		std::chrono::system_clock::duration Target;
#endif

		double TotalSeconds();

		double TotalMilliseconds();

		double TotalMicroseconds();
        
		long long Ticks();
        
		UTF8String ToString();

	private:
    
		static void Join(UTF8String &result, double &total, long long limit, UTF8String unit);
	};
}
#endif