#include "RedUI/Remove.h"
#include "RedUI/UIState.h"

void RedUI::Remove(UIObject *&object)
{
	object->Enabled = false;
	if (UIState::IsUpdating)
	{
		UIState::QueuedObjectDeletions.push_back(object);
		return ;
	}
	if (object->GetParent() == nullptr)
		std::erase_if(UIState::RootObjects, [object](const UIObjectOwner &ptr){
			return (object == ptr.get());
		});
	else
		std::erase_if(object->GetParent()->GetChildren(), [object](const UIObjectOwner &ptr){
			return (object == ptr.get());
		});
	object = nullptr;
}
