#include "RedUI/IO/File.h"
#include <filesystem>

using namespace RedUI;


IO::File::File(const char *filename, const bool replaceIfExists)
	: Filename(filename)
{
	Stream.open(filename, std::ios_base::out | (replaceIfExists ? std::ios_base::trunc : std::ios_base::app));
	Stream.close();
}

bool IO::File::Open(const std::ios_base::openmode mode)
{
	Stream.open(Filename, mode);
	return (IsOpen());
}

void IO::File::Close()
{
	Stream.close();
}

void IO::File::Write(const char *str)
{
	Stream << str;
}

std::string IO::File::Read() const
{
	std::stringstream	buff;

	buff << Stream.rdbuf();
	return (std::string(buff.str()));
}

bool IO::File::IsOpen() const
{
	return (Stream.is_open());
}

bool IO::File::Exists(const char *filename)
{
	return (std::filesystem::exists(filename));
}
