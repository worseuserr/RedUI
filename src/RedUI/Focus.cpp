#include "RedUI/Focus.h"
#include "RedUI/UIState.h"

using namespace RedUI;

void FocusHandle::UpdateFocusState(const int change) const
{
	if ((Flags & Focus::Cursor) != Focus::None)
		UIState::Focus.CursorRefs += change;
	if ((Flags & Focus::Interaction) != Focus::None)
		UIState::Focus.InteractionRefs += change;
	if ((Flags & Focus::DisableInput) != Focus::None)
		UIState::Focus.InputDisabledRefs += change;
	UIState::CursorEnabled = UIState::Focus.CursorRefs > 0;
	UIState::InteractionEnabled = UIState::Focus.InteractionRefs > 0;
	UIState::MouseInputsDisabled = UIState::Focus.InputDisabledRefs > 0;
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
