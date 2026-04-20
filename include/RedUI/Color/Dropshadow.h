#pragma once

#include "RedUI/Color/RGB.h"

namespace RedUI::Color
{
	class	Dropshadow
	{
	public:
		unsigned char	Distance;
		RGB				Color;
		float			Alpha;

		Dropshadow(unsigned char distance, RGB color = {0, 0, 0}, float alpha = 1.0f);
		bool			operator==(const Dropshadow &other) const;
		Dropshadow		operator+(const Dropshadow &other) const;
		Dropshadow		operator-(const Dropshadow &other) const;
		Dropshadow		operator*(const Dropshadow &other) const;
		Dropshadow		&operator+=(const Dropshadow &other);
		Dropshadow		&operator-=(const Dropshadow &other);
		Dropshadow		&operator*=(const Dropshadow &other);
	};
}
