#include "RedUI/Debug.h"
#include "RedUI/Runtime.h"
#include <dbghelp.h>
#include <filesystem>
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
	DLogger->Error(message, fatal);
	if (fatal)
		Runtime::UpdateLoopEnabled = false;
}

void Debug::Error(const std::string &message, const bool fatal)
{
	Error(message.c_str(), fatal);
}

class	TraceContext
{
public:
	SYMBOL_INFO		*Symbol;
	HANDLE			Process;
	IMAGEHLP_LINE64	Line{};
	DWORD			Displacement;
	WORD			FrameCount;

	TraceContext(void **frames, char *symbolBuffer, const unsigned long framesToSkip)
	{
		Displacement = 0;
		Line.SizeOfStruct = sizeof(Line);
		Process = GetCurrentProcess();
		SymInitialize(Process, nullptr, TRUE);
		Symbol = reinterpret_cast<SYMBOL_INFO *>(symbolBuffer);
		Symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
		Symbol->MaxNameLen = MAX_SYM_NAME;
		FrameCount = CaptureStackBackTrace(framesToSkip, 32, frames, nullptr);
	}
};

std::string GetSymLine(TraceContext &ctx)
{
	std::filesystem::path	path;

	if (SymGetLineFromAddr64(ctx.Process, ctx.Symbol->Address, &ctx.Displacement, &ctx.Line))
	{
		path = ctx.Line.FileName;
		return (std::format(" [{}:{}]\n", std::format("{}\\{}", path.parent_path().filename().string(), path.filename().string()), ctx.Line.LineNumber));
	}
	return ("\n");
}

std::string Debug::GetStacktrace(const unsigned long framesToSkip)
{
	char				symbolBuffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME];
	void				*frames[32];
	std::string			res;
	unsigned short		i;
	TraceContext		ctx = TraceContext(frames, symbolBuffer, framesToSkip);

	for (i=0; i < ctx.FrameCount; ++i)
	{
		if (SymFromAddr(ctx.Process, reinterpret_cast<DWORD64>(frames[i]), nullptr, ctx.Symbol))
		{
			res += std::format("   #{}: at (0x{:016X}, 0x{:016X}) | {}", i,
				ctx.Symbol->Address, ctx.Symbol->Address - ctx.Symbol->ModBase, ctx.Symbol->Name);
			res += GetSymLine(ctx);
		}
	}
	SymCleanup(ctx.Process);
	return (res);
}
