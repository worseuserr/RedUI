#include "RedUI/Time/Time.h"

using namespace RedUI;

Time::Milliseconds Time::MsSinceEpoch()
{
	return (duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count());
}

Time::Microseconds Time::UsSinceEpoch()
{
	return (duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count());
}

Time::Nanoseconds Time::NsSinceEpoch()
{
	return (duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count());
}

Time::Seconds Time::SSinceEpoch()
{
	return (duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now().time_since_epoch()).count());
}

tm Time::Now()
{
	time_t				now;
	tm					current;

	now = time(nullptr);
	if (localtime_s(&current, &now) != 0)
		throw (std::exception());
	return (current);
}
