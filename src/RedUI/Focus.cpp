#include "RedUI/Focus.h"
#include "RedUI/UIState.h"

using namespace RedUI;

unsigned int	Focus::Refs[3]{0, 0, 0};
Focus			Focus::State{};

void Focus::Tick()
{
	if ((State & Cursor) != 0)
		_NAMESPACE30::_SET_MOUSE_CURSOR_ACTIVE_THIS_FRAME();
	if (UIState::MouseInputsDisabled)
	{
		PAD::DISABLE_CONTROL_ACTION(0, Input::INPUT_ATTACK, true);
		PAD::DISABLE_CONTROL_ACTION(0, Input::INPUT_AIM, true);
	}
}

void FocusHandle::UpdateSingleState(const int change, const int index, const Focus flag) const
{
	if ((Flags & flag) != Focus::None)
		Focus::Refs[0] += change;
	if (Focus::Refs[0] > 0)
		Focus::State |= flag;
}

void FocusHandle::UpdateFocusState(const int change) const
{
	Focus::State = 0;
	UpdateSingleState(change, 0, Focus::Cursor);
	UpdateSingleState(change, 1, Focus::Interaction);
	UpdateSingleState(change, 2, Focus::DisableInput);
}

void FocusHandle::UnregisterFlags() const
{
	UpdateFocusState(-1);
}

void FocusHandle::RegisterFlags() const
{
	UpdateFocusState(1);
}

FocusHandle::FocusHandle(const Focus flags, const bool isValid)
{
	Flags = flags;
	Valid = isValid;
	if (isValid)
		RegisterFlags();
}

FocusHandle::~FocusHandle()
{
	if (Valid)
		Release();
}

void FocusHandle::Release()
{
	if (Valid)
		UnregisterFlags();
	Valid = false;
}

FocusHandle::operator bool() const
{
	return (Valid);
}

FocusHandle::FocusHandle(FocusHandle&& other) noexcept
{
	Flags = other.Flags;
	Valid = other.Valid;
	other.Valid = false;
}

FocusHandle& FocusHandle::operator=(FocusHandle&& other) noexcept
{
	if (this != &other)
	{
		Release();
		Flags = other.Flags;
		Valid = other.Valid;
		other.Valid = false;
	}
	return (*this);
}

FocusHandle RedUI::AcquireUIFocus(const Focus flags)
{
	return (FocusHandle(flags, true));
}
