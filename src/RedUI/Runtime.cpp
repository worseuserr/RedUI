#include "RedUI/Runtime.h"
#include "RedUI/UIObject.h"
#include "RedUI/Input/Mouse.h"

using namespace RedUI;

void Runtime::RedUILoop()
{
	while (true)
	{
		if (UpdateLoopEnabled)
			ProcessTick();
		WAIT(0);
	}
}

void Runtime::ProcessTick()
{
	FrameState	state = { .MousePosition = Input::GetMousePosition() };

	Input::Tick(state); // Sets .IsLeftMouseClicked and .IsRightMouseClicked
	// Scheduler::Tick(); For future coroutine scheduler.
	Focus::Tick();
	UIObject::IsUpdateLocked = true;
	IAnimation::Tick();
	if ((Focus::State & Focus::Interaction) != 0)
		UIObject::TickEvents(state);
	UIObject::TickRender(state);
	UIObject::IsUpdateLocked = false;
	UIObject::TickQueues();
}
