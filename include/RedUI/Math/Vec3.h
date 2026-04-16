#pragma once

namespace RedUI::Math
{
	// Vec3 instead of Vector3 because the scripthook sdk has a Vector3 type.
	class	Vec3
	{
	public:
		float	X;
		float	Y;
		float	Z;

		Vec3(float x = 0, float y = 0, float z = 0);
		Vec3	Lerp(const Vec3 &dest, float t) const;
		Vec3	operator+(const Vec3 &other) const;
		Vec3	operator-(const Vec3 &other) const;
		Vec3	operator*(const Vec3 &other) const;
		Vec3	&operator+=(const Vec3 &other);
		Vec3	&operator-=(const Vec3 &other);
		Vec3	&operator*=(const Vec3 &other);
	};

}
