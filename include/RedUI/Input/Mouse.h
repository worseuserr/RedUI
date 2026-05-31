#pragma once
#include <Sdk/natives.h>
#include "RedUI/Math/Vec2.h"
#include "RedUI/Event/Event.h"

#ifdef RedUI_EXPORTS // Define this in CMake only for the DLL target
   #define API __declspec(dllexport)
#else
   #define API __declspec(dllimport)
#endif

namespace RedUI::Input
{
	constexpr Hash	INPUT_CURSOR_X = 0xD6C4ECDC;
	constexpr Hash	INPUT_CURSOR_Y = 0xE4130778;
	constexpr Hash	INPUT_AIM = 0xF84FA74F;
	constexpr Hash	INPUT_ATTACK = 0x07CE1E61;

	struct MouseChangedEventArgs
	{
		bool	WasDown;
		bool	IsDown;
	};

	template	<typename TSender>
	class MouseChangedEvent : public Event::Event<TSender, MouseChangedEventArgs> {};

	// Returns width and height.
	Math::Vec2	GetGameWindow(HWND &window, RECT &clientRect);
	Math::Vec2	GetMousePosition();
	void		SetMousePosition(const Math::Vec2 &position);
	bool		IsLeftMouseDown();
	bool		IsRightMouseDown();

	// This may get changed back to a static class if a dynamic OnKeyPressed(key) or similar method is added.
	namespace Events
	{
		API extern MouseChangedEvent<void>	OnLeftMouseDown;
		API extern MouseChangedEvent<void>	OnLeftMouseUp;
		API extern MouseChangedEvent<void>	OnRightMouseDown;
		API extern MouseChangedEvent<void>	OnRightMouseUp;
	}
}
