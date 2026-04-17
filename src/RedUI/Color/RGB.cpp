#include "RedUI/Color/RGB.h"

using namespace RedUI::Color;

RGB::RGB(const unsigned char r, const unsigned char g, const unsigned char b)
{
	R = r;
	G = g;
	B = b;
}

bool RGB::operator==(const RGB &other) const
{
	return (
		R == other.R &&
		G == other.G &&
		B == other.B
	);
}

static unsigned char Clamp(const int value)
{
	if (value > 255)
		return (255);
	if (value < 0)
		return (0);
	return (static_cast<unsigned char>(value));
}

RGB RGB::operator+(const RGB &other) const
{
	return (RGB(
		Clamp(static_cast<int>(R) + other.R),
		Clamp(static_cast<int>(G) + other.G),
		Clamp(static_cast<int>(B) + other.B)
	));
}

RGB RGB::operator-(const RGB &other) const
{
	return (RGB(
		Clamp(static_cast<int>(R) - other.R),
		Clamp(static_cast<int>(G) - other.G),
		Clamp(static_cast<int>(B) - other.B)
	));
}

RGB RGB::operator*(const RGB &other) const
{
	return (RGB(
		Clamp(static_cast<int>(R) * other.R),
		Clamp(static_cast<int>(G) * other.G),
		Clamp(static_cast<int>(B) * other.B)
	));
}

RGB &RGB::operator+=(const RGB &other)
{
	R = Clamp(static_cast<int>(R) + other.R);
	G = Clamp(static_cast<int>(G) + other.G);
	B = Clamp(static_cast<int>(B) + other.B);
	return (*this);
}

RGB &RGB::operator-=(const RGB &other)
{
	R = Clamp(static_cast<int>(R) - other.R);
	G = Clamp(static_cast<int>(G) - other.G);
	B = Clamp(static_cast<int>(B) - other.B);
	return (*this);
}

RGB &RGB::operator*=(const RGB &other)
{
	R = Clamp(static_cast<int>(R) * other.R);
	G = Clamp(static_cast<int>(G) * other.G);
	B = Clamp(static_cast<int>(B) * other.B);
	return (*this);
}
