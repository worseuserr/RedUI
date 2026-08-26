#include "RedUI/Runtime.h"
#include "RedUI/Focus.h"
#include "RedUI/Object/UIObject.h"
#include "RedUI/Input/Mouse.h"

using namespace RedUI;
using namespace RedUI::Object;

bool Runtime::UpdateLoopEnabled = true;

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

	Input::MouseEvents::Tick(state); // Sets .IsLeftMouseClicked and .IsRightMouseClicked
	Input::KeyEvents::Tick(state);
	// Scheduler::Tick(); For future coroutine scheduler.
	Focus::Tick();
	UIObject::IsTickLocked = true;
	IAnimation::Tick();
	if ((Focus::State & Focus::Interaction) != 0)
		UIObject::TickEvents(state);
	UIObject::TickRender(state);
	UIObject::IsTickLocked = false;
	IAnimation::TickQueue();
	UIObject::TickQueue();
}
