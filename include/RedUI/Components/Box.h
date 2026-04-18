#pragma once
#include "RedUI/UIObject.h"

namespace RedUI
{
	class	Box : public UIObject
	{
	public:
		using	UIObject::UIObject;
		void	Draw() override;
	};
}
