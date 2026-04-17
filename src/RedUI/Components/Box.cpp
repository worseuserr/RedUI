#include "RedUI/Components/Box.h"
#include "Sdk/natives.h"

using namespace RedUI;

void Box::Draw()
{
	GRAPHICS::DRAW_RECT(Position.X, Position.Y, Scale.X, Scale.Y,
		Color.R, Color.G, Color.B,
		static_cast<int>(Alpha * 255),
		true, true);
}
