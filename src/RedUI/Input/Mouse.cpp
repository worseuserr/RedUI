#include <windows.h>
#include "RedUI/Input/Mouse.h"
#include "RedUI/Input/Key.h"

using namespace RedUI;

Math::Vec2 Input::GetGameWindow(HWND& window, RECT &clientRect)
{
	window = FindWindowA("sgaWindow", "Red Dead Redemption 2");
	if (window == nullptr)
		return (Math::Vec2());
	GetClientRect(window, &clientRect);
	return (Math::Vec2(
		clientRect.right - clientRect.left,
		clientRect.bottom - clientRect.top
		));
}

// Uses windows api to get mouse position because the shitty ass native doesn't work while not in a menu.
Math::Vec2 Input::GetMousePosition()
{
	POINT		cursorPos;
	HWND		window;
	Math::Vec2	size;
	RECT		rect;

	size = GetGameWindow(window, rect);
	if (window == nullptr || size.X == 0 || size.Y == 0)
		return (Math::Vec2());
	GetCursorPos(&cursorPos);
	ScreenToClient(window, &cursorPos);
	return (Math::Vec2(
		static_cast<float>(cursorPos.x) / size.X,
		static_cast<float>(cursorPos.y) / size.Y
		));
}

void Input::SetMousePosition(const Math::Vec2 &position)
{
	HWND		window;
	Math::Vec2	size;
	RECT		rect;
	POINT		screenPos;

	size = GetGameWindow(window, rect);
	if (window == nullptr || size.X == 0 || size.Y == 0)
		return ;
	screenPos = POINT(position.X * size.X, position.Y * size.Y);
	ClientToScreen(window, &screenPos);
	SetCursorPos(screenPos.x, screenPos.y);
}

bool Input::IsLeftMouseDown()
{
	return (IsKeyDown(Key::MouseLeft));
}

bool Input::IsRightMouseDown()
{
	return (IsKeyDown(Key::MouseRight));
}

Input::MouseChangedEvent<void> Input::Events::OnLeftMouseDown;
Input::MouseChangedEvent<void> Input::Events::OnLeftMouseUp;
Input::MouseChangedEvent<void> Input::Events::OnRightMouseDown;
Input::MouseChangedEvent<void> Input::Events::OnRightMouseUp;
