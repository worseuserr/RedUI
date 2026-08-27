#include "RedUI/Object/UIObject.h"
#include <algorithm>
#include "RedUI/Input/Screen.h"

using namespace RedUI::Object;
using namespace RedUI::Math;
using namespace RedUI::Color;

bool								UIObject::IsTickLocked = false;
std::vector<UIObjectOwner>			UIObject::RootObjects = {};
std::vector<UIObject *>				UIObject::DeletionQueue = {};
std::map<UIObject *, UIObject *>	UIObject::ReparentQueue = {};

void UIObject::TickEvents(FrameState &state)
{
	int			i;
	HitState	hitState = {
		.Frame = state,
		.LeftClickConsumed = false,
		.RightClickConsumed = false,
		.HoverConsumed = false,
		.FullyConsumed = false
	};

	// Process events backwards for newer children to occlude existing ones since that's how they render.
	for (i = RootObjects.size(); i-- > 0;)
		RootObjects[i]->RecursivelyProcessEvents(hitState);
}

void UIObject::TickRender(FrameState &state)
{
	int	i;

	for (i = 0; i < RootObjects.size(); i++)
		RootObjects[i]->RecursivelyRender(state);
}

void UIObject::TickQueue()
{
	for (UIObject *obj: DeletionQueue)
		obj->Destroy();
	for (const auto &[obj, newParent] : ReparentQueue)
		obj->SetParent(newParent);
	DeletionQueue.clear();
	ReparentQueue.clear();
}

void UIObject::UpdateZ() const
{
	std::vector<UIObjectOwner>	&container = Parent == nullptr ? RootObjects : Parent->Children;

	std::ranges::sort(container, [](const UIObjectOwner &a, const UIObjectOwner &b){
		return (a->ZIndex > b->ZIndex);
	});
}

UIObject::UIObject(const Vec2 &position, const Vec2 &scale, const RGB &color, const float opacity)
{
	Position = position;
	Scale = scale;
	Color = color;
	Opacity = opacity;
}

void UIObject::SetParent(UIObject *newParent)
{
	if (newParent == Parent)
		return ;
	if (IsTickLocked)
	{
		ReparentQueue[this] = newParent;
		return ;
	}
	if (Parent == nullptr)
	{
		newParent->Children.push_back(std::move(*GetChildHandle(RootObjects, this)));
		std::erase(RootObjects, nullptr);
	}
	else
	{
		RootObjects.push_back(std::move(*GetChildHandle(Parent->Children, this)));
		std::erase(Parent->Children, nullptr);
	}
	Parent = newParent;
	UpdateWorldTransform();
}

UIObject *UIObject::GetParent() const
{
	return (Parent);
}

void UIObject::SetPosition(const Vec2 &position)
{
	Position = position;
	UpdateWorldTransform();
}

Vec2 UIObject::GetPosition() const
{
	return (Position);
}

Vec2 UIObject::GetScale() const
{
	return (Scale);
}

void UIObject::SetScale(const Vec2 &scale)
{
	Scale = scale;
	UpdateWorldTransform();
}

void UIObject::SetZIndex(int value)
{
	ZIndex = value;
	UpdateZ();
}

int UIObject::GetZIndex() const
{
	return (ZIndex);
}

std::vector<UIObjectOwner> &UIObject::GetChildren()
{
	return (Children);
}

UIObjectOwner *UIObject::GetChildHandle(std::vector<UIObjectOwner> &children, UIObject *child)
{
	const auto	it = std::ranges::find(children, child, &UIObjectOwner::get);

	return (it != children.end() ? &(*it) : nullptr);
}

bool UIObject::IsInTick()
{
	return (IsTickLocked);
}

void UIObject::RecursivelyRender(FrameState &state)
{
	if (!Enabled)
		return ;
	if (!HasUpdatedWorldTransform)
		UpdateWorldTransform();
	// It's set to false because it won't be used for the rest of the tick.
	HasUpdatedWorldTransform = false;
	if (MouseHovering != HasHovered)
	{
		if (HasHovered)
			OnMouseEnter.Invoke(this, { .MousePosition = state.MousePosition });
		else
			OnMouseLeave.Invoke(this, { .MousePosition = state.MousePosition });
		MouseHovering = HasHovered;
	}
	HasHovered = false;
	this->Update(state);
	if (Visible)
		this->Draw();
	for (const UIObjectOwner &child : Children)
		child->RecursivelyRender(state);
}

void UIObject::Destroy()
{
	Enabled = false;
	if (IsTickLocked)
	{
		DeletionQueue.push_back(this);
		return ;
	}
	if (Parent == nullptr)
		std::erase_if(RootObjects, [this](const UIObjectOwner &ptr){
			return (this == ptr.get());
		});
	else
		std::erase_if(Parent->GetChildren(), [this](const UIObjectOwner &ptr){
			return (this == ptr.get());
		});
}

void UIObject::UpdateWorldTransform()
{
	bool	isRoot;
	Vec2	AspectScale = Vec2(Input::GetGameWindow().GetAspectRatio(), 1);

	isRoot = Parent == nullptr;
	WorldScale = isRoot ? Scale : Parent->WorldScale * Scale;
	WorldPosition = isRoot ? Position : Parent->WorldPosition + (Position - Vec2(0.5, 0.5)) * (Parent->WorldScale * AspectScale);
	FinalDrawPosition = WorldPosition + RenderOffset;
	FinalDrawScale = (WorldScale * RenderScale) * AspectScale;
	FinalHitPosition = (RenderTransformAffectsHits ? WorldPosition + RenderOffset : WorldPosition);
	FinalHitScale = (RenderTransformAffectsHits ? WorldScale * RenderScale : WorldScale) * AspectScale;
}

void UpdateHitState(HitState &state)
{
	if (state.RightClickConsumed && state.HoverConsumed && state.LeftClickConsumed)
		state.FullyConsumed = true;
}

bool UIObject::RecursivelyProcessEvents(HitState &state)
{
	bool	contains;
	size_t	i;

	// Early exit and children.
	if (state.FullyConsumed || !Enabled)
		return (false);
	contains = ContainsPoint(state.Frame.MousePosition);
	if (!OverflowChildHits && !contains)
		return (true);
	UpdateWorldTransform();
	HasUpdatedWorldTransform = true;
	for (i = Children.size(); i-- > 0;)
	{
		const UIObjectOwner&	child = Children[i];
		if (!child->Enabled)
			continue ;
		child->RecursivelyProcessEvents(state);
		if (state.FullyConsumed)
			return (false);
	}
	if (!contains)
		return (true);
	// Process hit.
	if (!state.LeftClickConsumed && state.Frame.IsLeftMouseClicked)
	{
		if (Clickable)
			OnLeftClick.Invoke(this, { .IsLeft = true, .MousePosition = state.Frame.MousePosition });
		if (BlocksClick)
			state.LeftClickConsumed = true;
	}
	if (!state.RightClickConsumed && state.Frame.IsRightMouseClicked)
	{
		if (Clickable)
			OnRightClick.Invoke(this, { .IsLeft = false, .MousePosition = state.Frame.MousePosition });
		if (BlocksClick)
			state.RightClickConsumed = true;
	}
	// For hover, the events are called in RecursivelyRender to allow easy comparison between old and new state.
	if (!state.HoverConsumed && Hoverable)
		HasHovered = true;
	if (BlocksHover)
		state.HoverConsumed = true;
	UpdateHitState(state);
	return (false);
}

bool UIObject::IsMouseHovering() const
{
	return (MouseHovering);
}

bool UIObject::HasMouseHoveredThisFrame() const
{
	return (HasHovered);
}

void UIObject::AnimatePosition(const Vec2 &startValue, const Vec2 &endValue, const Time::Milliseconds duration, const Easing easing)
	{ Animate<Vec2>(&Position, startValue, endValue, duration, easing); }

void UIObject::AnimateRenderOffset(const Vec2 &startValue, const Vec2 &endValue, const Time::Milliseconds duration, const Easing easing)
	{ Animate<Vec2>(&RenderOffset, startValue, endValue, duration, easing); }

void UIObject::AnimateRenderScale(const Vec2 &startValue, const Vec2 &endValue, const Time::Milliseconds duration, const Easing easing)
	{ Animate<Vec2>(&RenderScale, startValue, endValue, duration, easing); }

void UIObject::AnimateScale(const Vec2 &startValue, const Vec2 &endValue, const Time::Milliseconds duration, const Easing easing)
	{ Animate<Vec2>(&Scale, startValue, endValue, duration, easing); }

void UIObject::AnimateColor(const RGB &startValue, const RGB &endValue, const Time::Milliseconds duration, const Easing easing)
	{ Animate<RGB>(&Color, startValue, endValue, duration, easing); }

void UIObject::AnimateOpacity(const float startValue, const float endValue, const Time::Milliseconds duration, const Easing easing)
	{ Animate<float>(&Opacity, startValue, endValue, duration, easing); }
