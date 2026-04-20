#pragma once
#include "Math/Vec2.h"

namespace RedUI
{
	// Updates all UI components. This must be called every frame.
	void	Update();

	// Data to be passed to every UIObject::RecursivelyUpdateAndDraw call to prevent calling natives for every object.
	struct		FrameState
	{
		bool		IsLeftMouseDown;
		bool		IsRightMouseDown;
		Math::Vec2	MousePosition;
	};
}
