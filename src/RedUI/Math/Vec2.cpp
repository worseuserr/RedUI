#include "RedUI/Math/Vec2.h"

using namespace RedUI::Math;

Vec2::Vec2(const float x, const float y)
{
	X = x;
	Y = y;
}

Vec2	Vec2::Lerp(const Vec2 &dest, const float t) const
{
	return (Vec2(
		X + (dest.X - X) * t,
		Y + (dest.Y - Y) * t
	));
}

bool Vec2::operator==(const Vec2 &other) const
{
	return (
		X == other.X &&
		Y == other.Y
	);
}

Vec2 Vec2::operator+(const Vec2 &other) const
{
	return (Vec2(
		X + other.X,
		Y + other.Y
	));
}

Vec2 Vec2::operator-(const Vec2 &other) const
{
	return (Vec2(
		X - other.X,
		Y - other.Y
	));
}

Vec2 Vec2::operator*(const Vec2 &other) const
{
	return (Vec2(
		X * other.X,
		Y * other.Y
	));
}

Vec2 Vec2::operator+(const float &other) const
{
	return (Vec2(
		X + other,
		Y + other
	));
}

Vec2 Vec2::operator-(const float &other) const
{
	return (Vec2(
		X - other,
		Y - other
	));
}

Vec2 Vec2::operator*(const float &other) const
{
	return (Vec2(
		X * other,
		Y * other
	));
}

Vec2 &Vec2::operator+=(const Vec2 &other)
{
	X += other.X;
	Y += other.Y;
	return (*this);
}

Vec2 &Vec2::operator-=(const Vec2 &other)
{
	X -= other.X;
	Y -= other.Y;
	return (*this);
}

Vec2 &Vec2::operator*=(const Vec2 &other)
{
	X *= other.X;
	Y *= other.Y;
	return (*this);
}
