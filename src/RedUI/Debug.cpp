#include "RedUI/Debug.h"
#include "RedUI/Runtime.h"
#include <dbghelp.h>
#include <format>

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

void Debug::Error(const char *message, const bool fatal)
{
	std::string	str = std::format("{}rror! Message: \"{}\".{}", fatal ? "Fatal e" : "E", message, fatal ? " RedUI shutting down." : "");

	DLogger->Write(str, LL::Error);
	MessageBox(
		nullptr,
		str.c_str(),
		"RedUI error!",
		MB_ICONERROR | MB_OK
	);
	if (fatal)
		Runtime::UpdateLoopEnabled = false;
}

void Debug::Error(const std::string &message, const bool fatal)
{
	Error(message.c_str(), fatal);
}
