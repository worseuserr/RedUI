#pragma once

#include "RedUI/UIObject.h"

namespace RedUI
{
	constexpr unsigned int	VERSION = 1;
	constexpr const char	*MOD_PAGE = "https://example.com";

	// Returns false if current RedUI version is below passed version.
	bool	CheckVersion(unsigned int version);
	// Shows an error message and returns false if RedUI version is below passed version.
	bool	RequireVersion(unsigned int version);
	// Updates all UI components. This must be called every frame.
	void	Update();
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
		EmplaceNewObject(parent, std::move(obj));
		return (raw);
	}
	// Remove ui component from screen by original reference. Sets the reference to nullptr.
	void	Remove(UIObject *&object);
}
