#pragma once
#include "Sdk/main.h"
#include "RedUI/Math/Vec2.h"
#include "RedUI/Input/Mouse.h"
#include "RedUI/Focus.h"
#include "RedUI/UIObject.h"

namespace RedUI
{
	struct		FrameState
	{
		// This is only true for the first frame that the mouse button has been down.
		bool		IsLeftMouseClicked;
		// This is only true for the first frame that the mouse button has been down.
		bool		IsRightMouseClicked;
		Math::Vec2	MousePosition;
	};

	class Runtime
	{
		static bool	UpdateLoopEnabled;

	public:
		[[noreturn]] static void	RedUILoop()
		{
			while (true)
			{
				if (UpdateLoopEnabled)
					ProcessTick();
				WAIT(0);
			}
		}

		// Process every core system in a specified order.
		static void	ProcessTick()
		{
			FrameState	state = { .MousePosition = Input::GetMousePosition() };

			Input::Tick(state); // Sets .IsLeftMouseClicked and .IsRightMouseClicked
			// Scheduler::Tick(); For future coroutine scheduler.
			Focus::Tick(state);
			UIObject::IsUpdateLocked = true;
			UIObject::TickEvents(state);
			UIObject::TickAnimation(state);
			UIObject::TickRender(state);
			UIObject::IsUpdateLocked = false;
			UIObject::TickQueues(state);
		}
	};
}
