#include "RedUI/Runtime.h"
#include "RedUI/Debug.h"
#include "RedUI/Focus.h"
#include "RedUI/Object/UIObject.h"
#include "RedUI/Input/Mouse.h"

using namespace RedUI;
using namespace RedUI::Object;

bool Runtime::UpdateLoopEnabled = true;

void Runtime::RedUILoop()
{
	static IO::Logger	logger = IO::Logger("RedUI.log", "RedUI");
	logger.UseBuffer = true;
	logger.BufferSize = 1048;
	Debug::DLogger = &logger;
	Debug::Log("Starting RedUI version INDEV");
	while (true)
	{
		if (UpdateLoopEnabled)
		{
			try
			{
				ProcessTick();
			}
			catch (const Debug::RedUIException &e)
			{
				Debug::Log("Error exception in RedUI loop caught properly (RedUIException).", LogLevel::Error);
				Debug::Log(std::format("Message: '{}'.", e.what()), LogLevel::Error);
			}
			catch (const std::exception &e)
			{
				Debug::Log("A wrong exception type was thrown in RedUI loop (is or inherits from std::exception). This could be caused by a mod throwing an exception in one of a component's event handlers.", LogLevel::Error);
				Debug::Log(std::format("Message: '{}'.", e.what()), LogLevel::Error);
			}
			catch (...)
			{
				Debug::Log("Unknown exception thrown in RedUI loop.", LogLevel::Error);
			}
		}
		WAIT(UpdateLoopEnabled ? 0 : 1000);
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
	if (Focus::IsActive(Focus::Interaction))
		UIObject::TickEvents(state);
	UIObject::TickRender(state);
	UIObject::IsTickLocked = false;
	IAnimation::TickQueue();
	UIObject::TickQueue();
}
