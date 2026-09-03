#pragma once
#include "IO/Logger.h"

namespace RedUI
{
	class	Debug
	{
	public:
		static IO::Logger	*DLogger;

		Debug() = delete;
		static void			Log(const char *str, LL logLevel = LL::Info, bool prependDatetime = true, bool appendNewline = true);
		static void			Log(const std::string &str, LL logLevel = LL::Info, bool prependDatetime = true, bool appendNewline = true);
		// If fatal == true, stops the RedUI loop.
		static void			Error(const char *message, bool fatal = false);
		// If fatal == true, stops the RedUI loop.
		static void			Error(const std::string &message, bool fatal = false);
	};
}
