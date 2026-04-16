#pragma once

#include <unordered_set>
#include <vector>
#include "Color/RGB.h"
#include "Math/Vec3.h"

namespace RedUI
{
	// Base class for all ui components.
	class	UIObject
	{
	protected:
		UIObject				*Parent = nullptr;
		std::vector<UIObject *>	Children = {};
		Math::Vec3				WorldPosition = Math::Vec3();
		Math::Vec3				WorldScale = Math::Vec3();

	public:

		bool       Enabled;
		Math::Vec3 Position;
		Math::Vec3 Scale;
		Color::RGB Color;
		float      Alpha;

		UIObject(Math::Vec3 position = Math::Vec3(), Math::Vec3 scale = Math::Vec3(1, 1, 1),
			Color::RGB color = Color::RGB(), float alpha = 1.0f, UIObject *parent = nullptr);
		virtual			~UIObject() = default;
		// Set parent of object. Parent is root (unparented) if nullptr or no argument.
		void					SetParent(UIObject *newParent = nullptr);
		UIObject				*GetParent() const;
		std::vector<UIObject *>	GetChildren() const;
		virtual void			Draw() const;
	};
}
