#include "RedUI/Remove.h"
#include "RedUI/UIState.h"
#include "RedUI/Input/Mouse.h"
#include "Sdk/natives.h"

using namespace RedUI;

constexpr BYTE	LMB = 1 << 0;
constexpr BYTE	RMB = 1 << 1;

BYTE ProcessStaticMouseEvents()
{
	static bool	wasLeftMouseDown = false;
	static bool	wasRightMouseDown = false;
	bool		isLeftMouseDown;
	bool		isRightMouseDown;
	BYTE		res;

	isLeftMouseDown = Input::IsLeftMouseDown();
	isRightMouseDown = Input::IsRightMouseDown();
	if (isLeftMouseDown != wasLeftMouseDown)
	{
		if (isLeftMouseDown)
			Input::Events::OnLeftMouseDown.Invoke(nullptr, { wasLeftMouseDown, isLeftMouseDown });
		else
			Input::Events::OnLeftMouseUp.Invoke(nullptr, { wasLeftMouseDown, isLeftMouseDown });
	}
	if (isRightMouseDown != wasRightMouseDown)
	{
		if (isRightMouseDown)
			Input::Events::OnRightMouseDown.Invoke(nullptr, { wasRightMouseDown, isRightMouseDown });
		else
			Input::Events::OnRightMouseUp.Invoke(nullptr, { wasRightMouseDown, isRightMouseDown });
	}
	res = (0 |
		((!wasLeftMouseDown && isLeftMouseDown) ? LMB : 0) |
		((!wasRightMouseDown && isRightMouseDown) ? RMB : 0)
		);
	wasLeftMouseDown = isLeftMouseDown;
	wasRightMouseDown = isRightMouseDown;
	return (res);
}

void RedUI::Update()
{
	size_t		i;
	BYTE		clicks;

	clicks = ProcessStaticMouseEvents();
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
		.IsLeftMouseClicked = (clicks & LMB) != 0,
		.IsRightMouseClicked = (clicks & RMB) != 0,
		.MousePosition = Input::GetMousePosition()
	};
	if (UIState::InteractionEnabled)
	{
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
