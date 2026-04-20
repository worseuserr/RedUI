#include "RedUI.h"
#include "RedUI/UIState.h"
#include "RedUI/Input/Mouse.h"
#include "Sdk/natives.h"

void RedUI::Update()
{
	FrameState	state;

	if (UIState::IsCursorEnabled)
		_NAMESPACE30::_SET_MOUSE_CURSOR_ACTIVE_THIS_FRAME();

	UIState::IsUpdating = true;
	// Update all animations.
	for (AnimationOwner &anim : UIState::Animations)
		if (anim->Update())
			UIState::QueuedFinishedAnimations.push_back(&anim); // Queue animation for removal if finished.
	// Set worldpositions and draw objects.
	state = {
		.IsLeftMouseDown = Input::IsLeftMouseDown(),
		.IsRightMouseDown = Input::IsRightMouseDown(),
		.MousePosition = Input::GetMousePosition()
	};
	for (const UIObjectOwner &obj : UIState::RootObjects)
		obj->RecursivelyUpdateAndDraw(state);
	UIState::IsUpdating = false;

	// Process queues.
	// TODO: add deletion queue
	for (const auto &[obj, newParent] : UIState::QueuedHierarchyChanges)
		obj->SetParent(newParent);
	for (const AnimationOwner *anim : UIState::QueuedFinishedAnimations)
		std::erase(UIState::Animations, *anim);
	// Clear.
	UIState::QueuedHierarchyChanges.clear();
	UIState::QueuedFinishedAnimations.clear();
}
