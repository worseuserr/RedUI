/*
THIS FILE IS A MODIFIED PART OF RDR 2 SCRIPT HOOK SDK
				http://dev-c.com
			(C) Alexander Blade 2019
*/

#include <Sdk/main.h>
#include "RedUI/Runtime.h"

constexpr int	KEYS_SIZE = 255;

struct {
	DWORD	time;
	BOOL	isWithAlt;
	BOOL	wasDownBefore;
	BOOL	isUpNow;
} keyStates[KEYS_SIZE];

void OnKeyboardMessage(const DWORD key, WORD repeats, BYTE scanCode, BOOL isExtended, const BOOL isWithAlt, const BOOL wasDownBefore, const BOOL isUpNow)
{
	if (key < KEYS_SIZE)
	{
		keyStates[key].time = GetTickCount();
		keyStates[key].isWithAlt = isWithAlt;
		keyStates[key].wasDownBefore = wasDownBefore;
		keyStates[key].isUpNow = isUpNow;
	}
}

BOOL APIENTRY DllMain(const HMODULE hInstance, const DWORD reason, LPVOID lpReserved)
{
	switch (reason)
	{
		case (DLL_PROCESS_ATTACH):
			scriptRegister(hInstance, RedUI::Runtime::RedUILoop);
			keyboardHandlerRegister(OnKeyboardMessage);
			break;
		case (DLL_PROCESS_DETACH):
			scriptUnregister(hInstance);
			keyboardHandlerUnregister(OnKeyboardMessage);
			break;
		default: ;
	}
	return (TRUE);
}
