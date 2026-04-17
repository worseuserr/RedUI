#include "RedUI/UIObject.h"
#include "RedUI/UIState.h"

using namespace RedUI;
using namespace RedUI::Math;
using namespace RedUI::Color;

UIObject::UIObject(const Vec3 position, const Vec3 scale, const RGB color, const float alpha)
{
	Enabled = true;
	Visible = true;
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

void UIObject::RecursivelyUpdateAndDraw()
{
	bool	isRoot;

	if (!Enabled)
		return ;
	isRoot = Parent == nullptr;
	WorldScale = isRoot ? Scale : Parent->WorldScale * Scale;
	WorldPosition = isRoot ? Position : Parent->WorldPosition + (Position * Parent->WorldScale);
	if (Visible)
		this->Draw();
	for (const std::unique_ptr<UIObject> &child : Children)
		child->RecursivelyUpdateAndDraw();
}

UIObjectOwner *UIObject::GetChildHandle(std::vector<UIObjectOwner> &children, UIObject *child)
{
	const auto	it = std::ranges::find(children, child, &UIObjectOwner::get);

	return (it != children.end() ? &(*it) : nullptr);
}

void UIObject::AnimatePositionFrom(Vec3 startPosition, Time::Milliseconds duration, Easing easing)
{
	UIState::Animations.push_back(std::make_unique<Animation<Vec3>>(&Position, duration, startPosition, Position, easing));
}

void UIObject::AnimatePositionTo(Vec3 endPosition, Time::Milliseconds duration, Easing easing)
{
	UIState::Animations.push_back(std::make_unique<Animation<Vec3>>(&Position, duration, Position, endPosition, easing));
}

void UIObject::AnimateScaleFrom(Vec3 startScale, Time::Milliseconds duration, Easing easing)
{
	UIState::Animations.push_back(std::make_unique<Animation<Vec3>>(&Scale, duration, startScale, Scale, easing));
}

void UIObject::AnimateScaleTo(Vec3 endScale, Time::Milliseconds duration, Easing easing)
{
	UIState::Animations.push_back(std::make_unique<Animation<Vec3>>(&Scale, duration, Scale, endScale, easing));
}

void UIObject::AnimateAlphaFrom(float startAlpha, Time::Milliseconds duration, Easing easing)
{
	UIState::Animations.push_back(std::make_unique<Animation<float>>(&Alpha, duration, startAlpha, Alpha, easing));
}

void UIObject::AnimateAlphaTo(float endAlpha, Time::Milliseconds duration, Easing easing)
{
	UIState::Animations.push_back(std::make_unique<Animation<float>>(&Alpha, duration, Alpha, endAlpha, easing));
}

void UIObject::AnimateColorFrom(RGB startColor, Time::Milliseconds duration, Easing easing)
{
	UIState::Animations.push_back(std::make_unique<Animation<RGB>>(&Color, duration, startColor, Color, easing));
}

void UIObject::AnimateColorTo(RGB endColor, Time::Milliseconds duration, Easing easing)
{
	UIState::Animations.push_back(std::make_unique<Animation<RGB>>(&Color, duration, Color, endColor, easing));
}
