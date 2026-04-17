#pragma once

#include <chrono>

namespace RedUI::Time
{
	using	Milliseconds = unsigned long long;
	using	Microseconds = unsigned long long;
	using	Nanoseconds = unsigned long long;
	using	Seconds = unsigned long long;

	inline Milliseconds	MsSinceEpoch()
	{
		return (duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count());
	}

	inline Microseconds	UsSinceEpoch()
	{
		return (duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count());
	}

	inline Nanoseconds	NsSinceEpoch()
	{
		return (duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count());
	}

	inline Seconds		SSinceEpoch()
	{
		return (duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now().time_since_epoch()).count());
	}
}
