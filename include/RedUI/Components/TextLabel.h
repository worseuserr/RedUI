#pragma once
#include "RedUI/UIObject.h"
#include "RedUI/Color/Dropshadow.h"

namespace RedUI
{
	class	TextLabel : public UIObject
	{
	public:
		using				UIObject::UIObject;
		Color::Dropshadow	Dropshadow;
		float				TextScale;
		std::string			Text;

		void	Draw() override;
	};
}
