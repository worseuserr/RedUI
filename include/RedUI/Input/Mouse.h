#pragma once
#include <Sdk/natives.h>
#include "Key.h"
#include "RedUI/Math/Vec2.h"
#include "RedUI/Event/Event.h"
#include "RedUI/Runtime.h"

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

	struct	MouseHoverEventArgs
	{
		Math::Vec2	MousePosition;
	};

	struct	MouseClickEventArgs
	{
		bool		IsLeft;
		Math::Vec2	MousePosition;
	};

	struct	MouseChangedEventArgs
	{
		bool	WasDown;
		bool	IsDown;
	};

	template	<typename TSender>
	class	MouseHoverEvent : public Event::Event<TSender, MouseHoverEventArgs> {};
	template	<typename TSender>
	class	MouseClickEvent : public Event::Event<TSender, MouseClickEventArgs> {};
	template	<typename TSender>
	class	MouseChangedEvent : public Event::Event<TSender, MouseChangedEventArgs> {};

	Math::Vec2	GetMousePosition();
	void		SetMousePosition(const Math::Vec2 &position);
	bool		IsLeftMouseDown();
	bool		IsRightMouseDown();

	class MouseEvents
	{
		friend class	::RedUI::Runtime;
		static void		Tick(FrameState &state);

	public:
		API static MouseChangedEvent<void>	OnLeftMouseDown;
		API static MouseChangedEvent<void>	OnLeftMouseUp;
		API static MouseChangedEvent<void>	OnRightMouseDown;
		API static MouseChangedEvent<void>	OnRightMouseUp;
	};
}
