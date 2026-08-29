#include "RedUI/Input/Screen.h"
#include <exception>

using namespace RedUI;

float Input::Window::GetAspectRatio() const
{
	return (Size.Y / Size.X);
}

Input::Window Input::GetGameWindow()
{
	Window	res;

	res.Handle = FindWindowA("sgaWindow", "Red Dead Redemption 2");
	if (res.Handle == nullptr)
		throw (std::exception("Game window not found, what the fuck?"));
	GetClientRect(res.Handle, &res.Rect);
	res.Size = Math::Vec2(
		res.Rect.right - res.Rect.left,
		res.Rect.bottom - res.Rect.top
	);
	return (res);
}
