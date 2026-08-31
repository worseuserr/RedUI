#pragma once
#include <sstream>
#include "File.h"

namespace RedUI
{
	enum class	LogLevel
	{
		Info,
		Warn,
		Error,
		Debug
	};

	constexpr const char	*LogLevelStrings[] =
	{
		"[INFO ] ",
		"[WARN ] ",
		"[ERROR] ",
		"[DEBUG] "
	};

	// Shorthand for LogLevel to make Write calls more concise.
	using LL = LogLevel;
}

namespace RedUI::IO
{
	class Logger
	{
		File				Out;
		std::stringstream	Buffer;

	public:
		bool			UseBuffer = false;
		unsigned int	BufferSize = 2048; // Size in characters.

		Logger(const char *filename, bool overwriteIfExists = true);
		~Logger();
		void	Write(const char *str, LL logLevel = LL::Info, bool prependDatetime = true, bool appendNewline = true);
		void	Flush();
	};
}
