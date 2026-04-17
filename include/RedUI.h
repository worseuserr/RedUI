#pragma once
#include "RedUI/UIObject.h"
#include "RedUI/UIState.h"

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
	// Creates a UI component on the heap and returns a non-owning raw pointer to it. If parent is nullptr, the component is root.
	template <typename T, typename ...Args>
	requires (std::derived_from<T, UIObject>)
	T		*Create(UIObject *parent, Args&&... args)
	{
		T					*raw;
		std::unique_ptr<T>	obj = std::make_unique<T>(std::forward<Args>(args)...);

		raw = obj.get();
		if (parent == nullptr)
			UIState::RootObjects.push_back(std::move(obj));
		else
			parent->GetChildren().push_back(std::move(obj));
		return (raw);
	}
	// Remove ui component from screen by reference.
	void	Remove(UIObject *object);
}
