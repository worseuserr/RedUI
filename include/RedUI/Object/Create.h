#pragma once
#include "UIObject.h"
#include "RedUI/Debug.h"

namespace RedUI::Object
{
	void	ParentNewUIObject(UIObjectOwner obj, UIObject *newParent);

	// Creates a UI component on the heap and returns a raw pointer to it. If parent is nullptr, the component is root.
	// Default UIObject constructor parameters: Position, Scale, Color, Opacity
	template <typename T, typename ...Args>
	requires (std::derived_from<T, UIObject> && std::constructible_from<T, Args...>)
	T		*Create(UIObject *parent, Args&&... args)
	{
		T					*raw;
		std::unique_ptr<T>	obj = std::make_unique<T>(std::forward<Args>(args)...);

		raw = obj.get();
		Debug::Log(std::format(
			"New UIObject created: {:p} ({}), parent: {:p} ({})",
			static_cast<void *>(raw),
			obj->Name(),
			static_cast<void *>(parent),
			parent ? parent->Name() : "nullptr"
		));
		Object::ParentNewUIObject(std::move(obj), parent);
		return (raw);
	}
}

// UI_CREATE is in UIComponent.h.
