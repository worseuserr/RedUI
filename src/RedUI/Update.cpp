#include "RedUI/Remove.h"
#include "RedUI/UIState.h"
#include "RedUI/Input/Mouse.h"
#include "Sdk/natives.h"

void RedUI::Update()
{
	static bool	LeftMouseDown = false;
	static bool	RightMouseDown = false;
	bool		LeftMouseDownNow;
	bool		RightMouseDownNow;
	size_t		i;

	LeftMouseDownNow = Input::IsLeftMouseDown();
	RightMouseDownNow = Input::IsRightMouseDown();
	if (LeftMouseDownNow != LeftMouseDown)
	{
		if (LeftMouseDownNow)
			Input::Events::OnLeftMouseDown.Invoke(nullptr, { LeftMouseDown, LeftMouseDownNow });
		else
			Input::Events::OnLeftMouseUp.Invoke(nullptr, { LeftMouseDown, LeftMouseDownNow });
	}
	if (RightMouseDownNow != RightMouseDown)
	{
		if (RightMouseDownNow)
			Input::Events::OnRightMouseDown.Invoke(nullptr, { RightMouseDown, RightMouseDownNow });
		else
			Input::Events::OnRightMouseUp.Invoke(nullptr, { RightMouseDown, RightMouseDownNow });
	}

	// Render loop.
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
		.IsLeftMouseClicked = !LeftMouseDown && LeftMouseDownNow,
		.IsRightMouseClicked = !RightMouseDown && RightMouseDownNow,
		.MousePosition = Input::GetMousePosition()
	};
	LeftMouseDown = LeftMouseDownNow;
	RightMouseDown = RightMouseDownNow;
	HitState	hitState = {
		.Frame = state,
		.LeftClickConsumed = false,
		.RightClickConsumed = false,
		.HoverConsumed = false,
		.FullyConsumed = false
	};
	// Process events backwards for newer children to occlude existing ones since that's how they render.
	for (i = UIState::RootObjects.size(); i-- > 0;)
	{
		UIState::RootObjects[i]->RecursivelyProcessEvents(hitState);
	}
	// Render forwards.
	for (i = 0; i < UIState::RootObjects.size(); i++)
	{
		UIState::RootObjects[i]->RecursivelyRender(state);
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
