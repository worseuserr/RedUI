#include <windows.h>
#include "RedUI/UIObject.h"
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

UIObject *UIObject::GetParent() const
{
	return (Parent);
}

std::vector<UIObject *> UIObject::GetChildren() const
{
	return (Children);
}

void UIObject::RecursivelyUpdateAndDraw()
{
	bool	isRoot;

	isRoot = Parent == nullptr;
	WorldPosition = isRoot ? Position : Parent->WorldPosition * Position;
	WorldScale = isRoot ? Scale : Parent->WorldScale * Scale;
	this->Draw();
	for (UIObject *child : Children)
		child->RecursivelyUpdateAndDraw();
}
