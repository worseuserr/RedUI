#include "RedUI/Components/TextLabel.h"
#include "Sdk/natives.h"

using namespace RedUI::Components;
using namespace RedUI::Math;
using namespace RedUI::Color;

TextLabel::TextLabel(const std::string &text, const Vec2 &position,
			const float textScale, const RGB &textColor,
			const float textOpacity, const Vec2 &backgroundScale,
			const RGB &backgroundColor, const float backgroundOpacity)
{
	Text = text;
	Position = position;
	TextScale = textScale;
	TextColor = textColor;
	TextOpacity = textOpacity;
	Scale = backgroundScale;
	Color = backgroundColor;
	Opacity = backgroundOpacity;
	Dropshadow = {};
}

void TextLabel::Draw()
{
	Box::Draw();
	UI::SET_TEXT_SCALE(0, TextScale);
	UI::SET_TEXT_COLOR_RGBA(TextColor.R, TextColor.G, TextColor.B, TextOpacity * 255);
	UI::SET_TEXT_CENTRE(TextCentered);
	UI::SET_TEXT_DROPSHADOW(Dropshadow.Distance, Dropshadow.Color.R, Dropshadow.Color.G, Dropshadow.Color.B, Dropshadow.Opacity * 255);
	UI::DRAW_TEXT(
		MISC::CREATE_STRING(
			10,
			"LITERAL_STRING",
			const_cast<char *>(Text.c_str())),
		FinalDrawPosition.X - FinalDrawScale.X * 0.5,
		FinalDrawPosition.Y - FinalDrawScale.Y * 0.5);
}

void TextLabel::AnimateTextScale(const float startValue, const float endValue, const Time::Milliseconds duration, const Easing easing)
	{ Animate<float>(&TextScale, startValue, endValue, duration, easing); }

void TextLabel::AnimateTextColor(const RGB &startValue, const RGB &endValue, const Time::Milliseconds duration, const Easing easing)
	{ Animate<RGB>(&TextColor, startValue, endValue, duration, easing); }

void TextLabel::AnimateTextOpacity(const float startValue, const float endValue, const Time::Milliseconds duration, const Easing easing)
	{ Animate<float>(&TextOpacity, startValue, endValue, duration, easing); }
