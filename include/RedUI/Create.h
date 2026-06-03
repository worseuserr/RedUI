#pragma once
#include "UIObject.h"

namespace RedUI
{
	// Required to not copy static members of UIStates when compiling.
	void	EmplaceNewObject(UIObject *parent, UIObjectOwner obj);

	// Creates a UI component on the heap and returns a raw pointer to it. If parent is nullptr, the component is root.
	// Default UIObject constuctor parameters: Position, Scale, Color, Alpha
	template <typename T, typename ...Args>
	requires (std::derived_from<T, UIObject> && std::constructible_from<T, Args...>)
	T		*Create(UIObject *parent, Args&&... args)
	{
		T					*raw;
		std::unique_ptr<T>	obj = std::make_unique<T>(std::forward<Args>(args)...);

		raw = obj.get();
		obj->SetParent(parent, true);
		return (raw);
	}
}
