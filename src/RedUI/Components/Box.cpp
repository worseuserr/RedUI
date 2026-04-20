#include "RedUI/Components/Box.h"
#include "Sdk/natives.h"

using namespace RedUI;

void Box::Draw()
{
	GRAPHICS::DRAW_RECT(
		WorldPosition.X, WorldPosition.Y, WorldScale.X, WorldScale.Y,
		Color.R, Color.G, Color.B,
		static_cast<int>(Alpha * 255),
		true, true);
}

bool Box::ContainsPoint(Math::Vec2 &point)
{
	float	halfX;
	float	halfY;

	halfX = WorldScale.X * 0.5f;
	halfY = WorldScale.Y * 0.5f;
	return (
		point.X > WorldPosition.X - halfX &&
		point.X < WorldPosition.X + halfX &&
		point.Y > WorldPosition.Y - halfY &&
		point.Y < WorldPosition.Y + halfY
	);
}
