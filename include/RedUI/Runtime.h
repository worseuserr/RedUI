#pragma once
#include "Sdk/main.h"

namespace RedUI
{
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
			Input::Tick();
			// Scheduler::Tick(); For future coroutine scheduler.
			Focus::Tick();
			UIObject::IsUpdateLocked = true;
			UIObject::TickEvents();
			UIObject::TickAnimation();
			UIObject::TickRender();
			UIObject::IsUpdateLocked = false;
			UIObject::TickQueues();
		}
	};
}
