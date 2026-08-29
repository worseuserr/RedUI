#include <windows.h>
#include "RedUI/Input/Mouse.h"
#include "RedUI/Input/Key.h"
#include "RedUI/Input/Screen.h"

using namespace RedUI;

// Uses windows api to get mouse position because the shitty ass native doesn't work while not in a menu.
Math::Vec2 Input::GetMousePosition()
{
	Window	window = GetGameWindow();
	POINT	cursorPos;

	GetCursorPos(&cursorPos);
	ScreenToClient(window.Handle, &cursorPos);
	return (Math::Vec2(
		static_cast<float>(cursorPos.x) / window.Size.X,
		static_cast<float>(cursorPos.y) / window.Size.Y
		));
}

void Input::SetMousePosition(const Math::Vec2 &position)
{
	Window	window = GetGameWindow();
	POINT	screenPos;

	screenPos = POINT(position.X * window.Size.X, position.Y * window.Size.Y);
	ClientToScreen(window.Handle, &screenPos);
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

void Input::MouseEvents::Tick(FrameState &state)
{
	static bool	wasLeftMouseDown = false;
	static bool	wasRightMouseDown = false;
	bool		isLeftMouseDown;
	bool		isRightMouseDown;

	isLeftMouseDown = IsLeftMouseDown();
	isRightMouseDown = IsRightMouseDown();
	if (isLeftMouseDown != wasLeftMouseDown)
	{
		if (isLeftMouseDown)
			OnLeftMouseDown.Invoke(nullptr, { wasLeftMouseDown, isLeftMouseDown });
		else
			OnLeftMouseUp.Invoke(nullptr, { wasLeftMouseDown, isLeftMouseDown });
	}
	if (isRightMouseDown != wasRightMouseDown)
	{
		if (isRightMouseDown)
			OnRightMouseDown.Invoke(nullptr, { wasRightMouseDown, isRightMouseDown });
		else
			OnRightMouseUp.Invoke(nullptr, { wasRightMouseDown, isRightMouseDown });
	}
	state.IsLeftMouseClicked = !wasLeftMouseDown && isLeftMouseDown;
	state.IsRightMouseClicked = !wasRightMouseDown && isRightMouseDown;
	wasLeftMouseDown = isLeftMouseDown;
	wasRightMouseDown = isRightMouseDown;
}

Input::MouseChangedEvent<void> Input::MouseEvents::OnLeftMouseDown;
Input::MouseChangedEvent<void> Input::MouseEvents::OnLeftMouseUp;
Input::MouseChangedEvent<void> Input::MouseEvents::OnRightMouseDown;
Input::MouseChangedEvent<void> Input::MouseEvents::OnRightMouseUp;
