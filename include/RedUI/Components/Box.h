#pragma once
#include "RedUI/UIObject.h"
#include "RedUI/Graphics/Sprite.h"

namespace RedUI
{
	class	Box : public UIObject
	{
	protected:
		void	Draw() override;

	public:
		// An optional sprite to display as the background instead of a solid color.
		Sprite	*Sprite = nullptr;

		using	UIObject::UIObject;
		bool	ContainsPoint(const Math::Vec2 &point) override;
	};
}
