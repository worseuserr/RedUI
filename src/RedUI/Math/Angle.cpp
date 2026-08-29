#include "RedUI/Math/Angle.h"
#include <cmath>

using namespace RedUI;

float Math::Angle::Normalize(float angleDegrees)
{
	// Wrap 360s.
	angleDegrees = std::fmod(angleDegrees, (angleDegrees < 0) ? -360.0f : 360.0f);

	if (angleDegrees < 0)
		angleDegrees = 360.0f - std::abs(angleDegrees);
	return (angleDegrees);
}

Math::Angle::Angle()
{
	Degrees = 0.0f;
}

Math::Angle::Angle(const float degrees)
{
	Degrees = degrees;
}

Math::Angle::Angle(const int degrees)
{
	Degrees = static_cast<float>(degrees);
}

float Math::Angle::ToDegrees() const
{
	return (Degrees);
}

Math::Angle Math::Angle::operator+(const Angle &other) const
{
	return (Normalize(Degrees + other.Degrees));
}

Math::Angle &Math::Angle::operator+=(const Angle &other)
{
	Degrees = Normalize(Degrees + other.Degrees);
	return (*this);
}

Math::Angle Math::Angle::operator-(const Angle &other) const
{
	return (Normalize(Degrees - other.Degrees));
}

Math::Angle &Math::Angle::operator-=(const Angle &other)
{
	Degrees = Normalize(Degrees - other.Degrees);
	return (*this);
}

Math::Angle Math::Angle::operator*(const Angle &other) const
{
	return (Normalize(Degrees * other.Degrees));
}

Math::Angle &Math::Angle::operator*=(const Angle &other)
{
	Degrees = Normalize(Degrees * other.Degrees);
	return (*this);
}

Math::Angle Math::Angle::operator/(const Angle &other) const
{
	return (Normalize(Degrees / other.Degrees));
}

Math::Angle &Math::Angle::operator/=(const Angle &other)
{
	Degrees = Normalize(Degrees / other.Degrees);
	return (*this);
}
