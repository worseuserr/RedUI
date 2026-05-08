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

	struct	HitState
	{
		FrameState	&Frame;
		bool		LeftClickConsumed;
		bool		RightClickConsumed;
		bool		HoverConsumed;
		// Set to true if clicks and hovers are all consumed.
		bool		FullyConsumed;
	};

	// Plan for hit occlusion
	// CurrentlyHovering to track if hovering
	// HasHovered to track if mouse is still hovering this frame
	// HasLeftClicked and HasRightClicked to track if click was registered for object
	// 	in event processing, if mousedown and click hasnt been registered yet, set hasclicked to true and invoke mousedown
	//
	// After Update(), check mousedown, hashovered and everything to invoke all mouseup and hoverleave events, then reset bools
	//
	// MouseClick will be split into MouseDown and MouseUp

	// Base class for all ui components.
	class	UIObject
	{
		// Tracks if mouse is hovering.
		bool		MouseHovering = false;
		// If mouse was hovering during event processing. Is reset at end of RecursivelyRender.
		bool		HasHovered = false;
		bool		HasLeftClicked = false;
		bool		HasRightClicked = false;

		static void	RegisterAnimation(AnimationOwner anim);

	protected:
		UIObject					*Parent = nullptr;
		std::vector<UIObjectOwner>	Children = {};
		Math::Vec2					WorldPosition = Math::Vec2();
		Math::Vec2					WorldScale = Math::Vec2();

	public:
		// Toggles visibility and functionality of object AND its descendants.
		bool			Enabled = true;
		// Toggles only the visiblity of the object itself, not descendants.
		bool			Visible = true;
		// Toggles clicked events.
		bool			Clickable = true;
		// Toggles hover events.
		bool			Hoverable = true;
		bool			BlocksClick = true;
		bool			BlocksHover = true;
		// If enabled, children that are physically outside the object can receive mouse events. Otherwise not. Performance heavy if enabled with many children.
		bool			OverflowChildHits = false;
		Math::Vec2		Position;
		Math::Vec2		Scale;
		Color::RGB		Color;
		float			Alpha;
		// Purely visual offset that does not affect the position of an object's children.
		Math::Vec2		RenderOffset = Math::Vec2();
		// Purely visual scale multiplier that does not affect the position or scale of an object's children.
		Math::Vec2		RenderScale = Math::Vec2(1, 1);
		// If true, skips UpdateWorldTransform call during render. This is for skipping objects that have been updated in the event processing.
		bool			HasUpdatedWorldTransform = false;
		Event::MouseHoverEvent<UIObject>	OnMouseEnter;
		Event::MouseHoverEvent<UIObject>	OnMouseLeave;
		Event::MouseClickEvent<UIObject>	OnLeftClick;
		Event::MouseClickEvent<UIObject>	OnRightClick;

		UIObject(Math::Vec2 position = {}, Math::Vec2 scale = {1, 1},
			Color::RGB color = {}, float alpha = 1.0f);
		virtual			~UIObject() = default;
		// Updates world transform using local transforms and nearest parent.
		void			UpdateWorldTransform();
		// The main entry point for invoking events, updating layout and rendering.
		void			RecursivelyRender(FrameState &state);
		// Draw component. Called every frame, in order: ProcessEvents (and thus ContainsPoint) -> Update -> Draw.
		virtual void	Draw() = 0;
		// Optional method for ui components to implement per-frame logic.
		// Important: If changing Position or Scale inside the method, you MUST call UpdateWorldTransform afterwards or use SetPosition/SetScale.
		virtual void	Update(FrameState &state) {}
		// Return whether or not point is on the drawn component. This is polled every frame and used to dispatch mouse events.
		virtual bool	ContainsPoint(Math::Vec2 &point) = 0;
		// Gets input information, polls ContainsPoint, and invokes events.
		// This returns true if the mouse is NOT currently inside (ContainsPoint) the object for recursion early exit.
		// Does not exit early if object has OverflowChildHits set to true.
		bool			RecursivelyProcessEvents(HitState &state);
		template		<typename T>
		void			Animate(T *member, const T &startValue, const T &endValue, Time::Milliseconds duration, Easing easing)
		{
			RegisterAnimation(std::make_unique<Animation<T>>(member, duration, startValue, endValue, easing));
		}
		void			AnimatePositionFrom(const Math::Vec2 &startPosition, Time::Milliseconds duration, Easing easing = Easing::Linear);
		void			AnimatePositionTo(const Math::Vec2 &endPosition, Time::Milliseconds duration, Easing easing = Easing::Linear);
		void			AnimateRenderOffsetFrom(const Math::Vec2 &startOffset, Time::Milliseconds duration, Easing easing = Easing::Linear);
		void			AnimateRenderOffsetTo(const Math::Vec2 &endOffset, Time::Milliseconds duration, Easing easing = Easing::Linear);
		void			AnimateRenderScaleFrom(const Math::Vec2 &startScale, Time::Milliseconds duration, Easing easing = Easing::Linear);
		void			AnimateRenderScaleTo(const Math::Vec2 &endScale, Time::Milliseconds duration, Easing easing = Easing::Linear);
		void			AnimateScaleFrom(const Math::Vec2 &startScale, Time::Milliseconds duration, Easing easing = Easing::Linear);
		void			AnimateScaleTo(const Math::Vec2 &endScale, Time::Milliseconds duration, Easing easing = Easing::Linear);
		void			AnimateColorFrom(const Color::RGB &startColor, Time::Milliseconds duration, Easing easing = Easing::Linear);
		void			AnimateColorTo(const Color::RGB &endColor, Time::Milliseconds duration, Easing easing = Easing::Linear);
		void			AnimateAlphaFrom(float startAlpha, Time::Milliseconds duration, Easing easing = Easing::Linear);
		void			AnimateAlphaTo(float endAlpha, Time::Milliseconds duration, Easing easing = Easing::Linear);
		bool			IsMouseHovering() const;
		// Set parent of object. Parent is root (unparented) if nullptr or no argument.
		void			SetParent(UIObject *newParent = nullptr);
		UIObject		*GetParent() const;
		// Safely set position by immediately updating world transform afterwards.
		void			SetPosition(const Math::Vec2 &position);
		// Safely set scale by immediately updating world transform afterwards.
		void			SetScale(const Math::Vec2 &scale);
		std::vector<UIObjectOwner>	&GetChildren();
		static UIObjectOwner		*GetChildHandle(std::vector<UIObjectOwner> &children, UIObject *child);

		// Internal raw set parent. Do not use outside of core systems.
		void			__RawSetParent(UIObject *newParent = nullptr);
	};
}
