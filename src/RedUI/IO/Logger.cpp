#include "RedUI/IO/Logger.h"
#include "RedUI/Time/Time.h"
#include "RedUI/Debug.h"
#include <windows.h>

using namespace RedUI;

IO::Logger::Logger(const char *filename, const char *modname, const bool overwriteIfExists)
	: Out(filename, overwriteIfExists), Name(modname) {}

IO::Logger::~Logger()
{
	Flush();
}

void IO::Logger::Write(const char *str, LL logLevel, const bool prependDatetime, const bool appendNewline)
{
	tm	time = Time::Now();

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

void IO::Logger::Error(const char *message, const bool fatal)
{
	std::string	str = std::format(
		"{} error occurred in {}! Error message: \'{}\'.{}",
		fatal ? "A fatal" : "An", Name, message, fatal ? std::format(" {} shutting down.", Name) : "");

	Write(std::format("{}\nStack trace:\n{}", str, Debug::GetStacktrace()), LL::Error, true, false);
	if (fatal)
		MessageBox(
			nullptr,
			str.c_str(),
			(Name + " error!").c_str(),
			MB_ICONERROR | MB_OK
		);
}

void IO::Logger::Error(const std::string &message, const bool fatal)
{
	Error(message.c_str(), fatal);
}

void IO::Logger::Flush()
{
	if (Out.Open())
		Out << Buffer.str();
	Out.Close();
	Buffer.str("");
	Buffer.clear();
}
