#pragma once
#include "UIObject.h"

namespace RedUI
{
	void	RemoveInternal(UIObject *object);

	// Remove ui component from screen by ptr returned by Create. Sets the ptr to nullptr.
	template	<typename T>
	void		Remove(T *&object)
	{
		static_assert(std::is_base_of_v<UIObject, T>, "Object must be a UIObject.");
		if (object == nullptr)
			return ;
		RemoveInternal(object);
		object = nullptr;
	}
}
