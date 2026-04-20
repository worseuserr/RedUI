#pragma once
#include "UIObject.h"

namespace RedUI
{
	// Remove ui component from screen by ptr returned by Create. Sets the ptr to nullptr.
	void	Remove(UIObject *&object);
}
