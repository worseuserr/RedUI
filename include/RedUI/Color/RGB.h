#pragma once
#undef RGB // Windows RGB macro.

namespace RedUI::Color
{
	class	RGB
	{
	public:
		unsigned char	R;
		unsigned char	G;
		unsigned char	B;

		RGB(unsigned char r = 255, unsigned char g = 255, unsigned char b = 255);
		bool	operator==(const RGB &other) const;
		RGB		operator+(const RGB &other) const;
		RGB		operator-(const RGB &other) const;
		RGB		operator*(const RGB &other) const;
		RGB		&operator+=(const RGB &other);
		RGB		&operator-=(const RGB &other);
		RGB		&operator*=(const RGB &other);
	};
}
