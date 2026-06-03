#pragma once
#include "RedUI/Components/Box.h"
#include "RedUI/Color/Dropshadow.h"

namespace RedUI
{
	class	TextLabel : public Box
	{
	protected:
		void	Draw() override;

	public:
		Color::Dropshadow	Dropshadow;
		float				TextScale;
		Color::RGB			TextColor;
		float				TextAlpha;
		std::string			Text;
		bool				TextCentered = false;
		// bool				TextWrapping -> Could possibly be added in the future.

		TextLabel(const std::string &text, const Math::Vec2 &position = {},
			float textScale = 1.0f, const Color::RGB &textColor = {},
			float textAlpha = 1.0f, const Math::Vec2 &backgroundScale = {1, 1},
			const Color::RGB &backgroundColor = {}, float backgroundAlpha = 0.0f);
		void	AnimateTextScale(float startScale, float endScale, Time::Milliseconds duration, Easing easing = Easing::Linear);
		void	AnimateTextColor(const Color::RGB &startColor, const Color::RGB &endColor, Time::Milliseconds duration, Easing easing = Easing::Linear);
		void	AnimateTextAlpha(float startAlpha, float endAlpha, Time::Milliseconds duration, Easing easing = Easing::Linear);
		// void	AnimateDropshadow() -> Maybe.
		// void	AnimateText() -> Planned, with different animation styles (swap, erase then fill, glitch, fade in, etc).
	};
}
