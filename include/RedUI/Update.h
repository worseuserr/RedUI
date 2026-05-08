#pragma once
#include "Math/Vec2.h"

namespace RedUI
{
	// Updates all UI components. This must be called every frame.
	void	Update();

	// Data to be passed to every UIObject::RecursivelyRender call to prevent calling natives for every object.
	struct		FrameState
	{
		// This is only true for the first frame that the mouse button has been down.
		bool		IsLeftMouseClicked;
		// This is only true for the first frame that the mouse button has been down.
		bool		IsRightMouseClicked;
		Math::Vec2	MousePosition;
	};
}
