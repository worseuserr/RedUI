#pragma once

namespace RedUI::Math
{
	class	Angle
	{
		float			Degrees;

		// Normalize an angle to 0-360 degrees.
		static float	Normalize(float angleDegrees);

	public:
		Angle();
		Angle(float degrees);
		Angle(int degrees);

		float	ToDegrees() const;

		Angle	operator+(const Angle &other) const;
		Angle	&operator+=(const Angle &other);
		Angle	operator-(const Angle &other) const;
		Angle	&operator-=(const Angle &other);
		Angle	operator*(const Angle &other) const;
		Angle	&operator*=(const Angle &other);
		Angle	operator/(const Angle &other) const;
		Angle	&operator/=(const Angle &other);
	};
}
