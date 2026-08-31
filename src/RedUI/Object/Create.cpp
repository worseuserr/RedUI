#include "RedUI/Object/Create.h"

#include "RedUI/Debug.h"
#include "RedUI/Object/UIObject.h"

using namespace RedUI::Object;

void	RedUI::Object::ParentNewUIObject(UIObjectOwner obj, UIObject *newParent)
{
	Debug::DLogger->Write(std::format(
		"New UIObject created: {:p} ({}), parent: {:p} ({})",
		static_cast<void *>(obj.get()),
		obj->Name(),
		static_cast<void *>(newParent),
		newParent ? newParent->Name() : "nullptr"
	).c_str());
	obj->Parent = newParent;
	(newParent == nullptr ? UIObject::RootObjects : newParent->GetChildren()).push_back(std::move(obj));
}
