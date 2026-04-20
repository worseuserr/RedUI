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
	// Required to not copy static members of UIStates when compiling.
	void	EmplaceNewObject(UIObject *parent, UIObjectOwner obj);
	// Creates a UI component on the heap and returns a raw pointer to it. If parent is nullptr, the component is root.
	// Default UIObject constuctor parameters: Position, Scale, Color, Alpha
	template <typename T, typename ...Args>
	requires (std::derived_from<T, UIObject> && (std::is_abstract_v<T> || std::constructible_from<T, Args...>)) // Constructible check has to be here or bitchass resharper wont show parameter hints.
	T		*Create(UIObject *parent, Args&&... args)
	{
		static_assert(!std::is_abstract_v<T>, "T is an abstract class. Did you forget to implement a pure virtual function?");
		static_assert(std::is_constructible_v<T, Args...>, "T cannot be constructed with the provided arguments.");
		T					*raw;
		std::unique_ptr<T>	obj = std::make_unique<T>(std::forward<Args>(args)...);

		raw = obj.get();
		EmplaceNewObject(parent, std::move(obj));
		return (raw);
	}
	// Remove ui component from screen by ptr returned by Create. Sets the ptr to nullptr.
	void	Remove(UIObject *&object);
	// Force mouse cursor to show even while ingame.
	void	EnableCursor();
	// Disable forced cursor.
	void	ResetCursor();
	// Disable left and right clicks from registering ingame (shooting, aiming, etc).
	void	DisableMouseInputs();
	// Reallow ingame mouse inputs.
	void	ResetMouseInputs();
}
