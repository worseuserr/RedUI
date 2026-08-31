#pragma once
#include <fstream>
#include <string>

namespace RedUI::IO
{
	class	File
	{
		std::fstream	Stream;
		std::string		Filename;

	public:
		File(const char *filename, bool replaceIfExists = false);

		// Returns IsOpen().
		bool        Open(std::ios_base::openmode mode = std::ios_base::app | std::ios_base::out);
		void        Close();
		void        Write(const char *str);
		std::string	Read() const;
		bool        IsOpen() const;
		static bool Exists(const char *filename);

		template	<typename T>
		File		&operator<<(const T& data)
		{
			Stream << data;
			return (*this);
		}
		template	<typename T>
		File		&operator>>(T& value)
		{
			Stream >> value;
			return (*this);
		}
	};
}
