#pragma once
#include <map>
#include <memory>
#include <vector>
#include "Graphics/Animation.h"
#include "RedUI/Runtime.h"
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

	// Base class for all ui components.
	class	UIObject
	{
		friend class							Runtime;
		// static std::vector<UIObject *>		All; // Should add this.
		// Lock changes to static containers while ticking.
		static bool								IsTickLocked;
		static std::vector<UIObjectOwner>		RootObjects;
		static std::vector<UIObject *>			DeletionQueue;
		static std::map<UIObject *, UIObject *>	ReparentQueue;
		// Tracks if mouse is hovering.
		bool	MouseHovering = false;
		// If mouse was hovering during event processing this frame.
		bool	HasHovered = false;

		// Gets input information, polls ContainsPoint, and invokes events.
		// This returns true if the mouse is NOT currently inside (ContainsPoint) the object.
		// Does not exit early if object has OverflowChildHits set to true.
		// For now, the return value is not used and may be set to void in the future.
		bool		RecursivelyProcessEvents(HitState &state);
		// The main entry point for invoking events, updating layout and rendering.
		void		RecursivelyRender(FrameState &state);
		static void	TickEvents(FrameState &state);
		static void	TickRender(FrameState &state);
		static void	TickQueue();

	protected:
		UIObject					*Parent = nullptr;
		std::vector<UIObjectOwner>	Children = {};
		Math::Vec2					WorldPosition = Math::Vec2();
		Math::Vec2					WorldScale = Math::Vec2();

		// Optional method for ui components to implement per-frame logic.
		// Important: If changing Position or Scale inside the method, you MUST call UpdateWorldTransform afterwards or use SetPosition/SetScale.
		virtual void	Update(FrameState &state) {}
		// Draw component. Called every frame, in order: ProcessEvents (and thus ContainsPoint) -> Update -> Draw.
		virtual void	Draw() = 0;
		static void		RegisterAnimation(AnimationOwner anim);

	public:
		// Toggles visibility and functionality of object AND its descendants.
		bool			Enabled = true;
		// Toggles only the visiblity of the object itself, not descendants.
		bool			Visible = true;
		// Toggles clicked events.
		bool			Clickable = false;
		// Toggles hover events.
		bool			Hoverable = false;
		bool			BlocksClick = true;
		bool			BlocksHover = true;
		// If enabled, children that are physically outside the object can receive mouse events. Otherwise not. Performance heavy if enabled with many children.
		bool			OverflowChildHits = false;
		Math::Vec2		Position;
		Math::Vec2		Scale;
		Color::RGB		Color;
		float			Alpha;
		// Purely visual offset that does not affect the position of an object's children, or hit detection.
		Math::Vec2		RenderOffset = Math::Vec2();
		// Purely visual scale multiplier that does not affect the position or scale of an object's children, or hit detection.
		Math::Vec2		RenderScale = Math::Vec2(1, 1);
		// If true, skips UpdateWorldTransform call during render. This is for skipping objects that have been updated in the event processing.
		bool			HasUpdatedWorldTransform = false;
		Event::MouseHoverEvent<UIObject>	OnMouseEnter;
		Event::MouseHoverEvent<UIObject>	OnMouseLeave;
		Event::MouseClickEvent<UIObject>	OnLeftClick;
		Event::MouseClickEvent<UIObject>	OnRightClick;

		UIObject(const Math::Vec2 &position = {}, const Math::Vec2 &scale = {1, 1},
			const Color::RGB &color = {}, float alpha = 1.0f);
		virtual			~UIObject() = default;
		// Updates world transform using local transforms and nearest parent.
		void			UpdateWorldTransform();
		// Return whether or not point is on the drawn component. This is polled every frame and used to dispatch mouse events.
		virtual bool	ContainsPoint(const Math::Vec2 &point) = 0;
		template		<typename T>
		void			Animate(T *member, const T &startValue, const T &endValue, Time::Milliseconds duration, Easing easing)
		{
			RegisterAnimation(std::make_unique<Animation<T>>(member, duration, startValue, endValue, easing));
		}
		void			AnimatePosition(const Math::Vec2 &startPosition, const Math::Vec2 &endPosition, Time::Milliseconds duration, Easing easing = Easing::Linear);
		void			AnimateRenderOffset(const Math::Vec2 &startOffset, const Math::Vec2 &endOffset,Time::Milliseconds duration, Easing easing = Easing::Linear);
		void			AnimateRenderScale(const Math::Vec2 &startScale, const Math::Vec2 &endScale,Time::Milliseconds duration, Easing easing = Easing::Linear);
		void			AnimateScale(const Math::Vec2 &startScale, const Math::Vec2 &endScale, Time::Milliseconds duration, Easing easing = Easing::Linear);
		void			AnimateColor(const Color::RGB &startColor, const Color::RGB &endColor, Time::Milliseconds duration, Easing easing = Easing::Linear);
		void			AnimateAlpha(float startAlpha, float endAlpha, Time::Milliseconds duration, Easing easing = Easing::Linear);
		bool			IsMouseHovering() const;
		// Returns whether the mouse is hovering on the object this frame. Unlike a raw ContainsPoint call, this is occluded by other objects.
		bool			HasMouseHoveredThisFrame() const;
		// Set parent of object. Parent is root (unparented) if nullptr or no argument.
		void			SetParent(UIObject *newParent = nullptr);
		UIObject		*GetParent() const;
		// Safely set position by immediately updating world transform afterwards.
		void			SetPosition(const Math::Vec2 &position);
		// Safely set scale by immediately updating world transform afterwards.
		void			SetScale(const Math::Vec2 &scale);
		std::vector<UIObjectOwner>	&GetChildren();
		static UIObjectOwner		*GetChildHandle(std::vector<UIObjectOwner> &children, UIObject *child);
	};
}
