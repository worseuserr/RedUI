#include "RedUI/Math/Vec3.h"

using namespace RedUI::Math;

Vec3::Vec3(const float x, const float y, const float z)
{
	X = x;
	Y = y;
	Z = z;
}

Vec3	Vec3::Lerp(const Vec3 &dest, const float t) const
{
	return (Vec3(
		X + (dest.X - X) * t,
		Y + (dest.Y - Y) * t,
		Z + (dest.Z - Z) * t
	));
}

Vec3 Vec3::operator+(const Vec3 &other) const
{
	return (Vec3(
		X + other.X,
		Y + other.Y,
		Z + other.Z
	));
}

Vec3 Vec3::operator-(const Vec3 &other) const
{
	return (Vec3(
		X - other.X,
		Y - other.Y,
		Z - other.Z
	));
}

Vec3 Vec3::operator*(const Vec3 &other) const
{
	return (Vec3(
		X * other.X,
		Y * other.Y,
		Z * other.Z
	));
}

Vec3 &Vec3::operator+=(const Vec3 &other)
{
	X += other.X;
	Y += other.Y;
	Z += other.Z;
	return (*this);
}

Vec3 &Vec3::operator-=(const Vec3 &other)
{
	X -= other.X;
	Y -= other.Y;
	Z -= other.Z;
	return (*this);
}

Vec3 &Vec3::operator*=(const Vec3 &other)
{
	X *= other.X;
	Y *= other.Y;
	Z *= other.Z;
	return (*this);
}
