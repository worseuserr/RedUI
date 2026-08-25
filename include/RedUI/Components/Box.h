#pragma once
#include "RedUI/UIComponent.h"
#include "RedUI/Graphics/Sprite.h"

namespace RedUI::Components
{
	class	Box : public UIComponent
	{
	protected:
		void	Draw() override;

	public:
		UI_CREATE(Box)
		// An optional sprite to display as the background instead of a solid color.
		Sprite	*Sprite = nullptr;

		using	UIComponent::UIComponent;
		bool	ContainsPoint(const Math::Vec2 &point) override;
	};
}
