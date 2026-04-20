#include "RedUI/Components/Box.h"
#include "Sdk/natives.h"

using namespace RedUI;

void Box::Draw()
{
	const Math::Vec2	pos = WorldPosition + RenderOffset;
	const Math::Vec2	scale = WorldScale * RenderScale;

	GRAPHICS::DRAW_RECT(
		pos.X, pos.Y, scale.X, scale.Y,
		Color.R, Color.G, Color.B,
		static_cast<int>(Alpha * 255),
		true, true);
}

bool Box::ContainsPoint(Math::Vec2 &point)
{
	const Math::Vec2	pos = WorldPosition + RenderOffset;
	const Math::Vec2	scale = WorldScale * RenderScale;
	float				halfX;
	float				halfY;

	halfX = scale.X * 0.5f;
	halfY = scale.Y * 0.5f;
	return (
		point.X > pos.X - halfX &&
		point.X < pos.X + halfX &&
		point.Y > pos.Y - halfY &&
		point.Y < pos.Y + halfY
	);
}
