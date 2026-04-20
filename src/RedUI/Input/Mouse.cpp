#include "RedUI/Input/Mouse.h"

#include "RedUI/Input/Key.h"

using namespace RedUI;

Math::Vec2 Input::GetMousePosition()
{
	return (Math::Vec2(PAD::GET_CONTROL_NORMAL(0, INPUT_CURSOR_X), PAD::GET_CONTROL_NORMAL(0, INPUT_CURSOR_Y)));
}

bool Input::IsLeftMouseDown()
{
	return (IsKeyDown(Key::MouseLeft));
}

bool Input::IsRightMouseDown()
{
	return (IsKeyDown(Key::MouseRight));
}
