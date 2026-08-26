#pragma once
#include "RGB.h"

namespace RedUI::Color
{
	class	Dropshadow
	{
	public:
		unsigned char	Distance;
		RGB				Color;
		float			Opacity;

		Dropshadow(unsigned char distance = 0, RGB color = {0, 0, 0}, float opacity = 1.0f);
		bool			operator==(const Dropshadow &other) const;
		Dropshadow		operator+(const Dropshadow &other) const;
		Dropshadow		operator-(const Dropshadow &other) const;
		Dropshadow		operator*(const Dropshadow &other) const;
		Dropshadow		&operator+=(const Dropshadow &other);
		Dropshadow		&operator-=(const Dropshadow &other);
		Dropshadow		&operator*=(const Dropshadow &other);
	};
}
