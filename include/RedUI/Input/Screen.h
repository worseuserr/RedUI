#pragma once
#include "RedUI/Math/Vec2.h"

namespace RedUI::Input
{
	class	Window
	{
	public:
		HWND		Handle;
		RECT		Rect;
		Math::Vec2	Size;

		float		GetAspectRatio() const;
	};

	Window	GetGameWindow();
}
