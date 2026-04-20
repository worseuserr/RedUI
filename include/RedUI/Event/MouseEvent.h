#pragma once

#include "RedUI/Event/Event.h"
#include "RedUI/Math/Vec2.h"

namespace RedUI::Event
{

	struct	MouseHoverEventArgs
	{
		Math::Vec2	MousePosition;
	};

	struct	MouseClickEventArgs
	{
		bool		IsLeft;
		Math::Vec2	MousePosition;
	};

	template	<typename TSender>
	class	MouseHoverEvent : public Event<TSender, MouseHoverEventArgs> {};
	template	<typename TSender>
	class	MouseClickEvent : public Event<TSender, MouseClickEventArgs> {};
}
