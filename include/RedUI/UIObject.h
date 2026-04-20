#pragma once
#include <memory>
#include <vector>
#include "Animation.h"
#include "Update.h"
#include "Color/RGB.h"
#include "Event/MouseEvent.h"
#include "Math/Vec2.h"
#include "Time/Time.h"

namespace RedUI
{
	class	UIObject;
	using	UIObjectOwner = std::unique_ptr<UIObject>;

	// Base class for all ui components.
	class	UIObject
	{
		// Used for mouse events.
		bool						MouseHovering = false;
		bool						HasLeftClicked = false;
		bool						HasRightClicked = false;

	protected:
		UIObject					*Parent = nullptr;
		std::vector<UIObjectOwner>	Children = {};
		Math::Vec2					WorldPosition = Math::Vec2();
		Math::Vec2					WorldScale = Math::Vec2();

	public:
		// Toggles visibility of object AND its descendants.
		bool			Enabled = true;
		// Only toggles the visiblity of the object itself, not descendants.
		bool			Visible = true;
		bool			Clickable = true;
		Math::Vec2		Position;
		Math::Vec2		Scale;
		Color::RGB		Color;
		float			Alpha;
		// Purely visual offset that does not affect the position of an object's children.
		Math::Vec2		RenderOffset = Math::Vec2();
		// Purely visual scale multiplier that does not affect the position or scale of an object's children.
		Math::Vec2		RenderScale = Math::Vec2(1, 1);
		Event::MouseHoverEvent<UIObject>	OnMouseEnter;
		Event::MouseHoverEvent<UIObject>	OnMouseLeave;
		Event::MouseClickEvent<UIObject>	OnLeftClick;
		Event::MouseClickEvent<UIObject>	OnRightClick;

		UIObject(Math::Vec2 position = {}, Math::Vec2 scale = {1, 1},
			Color::RGB color = {}, float alpha = 1.0f);
		virtual			~UIObject() = default;
		void			RecursivelyUpdateAndDraw(FrameState &state);
		// Draw component. Called every frame, in order: ProcessEvents (and thus ContainsPoint) -> Update -> Draw.
		virtual void	Draw() = 0;
		// Optional method for ui components to implement per-frame logic.
		virtual void	Update(FrameState &state) {}
		// Return whether or not point is on the drawn component. This is polled every frame and used to dispatch mouse events.
		virtual bool	ContainsPoint(Math::Vec2 &point) = 0;
		// Gets input information, polls ContainsPoint, and invokes events.
		virtual void	ProcessEvents(FrameState &state);
		void			AnimatePositionFrom(Math::Vec2 startPosition, Time::Milliseconds duration, Easing easing = Easing::Linear); // Ooh, staircase!
		void			AnimatePositionTo(Math::Vec2 endPosition, Time::Milliseconds duration, Easing easing = Easing::Linear);
		void			AnimateRenderOffsetFrom(Math::Vec2 startOffset, Time::Milliseconds duration, Easing easing = Easing::Linear); // Ooh, staircase!
		void			AnimateRenderOffsetTo(Math::Vec2 endOffset, Time::Milliseconds duration, Easing easing = Easing::Linear);
		void			AnimateRenderScaleFrom(Math::Vec2 startScale, Time::Milliseconds duration, Easing easing = Easing::Linear);
		void			AnimateRenderScaleTo(Math::Vec2 endScale, Time::Milliseconds duration, Easing easing = Easing::Linear);
		void			AnimateScaleFrom(Math::Vec2 startScale, Time::Milliseconds duration, Easing easing = Easing::Linear);
		void			AnimateScaleTo(Math::Vec2 endScale, Time::Milliseconds duration, Easing easing = Easing::Linear);
		void			AnimateAlphaFrom(float startAlpha, Time::Milliseconds duration, Easing easing = Easing::Linear);
		void			AnimateAlphaTo(float endAlpha, Time::Milliseconds duration, Easing easing = Easing::Linear);
		void			AnimateColorFrom(Color::RGB startColor, Time::Milliseconds duration, Easing easing = Easing::Linear);
		void			AnimateColorTo(Color::RGB endColor, Time::Milliseconds duration, Easing easing = Easing::Linear);
		bool			IsMouseHovering() const;
		// Set parent of object. Parent is root (unparented) if nullptr or no argument.
		void			SetParent(UIObject *newParent = nullptr);
		UIObject		*GetParent() const;
		std::vector<UIObjectOwner>	&GetChildren();
		static UIObjectOwner		*GetChildHandle(std::vector<UIObjectOwner> &children, UIObject *child);

		// Internal raw set parent. Do not use outside of core systems.
		void			__RawSetParent(UIObject *newParent = nullptr);
	};
}
