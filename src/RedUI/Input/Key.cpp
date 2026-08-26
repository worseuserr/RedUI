#include "RedUI/Input/Key.h"

using namespace RedUI;

std::map<Input::Key, Input::KeyState>	Input::KeyChangedEvent::KeyChangedEvents = {};

Input::KeyChangedEvent::KeyChangedEvent(Input::Key key)
{
	Key = key;
	if (!KeyChangedEvents.contains(Key))
		KeyChangedEvents[Key] = { .IsDown = IsKeyDown(Key), .Events = {} };
	KeyChangedEvents[Key].Events.push_back(this);
}

Input::KeyChangedEvent::~KeyChangedEvent()
{
	std::erase(KeyChangedEvents[Key].Events, this);
	if (KeyChangedEvents[Key].Events.size() < 1)
		KeyChangedEvents.erase(Key);
}

bool Input::IsKeyDown(Key key)
{
	return ((GetAsyncKeyState(static_cast<SHORT>(key)) & KEY_PRESSED_BIT) != 0);
}

void Input::KeyEvents::Tick(FrameState &state)
{
	bool	isDown;

	for (auto &[key, keyState] : KeyChangedEvent::KeyChangedEvents)
	{
		isDown = IsKeyDown(key);
		if (keyState.IsDown != isDown)
		{
			for (KeyChangedEvent *event : keyState.Events)
				event->Invoke(nullptr, { .IsDown = isDown, .Key = key });
			keyState.IsDown = isDown;
		}
	}
}
