#include "Tidy_TimeSpan.h"
using namespace Tidy;
#if NOTSUPPORT_CHRONO
TimeSpan::TimeSpan(long long target)
{
	this->Target = target;
}
#else
TimeSpan::TimeSpan(std::chrono::system_clock::duration target)
{
    this->Target = target;
}
#endif

TimeSpan::TimeSpan(double hour, double minute, double second)
{
#if NOTSUPPORT_CHRONO
	this->Target = (long long)(
		hour * 60 * 60 +
		minute * 60 +
		second
    );
#else
    this->Target = std::chrono::system_clock::duration((long long)(
        hour * 60 * 60 * 1000 * 10000 +
        minute * 60 * 1000 * 10000 +
        second * 1000 * 10000
        ));
#endif
}

TimeSpan::TimeSpan(double day, double hour, double minute, double second)
{
#if NOTSUPPORT_CHRONO
	this->Target = (long long)(
		day * 24 * 60 * 60 +
		hour * 60 * 60 +
		minute * 60 +
		second
		);
#else
    this->Target = std::chrono::system_clock::duration((long long)(
        day * 24 * 60 * 60 * 1000 * 10000 +
        hour * 60 * 60 * 1000 * 10000 +
        minute * 60 * 1000 * 10000 +
        second * 1000 * 10000
        ));
#endif
}

double TimeSpan::TotalSeconds()
{
#if NOTSUPPORT_CHRONO
	return Target;
#else
    return Target.count() / 10000000.0;
#endif
}

double TimeSpan::TotalMilliseconds()
{
#if NOTSUPPORT_CHRONO
    return Target * 1000;
#else
    return Target.count() / 10000.0;
#endif
}

double TimeSpan::TotalMicroseconds()
{
#if NOTSUPPORT_CHRONO
    return Target * 1000 * 1000;
#else
	return Target.count() / 10.0;
#endif
}

long long TimeSpan::Ticks()
{
#if NOTSUPPORT_CHRONO
	return Target;
#else
    return Target.count();
#endif
}

UTF8String TimeSpan::ToString()
{
    static long long yearLimit = (long long)365 * 24 * 60 * 60 * 1000;
    static long long monthLimit = (long long)30 * 24 * 60 * 60 * 1000;
    static long long dayLimit = (long long)24 * 60 * 60 * 1000;
    static long long hourLimit = (long long)60 * 60 * 1000;
    static long long minuteLimit = (long long)60 * 1000;
    static long long secondLimit = (long long)1000;
    double total = TotalMilliseconds();
    UTF8String result;
    Join(result, total, yearLimit, LocaleString("Year"));
    Join(result, total, monthLimit, LocaleString("Month"));
    Join(result, total, dayLimit, LocaleString("Day"));
    Join(result, total, hourLimit, LocaleString("h"));
    Join(result, total, minuteLimit, LocaleString("m"));
    Join(result, total, secondLimit, LocaleString("s"));
    if (total > 0)
    {
        result.Append(total);
        result.Append(LocaleString("ms"));
    }
    return result;
}

void TimeSpan::Join(UTF8String& result, double& total, long long limit, UTF8String unit)
{
    if (total > limit)
    {
        int count = (int)(total / limit);
        result.Append(count);
        result.Append(unit);
        total = total - count * limit;
    }
}
