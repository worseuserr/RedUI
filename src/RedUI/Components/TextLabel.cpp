#include "RedUI/Components/TextLabel.h"
#include "Sdk/natives.h"

using namespace RedUI;
using namespace RedUI::Math;
using namespace RedUI::Color;

TextLabel::TextLabel(const std::string &text, const Vec2 &position,
			const float textScale, const RGB &textColor,
			const float textAlpha, const Vec2 &backgroundScale,
			const RGB &backgroundColor, const float backgroundAlpha)
{
	Text = text;
	Position = position;
	TextScale = textScale;
	TextColor = textColor;
	TextAlpha = textAlpha;
	Scale = backgroundScale;
	Color = backgroundColor;
	Alpha = backgroundAlpha;
	Dropshadow = {};
}

void TextLabel::Draw()
{
	const Vec2	pos = WorldPosition + RenderOffset;
	const Vec2	scale = WorldScale * RenderScale;

	Box::Draw();
	UI::SET_TEXT_SCALE(0, TextScale);
	UI::SET_TEXT_COLOR_RGBA(TextColor.R, TextColor.G, TextColor.B, TextAlpha * 255);
	UI::SET_TEXT_CENTRE(TextCentered);
	UI::SET_TEXT_DROPSHADOW(Dropshadow.Distance, Dropshadow.Color.R, Dropshadow.Color.G, Dropshadow.Color.B, Dropshadow.Alpha * 255);
	UI::DRAW_TEXT(
		MISC::CREATE_STRING(
			10,
			"LITERAL_STRING",
			const_cast<char *>(Text.c_str())),
		pos.X - scale.X * 0.5,
		pos.Y - scale.Y * 0.5);
}

void TextLabel::AnimateTextScale(const float startScale, const float endScale, const Time::Milliseconds duration, const Easing easing)
{ Animate<float>(&TextScale, startScale, endScale, duration, easing); }

void TextLabel::AnimateTextColor(const RGB &startColor, const RGB &endColor, const Time::Milliseconds duration, const Easing easing)
{ Animate<RGB>(&TextColor, startColor, endColor, duration, easing); }

void TextLabel::AnimateTextAlpha(const float startAlpha, const float endAlpha, const Time::Milliseconds duration, const Easing easing)
{ Animate<float>(&TextAlpha, startAlpha, endAlpha, duration, easing); }
