#pragma once
#include "RedUI/UIObject.h"
#include "RedUI/Graphics/Sprite.h"

namespace RedUI
{
	class	Box : public UIObject
	{
	public:
		// An optional sprite to display as the background instead of a solid color.
		Sprite	*Sprite = nullptr;

		using	UIObject::UIObject;
		void	Draw() override;
		bool	ContainsPoint(const Math::Vec2 &point) override;
	};
}
