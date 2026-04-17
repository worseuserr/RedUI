#pragma once

#include <memory>
#include <vector>
#include "Animation.h"
#include "Color/RGB.h"
#include "Math/Vec2.h"
#include "Time/Time.h"

namespace RedUI
{
	class	UIObject;
	using	UIObjectOwner = std::unique_ptr<UIObject>;

	// Base class for all ui components.
	class	UIObject
	{
	protected:
		UIObject					*Parent = nullptr;
		std::vector<UIObjectOwner>	Children = {};
		Math::Vec2					WorldPosition = Math::Vec2();
		Math::Vec2					WorldScale = Math::Vec2();

	public:
		// Toggles visibility of object AND its descendants.
		bool		Enabled;
		// Only toggles the visiblity of the object itself, not descendants.
		bool		Visible;
		Math::Vec2	Position;
		Math::Vec2	Scale;
		Color::RGB	Color;
		float		Alpha;

		UIObject(Math::Vec2 position = {}, Math::Vec2 scale = {1, 1},
			Color::RGB color = {}, float alpha = 1.0f);
		virtual			~UIObject() = default;
		virtual void	Draw() = 0;
		void			RecursivelyUpdateAndDraw();
		void			AnimatePositionFrom(Math::Vec2 startPosition, Time::Milliseconds duration, Easing easing = Easing::Linear); // Ooh, staircase!
		void			AnimatePositionTo(Math::Vec2 endPosition, Time::Milliseconds duration, Easing easing = Easing::Linear);
		void			AnimateScaleFrom(Math::Vec2 startScale, Time::Milliseconds duration, Easing easing = Easing::Linear);
		void			AnimateScaleTo(Math::Vec2 endScale, Time::Milliseconds duration, Easing easing = Easing::Linear);
		void			AnimateAlphaFrom(float startAlpha, Time::Milliseconds duration, Easing easing = Easing::Linear);
		void			AnimateAlphaTo(float endAlpha, Time::Milliseconds duration, Easing easing = Easing::Linear);
		void			AnimateColorFrom(Color::RGB startColor, Time::Milliseconds duration, Easing easing = Easing::Linear);
		void			AnimateColorTo(Color::RGB endColor, Time::Milliseconds duration, Easing easing = Easing::Linear);
		// Set parent of object. Parent is root (unparented) if nullptr or no argument.
		void			SetParent(UIObject *newParent = nullptr);
		UIObject		*GetParent() const;
		std::vector<UIObjectOwner>	&GetChildren();
		static UIObjectOwner		*GetChildHandle(std::vector<UIObjectOwner> &children, UIObject *child);

		// Internal raw set parent. Do not use outside of core systems.
		void			__RawSetParent(UIObject *newParent = nullptr);
	};
}
