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
void UIObject::SetParent(UIObject *parent)
{
	if (UIState::IsUpdating)
	{
		UIState::QueuedHierarchyChanges[this] = parent;
		return ;
	}

	// todo: add logic to remove from old parent and set to root if new parent = nullptr
	Parent = parent;
	Parent->Children.push_back(this);
}

void UIObject::Draw() const
{
}
