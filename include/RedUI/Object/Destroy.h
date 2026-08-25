#pragma once
#include "UIObject.h"

namespace RedUI::Object
{
	// Destroy ui component from screen by ptr returned by Create. Sets the ptr to nullptr.
	template	<typename T>
	void		Destroy(T *&object)
	{
		static_assert(std::is_base_of_v<UIObject, T>, "Object must be a UIObject.");
		if (object == nullptr)
			return ;
		object->Destroy();
		object = nullptr;
	}
}
