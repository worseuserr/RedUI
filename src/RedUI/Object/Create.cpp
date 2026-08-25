#include "RedUI/Object/Create.h"
#include "RedUI/Object/UIObject.h"

using namespace RedUI::Object;

void	RedUI::Object::ParentNewUIObject(UIObjectOwner obj, UIObject *newParent)
{
	obj->Parent = newParent;
	(newParent == nullptr ? UIObject::RootObjects : newParent->GetChildren()).push_back(std::move(obj));
}
