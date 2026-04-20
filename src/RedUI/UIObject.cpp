#include "RedUI/UIObject.h"
#include "RedUI/UIState.h"

using namespace RedUI;
using namespace RedUI::Math;
using namespace RedUI::Color;

void UIObject::RegisterAnimation(AnimationOwner anim)
{
	UIState::Animations.push_back(std::move(anim));
}

UIObject::UIObject(const Vec2 position, const Vec2 scale, const RGB color, const float alpha)
{
	Position = position;
	Scale = scale;
	Color = color;
	Alpha = alpha;
}

void UIObject::__RawSetParent(UIObject *newParent)
{
	Parent = newParent;
}

void UIObject::SetParent(UIObject *newParent)
{
	if (newParent == Parent)
		return ;
	if (UIState::IsUpdating)
	{
		UIState::QueuedHierarchyChanges[this] = newParent;
		return ;
	}
	if (newParent == nullptr)
	{
		UIState::RootObjects.push_back(std::move(*GetChildHandle(Parent->Children, this)));
		std::erase(Parent->Children, nullptr);
	}
	else
	{
		newParent->Children.push_back(std::move(*GetChildHandle(Parent->Children, this)));
		if (Parent == nullptr)
			std::erase(UIState::RootObjects, nullptr);
		else
			std::erase(Parent->Children, nullptr);
	}
	Parent = newParent;
}

UIObject *UIObject::GetParent() const
{
	return (Parent);
}

std::vector<UIObjectOwner> &UIObject::GetChildren()
{
	return (Children);
}

void UIObject::RecursivelyUpdateAndDraw(FrameState &state)
{
	bool	isRoot;

	if (!Enabled)
		return ;
	isRoot = Parent == nullptr;
	WorldScale = isRoot ? Scale : Parent->WorldScale * Scale;
	WorldPosition = isRoot ? Position : Parent->WorldPosition + (Position - Vec2(0.5, 0.5)) * Parent->WorldScale;
	this->ProcessEvents(state);
	this->Update(state);
	if (Visible)
		this->Draw();
	for (const UIObjectOwner &child : Children)
		child->RecursivelyUpdateAndDraw(state);
}

UIObjectOwner *UIObject::GetChildHandle(std::vector<UIObjectOwner> &children, UIObject *child)
{
	const auto	it = std::ranges::find(children, child, &UIObjectOwner::get);

	return (it != children.end() ? &(*it) : nullptr);
}

void UIObject::ProcessEvents(FrameState &state)
{
	bool	contains;

	contains = ContainsPoint(state.MousePosition);
	if (contains && !MouseHovering)
	{
		MouseHovering = true;
		OnMouseEnter.Invoke(this, { .MousePosition = state.MousePosition });
	}
	else if (!contains && MouseHovering)
	{
		MouseHovering = false;
		OnMouseLeave.Invoke(this, { .MousePosition = state.MousePosition });
	}
	if (!Clickable)
		return ;
	if (!state.IsLeftMouseDown)
		HasLeftClicked = false;
	else if (!HasLeftClicked && contains)
	{
		HasLeftClicked = true;
		OnLeftClick.Invoke(this, { .IsLeft = true, .MousePosition = state.MousePosition });
	}
	if (!state.IsRightMouseDown)
		HasRightClicked = false;
	else if (!HasRightClicked && contains)
	{
		HasRightClicked = true;
		OnRightClick.Invoke(this, { .IsLeft = false, .MousePosition = state.MousePosition });
	}
}

bool UIObject::IsMouseHovering() const
{
	return (MouseHovering);
}

void UIObject::AnimatePositionFrom(const Vec2 &startPosition, const Time::Milliseconds duration, const Easing easing)
	{ Animate<Vec2>(&Position, startPosition, Position, duration, easing); }

void UIObject::AnimatePositionTo(const Vec2 &endPosition, const Time::Milliseconds duration, const Easing easing)
	{ Animate<Vec2>(&Position, Position, endPosition, duration, easing); }

void UIObject::AnimateRenderOffsetFrom(const Vec2 &startOffset, const Time::Milliseconds duration, const Easing easing)
	{ Animate<Vec2>(&RenderOffset, startOffset, RenderOffset, duration, easing); }

void UIObject::AnimateRenderOffsetTo(const Vec2 &endOffset, const Time::Milliseconds duration, const Easing easing)
	{ Animate<Vec2>(&RenderOffset, RenderOffset, endOffset, duration, easing); }

void UIObject::AnimateRenderScaleFrom(const Vec2 &startScale, const Time::Milliseconds duration, const Easing easing)
	{ Animate<Vec2>(&RenderScale, startScale, RenderScale, duration, easing); }

void UIObject::AnimateRenderScaleTo(const Vec2 &endScale, const Time::Milliseconds duration, const Easing easing)
	{ Animate<Vec2>(&RenderScale, RenderScale, endScale, duration, easing); }

void UIObject::AnimateScaleFrom(const Vec2 &startScale, const Time::Milliseconds duration, const Easing easing)
	{ Animate<Vec2>(&Scale, startScale, Scale, duration, easing); }

void UIObject::AnimateScaleTo(const Vec2 &endScale, const Time::Milliseconds duration, const Easing easing)
	{ Animate<Vec2>(&Scale, Scale, endScale, duration, easing);}

void UIObject::AnimateColorFrom(const RGB &startColor, const Time::Milliseconds duration, const Easing easing)
	{ Animate<RGB>(&Color, startColor, Color, duration, easing); }

void UIObject::AnimateColorTo(const RGB &endColor, const Time::Milliseconds duration, const Easing easing)
	{ Animate<RGB>(&Color, Color, endColor, duration, easing); }

void UIObject::AnimateAlphaFrom(const float startAlpha, const Time::Milliseconds duration, const Easing easing)
	{ Animate<float>(&Alpha, startAlpha, Alpha, duration, easing); }

void UIObject::AnimateAlphaTo(const float endAlpha, const Time::Milliseconds duration, const Easing easing)
	{ Animate<float>(&Alpha, Alpha, endAlpha, duration, easing); }
