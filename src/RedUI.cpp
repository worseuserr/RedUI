#include <iostream>
#include <windows.h>
#include "RedUI.h"

bool RedUI::CheckVersion(const unsigned int version)
{
	return (VERSION >= version);
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
			MOD_PAGE,
			nullptr,
			nullptr,
			SW_SHOWNORMAL
		);
	return (false);
}
