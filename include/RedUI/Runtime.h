#pragma once
#include "RedUI/Math/Vec2.h"

namespace RedUI
{
	namespace Object
	{
		class UIObject;
	}

	struct	FrameState
	{
		// This is only true for the first frame that the mouse button has been down.
		bool		IsLeftMouseClicked;
		// This is only true for the first frame that the mouse button has been down.
		bool		IsRightMouseClicked;
		Math::Vec2	MousePosition;
	};

	class	Runtime
	{
		static bool	UpdateLoopEnabled;

	public:
		Runtime() = delete;
		// Main loop that gets registered to scripthook.
		[[noreturn]] static void	RedUILoop();
		// Process every core system in a specified order.
		static void					ProcessTick();
	};
}
