#pragma once

#include <memory>
#include <unordered_set>
#include <vector>

#include "Animation.h"
#include "Color/RGB.h"
#include "Math/Vec3.h"
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
		Math::Vec3					WorldPosition = Math::Vec3();
		Math::Vec3					WorldScale = Math::Vec3();

	public:

		bool		Enabled;
		Math::Vec3	Position;
		Math::Vec3	Scale;
		Color::RGB	Color;
		float		Alpha;

		UIObject(Math::Vec3 position = Math::Vec3(), Math::Vec3 scale = Math::Vec3(1, 1, 1),
			Color::RGB color = Color::RGB(), float alpha = 1.0f);
		virtual			~UIObject() = default;
		virtual void	Draw() = 0;
		void			RecursivelyUpdateAndDraw();
		void			AnimatePositionFrom(Math::Vec3 startPosition, Time::Milliseconds duration, Easing easing = Easing::Linear); // Ooh, staircase!
		void			AnimatePositionTo(Math::Vec3 endPosition, Time::Milliseconds duration, Easing easing = Easing::Linear);
		void			AnimateScaleFrom(Math::Vec3 startScale, Time::Milliseconds duration, Easing easing = Easing::Linear);
		void			AnimateScaleTo(Math::Vec3 endScale, Time::Milliseconds duration, Easing easing = Easing::Linear);
		void			AnimateAlphaFrom(float startAlpha, Time::Milliseconds duration, Easing easing = Easing::Linear);
		void			AnimateAlphaTo(float endAlpha, Time::Milliseconds duration, Easing easing = Easing::Linear);
		void			AnimateColorFrom(Color::RGB startColor, Time::Milliseconds duration, Easing easing = Easing::Linear);
		void			AnimateColorTo(Color::RGB endColor, Time::Milliseconds duration, Easing easing = Easing::Linear);
		// Set parent of object. Parent is root (unparented) if nullptr or no argument.
		void			SetParent(UIObject *newParent = nullptr);
		UIObject		*GetParent() const;
		std::vector<UIObjectOwner>	&GetChildren();
		static UIObjectOwner		*GetChildHandle(std::vector<UIObjectOwner> &children, UIObject *child);
	};
}
