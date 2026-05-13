#pragma once
// Includes to expose in RedUI.h
// ReSharper disable once CppUnusedIncludeDirective
#include "RedUI/Remove.h"
// ReSharper disable once CppUnusedIncludeDirective
#include "RedUI/Create.h"
// ReSharper disable once CppUnusedIncludeDirective
#include "RedUI/Focus.h"

namespace RedUI
{
	constexpr unsigned int	VERSION = 1;
	constexpr const char	*MOD_PAGE = "https://example.com";

	// Returns false if current RedUI version is below passed version.
	bool	CheckVersion(unsigned int version);
	// Shows an error message and returns false if RedUI version is below passed version.
	bool	RequireVersion(unsigned int version);
}
