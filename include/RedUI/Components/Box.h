#pragma once
#include "RedUI/UIComponent.h"
#include "RedUI/Graphics/Sprite.h"

namespace RedUI::Components
{
	class	Box : public UIComponent
	{
	protected:
		// An optional sprite to display as the background.
		Sprite	*Sprite = nullptr;
		void	Draw() override;

	public:
		UI_CREATE(Box)
		using			UIComponent::UIComponent;
		Color::RGB		SpriteColor;
		float			SpriteOpacity;

		bool			ContainsPoint(const Math::Vec2 &point) override;
		void			SetSprite(RedUI::Sprite *sprite);
		RedUI:: Sprite	*GetSprite() const;
		void			AnimateSpriteColor(const Color::RGB &startValue, const Color::RGB &endValue, Time::Milliseconds duration, Easing easing = Easing::Linear);
		void			AnimateSpriteOpacity(float startValue, float endValue, Time::Milliseconds duration, Easing easing = Easing::Linear);
	};
}
