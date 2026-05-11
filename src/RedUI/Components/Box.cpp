#include "RedUI/Components/Box.h"
#include "Sdk/natives.h"

using namespace RedUI;
using namespace RedUI::Math;

void Box::Draw()
{
	const Vec2	pos = WorldPosition + RenderOffset;
	const Vec2	scale = WorldScale * RenderScale;

	if (Sprite != nullptr)
		GRAPHICS::DRAW_SPRITE(
			Sprite->TextureDict.c_str(),
			Sprite->TextureName.c_str(),
			pos.X, pos.Y, scale.X, scale.Y,
			Sprite->Heading,
			Color.R, Color.G, Color.B,
			static_cast<int>(Alpha * 255),
			true);
	else
		GRAPHICS::DRAW_RECT(
			pos.X, pos.Y, scale.X, scale.Y,
			Color.R, Color.G, Color.B,
			static_cast<int>(Alpha * 255),
			true, true);
}

bool Box::ContainsPoint(const Vec2 &point)
{
	const Vec2	pos = WorldPosition;
	const Vec2	scale = WorldScale;
	const float	halfX = scale.X * 0.5f;
	const float	halfY = scale.Y * 0.5f;

	return (
		point.X > pos.X - halfX &&
		point.X < pos.X + halfX &&
		point.Y > pos.Y - halfY &&
		point.Y < pos.Y + halfY
	);
}
