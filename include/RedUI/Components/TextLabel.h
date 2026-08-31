#pragma once
#include "RedUI/Components/Box.h"
#include "../Graphics/Dropshadow.h"

namespace RedUI::Components
{
	class	TextLabel : public Box
	{
	protected:
		void	Draw() override;

	public:
		UI_CREATE(TextLabel, "TextLabel")
		Color::Dropshadow	Dropshadow;
		float				TextScale;
		Color::RGB			TextColor;
		float				TextOpacity;
		std::string			Text;
		bool				TextCentered = false;
		// bool				TextWrapping -> Could possibly be added in the future.

		TextLabel(const std::string &text, const Math::Vec2 &position = {},
			float textScale = 1.0f, const Color::RGB &textColor = {},
			float textOpacity = 1.0f, const Math::Vec2 &backgroundScale = {1, 1},
			const Color::RGB &backgroundColor = {}, float backgroundOpacity = 0.0f);
		void	AnimateTextScale(float startValue, float endValue, Time::Milliseconds duration, Easing easing = Easing::Linear);
		void	AnimateTextColor(const Color::RGB &startValue, const Color::RGB &endValue, Time::Milliseconds duration, Easing easing = Easing::Linear);
		void	AnimateTextOpacity(float startValue, float endValue, Time::Milliseconds duration, Easing easing = Easing::Linear);
		// void	AnimateDropshadow() -> Maybe.
		// void	AnimateText() -> Planned, with different animation styles (swap, erase then fill, glitch, fade in, etc).
	};
}
