#include "RedUI/IO/Logger.h"
#include "RedUI/Time/Time.h"

using namespace RedUI;

IO::Logger::Logger(const char *filename, const bool overwriteIfExists)
	: Out(filename, overwriteIfExists) {}

IO::Logger::~Logger()
{
	Flush();
}

void IO::Logger::Write(const char *str, LL logLevel, const bool prependDatetime, const bool appendNewline)
{
	tm	time = Time::GetCurrentTime();

	Buffer << (prependDatetime ? std::format(
		"[{:02}/{:02}/{} {:02}:{:02}:{:02}] ",
		time.tm_mday,
		time.tm_mon + 1,
		time.tm_year + 1900,
		time.tm_hour,
		time.tm_min,
		time.tm_sec) : "") << LogLevelStrings[static_cast<int>(logLevel)] << str << (appendNewline ? "\n" : "");
	if (!UseBuffer || Buffer.str().size() > BufferSize)
		Flush();
}

void IO::Logger::Write(const std::string &str, const LL logLevel, const bool prependDatetime, const bool appendNewline)
{
	Write(str.c_str(), logLevel, prependDatetime, appendNewline);
}

void IO::Logger::Flush()
{
	if (Out.Open())
		Out << Buffer.str();
	Out.Close();
	Buffer.str("");
	Buffer.clear();
}
