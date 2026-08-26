#include "RedUI/Components/Box.h"
#include "Sdk/natives.h"

using namespace RedUI::Components;
using namespace RedUI::Math;

void Box::Draw()
{
	const Vec2	pos = WorldPosition + RenderOffset;
	const Vec2	scale = WorldScale * RenderScale;

	GRAPHICS::DRAW_RECT(
		pos.X, pos.Y, scale.X, scale.Y,
		Color.R, Color.G, Color.B,
		static_cast<int>(Alpha * 255),
		true, true);
	if (Sprite != nullptr)
		GRAPHICS::DRAW_SPRITE(
			Sprite->TextureDict.c_str(),
			Sprite->TextureName.c_str(),
			pos.X, pos.Y, scale.X, scale.Y,
			Sprite->Heading,
			SpriteColor.R, SpriteColor.G, SpriteColor.B,
			static_cast<int>(SpriteAlpha * 255),
			true);
}

bool Box::ContainsPoint(const Vec2 &point)
{
	const Vec2	pos = (RenderTransformAffectsHits ? WorldPosition + RenderOffset : WorldPosition);
	const Vec2	scale = (RenderTransformAffectsHits ? WorldScale + RenderScale : WorldScale);
	const float	halfX = scale.X * 0.5f;
	const float	halfY = scale.Y * 0.5f;

	return (
		point.X > pos.X - halfX &&
		point.X < pos.X + halfX &&
		point.Y > pos.Y - halfY &&
		point.Y < pos.Y + halfY
	);
}

void Box::SetSprite(RedUI::Sprite *sprite)
{
	Sprite = sprite;
}

RedUI::Sprite *Box::GetSprite() const
{
	return (Sprite);
}

void Box::AnimateSpriteColor(const Color::RGB &startColor, const Color::RGB &endColor, const Time::Milliseconds duration, const Easing easing)
	{ Animate<Color::RGB>(&SpriteColor, startColor, endColor, duration, easing); }

void Box::AnimateSpriteAlpha(const float startAlpha, const float endAlpha, const Time::Milliseconds duration, const Easing easing)
	{ Animate<float>(&SpriteAlpha, startAlpha, endAlpha, duration, easing); }
