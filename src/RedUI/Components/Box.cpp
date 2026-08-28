#include "RedUI/Components/Box.h"
#include "Sdk/natives.h"

using namespace RedUI::Components;
using namespace RedUI::Math;

void Box::Draw()
{
	GRAPHICS::DRAW_SPRITE(
			"big_feed",
			"big_feed_placeholder_background",
			FinalDrawPosition.X, FinalDrawPosition.Y,
			FinalDrawScale.X, FinalDrawScale.Y,
			Rotation.ToDegrees(),
			Color.R, Color.G, Color.B,
			static_cast<int>(Opacity * 255),
			true);
	// GRAPHICS::DRAW_RECT(
	// 	FinalDrawPosition.X, FinalDrawPosition.Y,
	// 	FinalDrawScale.X, FinalDrawScale.Y,
	// 	Color.R, Color.G, Color.B,
	// 	static_cast<int>(Opacity * 255),
	// 	true, true);
	if (Sprite != nullptr)
		GRAPHICS::DRAW_SPRITE(
			Sprite->TextureDict.c_str(),
			Sprite->TextureName.c_str(),
			FinalDrawPosition.X, FinalDrawPosition.Y,
			FinalDrawScale.X, FinalDrawScale.Y,
			Rotation.ToDegrees() + Sprite->Heading,
			SpriteColor.R, SpriteColor.G, SpriteColor.B,
			static_cast<int>(SpriteOpacity * 255),
			true);
}

bool Box::ContainsPoint(const Vec2 &point)
{
	const float	halfX = FinalHitScale.X * 0.5f;
	const float	halfY = FinalHitScale.Y * 0.5f;

	return (
		point.X > FinalHitPosition.X - halfX &&
		point.X < FinalHitPosition.X + halfX &&
		point.Y > FinalHitPosition.Y - halfY &&
		point.Y < FinalHitPosition.Y + halfY
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

void Box::SetRotation(const float degrees)
{
	Rotation = {degrees};
}

Angle Box::GetRotation() const
{
	return (Rotation);
}

void Box::AnimateRotation(const Angle startValue, const Angle endValue, const Time::Milliseconds duration, const Easing easing)
	{ Animate<Angle>(&Rotation, startValue, endValue, duration, easing); }

void Box::AnimateSpriteColor(const Color::RGB &startValue, const Color::RGB &endValue, const Time::Milliseconds duration, const Easing easing)
	{ Animate<Color::RGB>(&SpriteColor, startValue, endValue, duration, easing); }

void Box::AnimateSpriteOpacity(const float startValue, const float endValue, const Time::Milliseconds duration, const Easing easing)
	{ Animate<float>(&SpriteOpacity, startValue, endValue, duration, easing); }
