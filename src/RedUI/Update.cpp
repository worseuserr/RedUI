#include "RedUI/Remove.h"
#include "RedUI/UIState.h"
#include "RedUI/Input/Mouse.h"
#include "Sdk/natives.h"

void RedUI::Update()
{
	FrameState	state;

	if (UIState::CursorEnabled)
		_NAMESPACE30::_SET_MOUSE_CURSOR_ACTIVE_THIS_FRAME();
	if (UIState::MouseInputsDisabled)
	{
		PAD::DISABLE_CONTROL_ACTION(0, Input::INPUT_ATTACK, true);
		PAD::DISABLE_CONTROL_ACTION(0, Input::INPUT_AIM, true);
	}
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
	for (UIObject *obj: UIState::QueuedObjectDeletions)
		Remove(obj);
	for (const auto &[obj, newParent] : UIState::QueuedHierarchyChanges)
		obj->SetParent(newParent);
	for (const AnimationOwner *anim : UIState::QueuedFinishedAnimations)
		std::erase(UIState::Animations, *anim);
	// Clear.
	UIState::QueuedHierarchyChanges.clear();
	UIState::QueuedFinishedAnimations.clear();
	UIState::QueuedObjectDeletions.clear();
}
