#include "RedUI/Color/Dropshadow.h"

using namespace RedUI::Color;

Dropshadow::Dropshadow(const unsigned char distance, const RGB color, const float alpha)
{
	Distance = distance;
	Color = color;
	Alpha = alpha;
}

bool Dropshadow::operator==(const Dropshadow &other) const
{
	return (
		Distance == other.Distance &&
		Color == other.Color &&
		Alpha == other.Alpha
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

static float FClamp(const float value)
{
	if (value > 1.0f)
		return (1.0f);
	if (value < 0.0f)
		return (0.0f);
	return (value);
}

Dropshadow Dropshadow::operator+(const Dropshadow &other) const
{
	return (Dropshadow(
		Clamp(static_cast<int>(Distance) + other.Distance),
		Color + other.Color,
		FClamp(Alpha + other.Alpha)
	));
}

Dropshadow Dropshadow::operator-(const Dropshadow &other) const
{
	return (Dropshadow(
		Clamp(static_cast<int>(Distance) - other.Distance),
		Color - other.Color,
		FClamp(Alpha - other.Alpha)
	));
}

Dropshadow Dropshadow::operator*(const Dropshadow &other) const
{
	return (Dropshadow(
		Clamp(static_cast<int>(Distance) * other.Distance),
		Color * other.Color,
		FClamp(Alpha * other.Alpha)
	));
}

Dropshadow &Dropshadow::operator+=(const Dropshadow &other)
{
	Distance = Clamp(static_cast<int>(Distance) + other.Distance);
	Color = Color + other.Color;
	Alpha = FClamp(Alpha + other.Alpha);
	return (*this);
}

Dropshadow &Dropshadow::operator-=(const Dropshadow &other)
{
	Distance = Clamp(static_cast<int>(Distance) - other.Distance);
	Color = Color - other.Color;
	Alpha = FClamp(Alpha - other.Alpha);
	return (*this);
}

Dropshadow &Dropshadow::operator*=(const Dropshadow &other)
{
	Distance = Clamp(static_cast<int>(Distance) * other.Distance);
	Color = Color * other.Color;
	Alpha = FClamp(Alpha * other.Alpha);
	return (*this);
}
