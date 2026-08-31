#include "RedUI/Focus.h"
#include <format>
#include "RedUI/Debug.h"
#include "RedUI/Input/Mouse.h"

using namespace RedUI;

unsigned int	Focus::Refs[3]{0, 0, 0};
Focus			Focus::State{};

void Focus::Tick()
{
	if (IsActive(Cursor))
		_NAMESPACE30::_SET_MOUSE_CURSOR_ACTIVE_THIS_FRAME();
	if (IsActive(DisableInput))
	{
		PAD::DISABLE_CONTROL_ACTION(0, Input::INPUT_ATTACK, true);
		PAD::DISABLE_CONTROL_ACTION(0, Input::INPUT_AIM, true);
	}
}

bool Focus::IsActive(const Focus flag)
{
	return ((State & flag) != 0);
}

void FocusHandle::UpdateSingleState(const int change, const int index, const Focus flag) const
{
	if ((Flags & flag) != Focus::None)
		Focus::Refs[index] += change;
	if (Focus::Refs[index] > 0)
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
	Debug::Log(std::format("Focus acquired ({:p}), flags: Cursor: {}, Interaction: {}, DisableInput: {}",
		static_cast<void *>(this),
		flags.Has(Focus::Cursor),
		flags.Has(Focus::Interaction),
		flags.Has(Focus::DisableInput)));
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
	Debug::Log(std::format("Focus released ({:p}), flags: Cursor: {}, Interaction: {}, DisableInput: {}",
		static_cast<void *>(this),
		Flags.Has(Focus::Cursor),
		Flags.Has(Focus::Interaction),
		Flags.Has(Focus::DisableInput)));
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
	Debug::Log(std::format("Focus moved {:p} -> {:p}", static_cast<void *>(&other), static_cast<void *>(this)));
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
