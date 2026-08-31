#pragma once
#include "IO/Logger.h"

namespace RedUI::Debug
{
	extern IO::Logger	*DLogger;
	void				Log(const char *str, LL logLevel = LL::Info, bool prependDatetime = true, bool appendNewline = true);
	void				Log(const std::string &str, LL logLevel = LL::Info, bool prependDatetime = true, bool appendNewline = true);
}
