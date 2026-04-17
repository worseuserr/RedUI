#pragma once

namespace RedUI::Math
{
	// Vec2 instead of Vector3 because the scripthook sdk has a Vector3 type.
	class	Vec2
	{
	public:
		float	X;
		float	Y;

		Vec2(float x = 0, float y = 0);
		Vec2	Lerp(const Vec2 &dest, float t) const;
		bool	operator==(const Vec2 &other) const;
		Vec2	operator+(const Vec2 &other) const;
		Vec2	operator-(const Vec2 &other) const;
		Vec2	operator*(const Vec2 &other) const;
		Vec2	&operator+=(const Vec2 &other);
		Vec2	&operator-=(const Vec2 &other);
		Vec2	&operator*=(const Vec2 &other);
	};

}
