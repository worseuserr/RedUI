#pragma once

namespace RedUI
{
	constexpr unsigned int	Version = 1;
	constexpr const char	*ModPage = "https://example.com";

	class	Menu
	{
	public:
		Menu();
	};

	// Returns false if current RedUI version is below passed version.
	bool	CheckVersion(unsigned int version);
	// Shows an error message and returns false if RedUI version is below passed version.
	bool	RequireVersion(unsigned int version);
}
