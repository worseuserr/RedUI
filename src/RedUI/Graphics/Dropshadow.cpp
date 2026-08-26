#include "../../../include/RedUI/Graphics/Dropshadow.h"

using namespace RedUI::Color;

Dropshadow::Dropshadow(const unsigned char distance, const RGB color, const float opacity)
{
	Distance = distance;
	Color = color;
	Opacity = opacity;
}

bool Dropshadow::operator==(const Dropshadow &other) const
{
	return (
		Distance == other.Distance &&
		Color == other.Color &&
		Opacity == other.Opacity
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
		FClamp(Opacity + other.Opacity)
	));
}

Dropshadow Dropshadow::operator-(const Dropshadow &other) const
{
	return (Dropshadow(
		Clamp(static_cast<int>(Distance) - other.Distance),
		Color - other.Color,
		FClamp(Opacity - other.Opacity)
	));
}

Dropshadow Dropshadow::operator*(const Dropshadow &other) const
{
	return (Dropshadow(
		Clamp(static_cast<int>(Distance) * other.Distance),
		Color * other.Color,
		FClamp(Opacity * other.Opacity)
	));
}

Dropshadow &Dropshadow::operator+=(const Dropshadow &other)
{
	Distance = Clamp(static_cast<int>(Distance) + other.Distance);
	Color = Color + other.Color;
	Opacity = FClamp(Opacity + other.Opacity);
	return (*this);
}

Dropshadow &Dropshadow::operator-=(const Dropshadow &other)
{
	Distance = Clamp(static_cast<int>(Distance) - other.Distance);
	Color = Color - other.Color;
	Opacity = FClamp(Opacity - other.Opacity);
	return (*this);
}

Dropshadow &Dropshadow::operator*=(const Dropshadow &other)
{
	Distance = Clamp(static_cast<int>(Distance) * other.Distance);
	Color = Color * other.Color;
	Opacity = FClamp(Opacity * other.Opacity);
	return (*this);
}
