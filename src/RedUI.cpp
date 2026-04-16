#include <iostream>
#include <windows.h>
#include "RedUI.h"

RedUI::Menu::Menu()
{
}

bool RedUI::CheckVersion(const unsigned int version)
{
	// Debug code for now.
	MessageBox(
		nullptr,
		version >= Version ? "valid version" : "invalid version",
		"Works",
		MB_ICONINFORMATION | MB_OK
	);
	return (version >= Version);
}

bool RedUI::RequireVersion(const unsigned int version)
{
	int	res;

	if (CheckVersion(version))
		return (true);
	res = MessageBox(
		nullptr,
		"Your RedUI version is too outdated for one or more of your mods. Would you like to open the RedUI mod page?",
		"RedUI version mismatch!",
		MB_ICONERROR | MB_YESNO
	);
	if (res == IDYES)
		ShellExecute(
			nullptr,
			"open",
			ModPage,
			nullptr,
			nullptr,
			SW_SHOWNORMAL
		);
	return (false);
}
