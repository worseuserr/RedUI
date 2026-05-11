#include "RedUI/Create.h"
#include "RedUI/UIState.h"

void RedUI::EmplaceNewObject(UIObject *parent, UIObjectOwner obj)
{
	obj->__RawSetParent(parent);
	if (parent == nullptr)
		UIState::RootObjects.push_back(std::move(obj));
	else
		parent->GetChildren().push_back(std::move(obj));
}
