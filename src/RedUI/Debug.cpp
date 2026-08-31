#include "RedUI/Debug.h"

using namespace RedUI;

IO::Logger *Debug::DLogger = nullptr;

void Debug::Log(const char *str, const LL logLevel, const bool prependDatetime, const bool appendNewline)
{
	DLogger->Write(str, logLevel, prependDatetime, appendNewline);
}

void Debug::Log(const std::string &str, const LL logLevel, const bool prependDatetime, const bool appendNewline)
{
	DLogger->Write(str, logLevel, prependDatetime, appendNewline);
}
