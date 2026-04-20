#pragma once
#include <Sdk/natives.h>
#include "RedUI/Math/Vec2.h"
#include "RedUI/Event/Event.h"

namespace RedUI::Input
{
	constexpr Hash	INPUT_CURSOR_X = 0xD6C4ECDC;
	constexpr Hash	INPUT_CURSOR_Y = 0xE4130778;
	constexpr Hash	INPUT_AIM = 0xF84FA74F;
	constexpr Hash	INPUT_ATTACK = 0x07CE1E61;

	Math::Vec2		GetMousePosition();
	bool			IsLeftMouseDown();
	bool			IsRightMouseDown();
}
