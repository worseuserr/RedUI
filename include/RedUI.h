#pragma once
#include "RedUI/UIObject.h"
// Expose these in RedUI.h
// ReSharper disable once CppUnusedIncludeDirective
#include "RedUI/Remove.h"
// ReSharper disable once CppUnusedIncludeDirective
#include "RedUI/Create.h"

namespace RedUI
{
	constexpr unsigned int	VERSION = 1;
	constexpr const char	*MOD_PAGE = "https://example.com";

	// Returns false if current RedUI version is below passed version.
	bool	CheckVersion(unsigned int version);
	// Shows an error message and returns false if RedUI version is below passed version.
	bool	RequireVersion(unsigned int version);
	// Force mouse cursor to show even while ingame.
	void	EnableCursor();
	// Disable forced cursor.
	void	ResetCursor();
	// Disable left and right clicks from registering ingame (shooting, aiming, etc).
	void	DisableMouseInputs();
	// Reallow ingame mouse inputs.
	void	ResetMouseInputs();
}
