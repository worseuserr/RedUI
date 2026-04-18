#include <iostream>
#include <windows.h>
#include "RedUI.h"
#include "RedUI/UIState.h"

bool RedUI::CheckVersion(const unsigned int version)
{
	return (VERSION >= version);
}

bool RedUI::RequireVersion(const unsigned int version)
{
	int	res;

	if (CheckVersion(version))
		return (true);
	res = MessageBox(
		nullptr,
		"Your RedUI version is too outdated for one or more of your mods. Would you like to open the RedUI mod page?",
		"RedUI version mismatch!",
		MB_ICONERROR | MB_YESNO
	);
	if (res == IDYES)
		ShellExecute(
			nullptr,
			"open",
			MOD_PAGE,
			nullptr,
			nullptr,
			SW_SHOWNORMAL
		);
	return (false);
}

void RedUI::Update()
{
	UIState::IsUpdating = true;
	// Update all animations.
	for (AnimationOwner &anim : UIState::Animations)
		if (anim->Update())
			UIState::QueuedFinishedAnimations.push_back(&anim); // Queue animation for removal if finished.
	// Set worldpositions and draw objects.
	for (const UIObjectOwner &obj : UIState::RootObjects)
		obj->RecursivelyUpdateAndDraw();
	UIState::IsUpdating = false;

	// Process queues.
	for (const auto &[obj, newParent] : UIState::QueuedHierarchyChanges)
		obj->SetParent(newParent);
	for (const AnimationOwner *anim : UIState::QueuedFinishedAnimations)
		std::erase(UIState::Animations, *anim);
	// Clear.
	UIState::QueuedHierarchyChanges.clear();
	UIState::QueuedFinishedAnimations.clear();
}

void RedUI::EmplaceNewObject(UIObject *parent, UIObjectOwner obj)
{
	obj->__RawSetParent(parent);
	if (parent == nullptr)
		UIState::RootObjects.push_back(std::move(obj));
	else
		parent->GetChildren().push_back(std::move(obj));
}

void RedUI::Remove(UIObject *&object)
{
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
