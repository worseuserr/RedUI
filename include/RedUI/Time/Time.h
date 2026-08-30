#pragma once
#include <chrono>

namespace RedUI::Time
{
	using	Milliseconds = unsigned long long;
	using	Microseconds = unsigned long long;
	using	Nanoseconds = unsigned long long;
	using	Seconds = unsigned long long;

	Milliseconds	MsSinceEpoch();
	Microseconds	UsSinceEpoch();
	Nanoseconds		NsSinceEpoch();
	Seconds			SSinceEpoch();

	tm	GetCurrentTime();

	// TODO: add a method for delaying functions
}
