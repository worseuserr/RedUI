#include "RedUI/Remove.h"
#include "RedUI/UIState.h"
#include "RedUI/Input/Mouse.h"
#include "Sdk/natives.h"

void RedUI::Update()
{
	if (UIState::IsUpdating)
		return ;
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
	FrameState	state = {
		.IsLeftMouseClicked = Input::IsLeftMouseDown(),
		.IsRightMouseClicked = Input::IsRightMouseDown(),
		.MousePosition = Input::GetMousePosition()
	};
	HitState	hitState = {
		.Frame = state,
		.LeftClickConsumed = false,
		.RightClickConsumed = false,
		.HoverConsumed = false,
		.FullyConsumed = false
	};
	for (const UIObjectOwner &obj : UIState::RootObjects)
	{
		obj->RecursivelyProcessEvents(hitState);
		obj->RecursivelyRender(state);
	}
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
