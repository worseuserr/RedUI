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

void RedUI::EnableCursor()
{
	UIState::CursorEnabled = true;
}

void RedUI::ResetCursor()
{
	UIState::CursorEnabled = false;
}

void RedUI::DisableMouseInputs()
{
	UIState::MouseInputsDisabled = true;
}

void RedUI::ResetMouseInputs()
{
	UIState::MouseInputsDisabled = false;
}
