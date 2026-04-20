#include <windows.h>
#include "RedUI/Input/Mouse.h"
#include "RedUI/Input/Key.h"

using namespace RedUI;

// Uses windows api to get mouse position because the shitty ass native doesn't work while not in a menu.
// This can probably be optimized. TODO: optimize
Math::Vec2 Input::GetMousePosition()
{
	POINT		cursorPos;
	HWND		gameWindow;
	int			windowWidth;
	int			windowHeight;
	RECT		clientRect;

	gameWindow = FindWindowA("sgaWindow", "Red Dead Redemption 2");
	if (gameWindow == nullptr)
		return (Math::Vec2());
	GetClientRect(gameWindow, &clientRect);
	windowHeight = clientRect.bottom - clientRect.top;
	windowWidth = clientRect.right - clientRect.left;
	if (windowWidth == 0 || windowHeight == 0)
		return (Math::Vec2());
	GetCursorPos(&cursorPos);
	ScreenToClient(gameWindow, &cursorPos);
	return (Math::Vec2(static_cast<float>(cursorPos.x) / windowWidth, static_cast<float>(cursorPos.y) / windowHeight));
}

bool Input::IsLeftMouseDown()
{
	return (IsKeyDown(Key::MouseLeft));
}

bool Input::IsRightMouseDown()
{
	return (IsKeyDown(Key::MouseRight));
}
