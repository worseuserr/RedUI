#include "RedUI/UIObject.h"

#include <algorithm>

#include "RedUI/UIState.h"

using namespace RedUI;
using namespace RedUI::Math;
using namespace RedUI::Color;

UIObject::UIObject(const Vec3 position, const Vec3 scale, const RGB color, const float alpha, UIObject *parent)
{
	Position = position;
	Scale = scale;
	Color = color;
	Alpha = alpha;
	SetParent(parent);
}

// If parent == nullptr, then parent is root.
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
		std::erase(Parent->Children, this);
		UIState::Objects.push_back(this);
	}
	else
	{
		if (Parent == nullptr)
			std::erase(UIState::Objects, this);
		else
			std::erase(Parent->Children, this);
		newParent->Children.push_back(this);
	}
	Parent = newParent;
}

void UIObject::Draw() const
{
}
