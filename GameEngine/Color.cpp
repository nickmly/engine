#include "Color.h"
#include <sstream>
#include "BasicTypes.h"

std::ostream& operator<<(std::ostream &os, const Color &clr)
{
	os << "(" << clr.r << ", " << clr.g << ", " << clr.b << ", " << clr.a << ")";
	return os;
}

std::string Color::toString()
{
	std::stringstream ss;
	ss << *this;
	return ss.str();
}

bool operator==(const Color &c1, const Color &c2)
{
	return c1.r == c2.r &&
		c1.g == c2.g &&
		c1.b == c2.b &&
		c1.a == c2.a;
}

Color::Color(const std::string& clrString)
{
	if (clrString[0] == '#')
	{
		std::string tmp = clrString.substr(1);
		(*this) = hexToColor(tmp);
	}
	else if (clrString[0] == '%')
	{
		std::string tmp = clrString.substr(1);
		(*this) = intToColor(tmp);
	}
	else (*this) = nameToColor(clrString);
}

Color Color::hexToColor(const std::string& clrName)
{
	int vals[4];
	int len = clrName.size();
	std::string tmp;

	vals[3] = 255;

	for (int i = 0, j = 0; i < len; i += 2, j++)
	{
		tmp = clrName.substr(i, 2);
		vals[j] = TypeServices::stringHexToInt(tmp);
	}
	return Color(vals[0], vals[1], vals[2], vals[3]);
}

Color Color::intToColor(const std::string& clrName)
{
	int vals[4];
	int len = clrName.size();
	std::string tmp;

	vals[3] = 255;

	for (int i = 0, j = 0; i < len; i += 3, j++)
	{
		tmp = clrName.substr(i, 3);
		vals[j] = TypeServices::stringIntToInt(tmp);
	}
	return Color(vals[0], vals[1], vals[2], vals[3]);
}


Color Color::nameToColor(const std::string& clrName)
{
	if (clrName == std::string("red") || clrName == std::string("RED")) return RED;
	if (clrName == std::string("green") || clrName == std::string("GREEN")) return GREEN;
	if (clrName == std::string("blue") || clrName == std::string("BLUE")) return BLUE;
	if (clrName == std::string("yellow") || clrName == std::string("YELLOW")) return YELLOW;
	if (clrName == std::string("white") || clrName == std::string("WHITE")) return WHITE;
	if (clrName == std::string("black") || clrName == std::string("BLACK")) return BLACK;
	if (clrName == std::string("pink") || clrName == std::string("PINK")) return PINK;
	if (clrName == std::string("violet") || clrName == std::string("VIOLET")) return VIOLET;
	if (clrName == std::string("purple") || clrName == std::string("PURPLE")) return PURPLE;
	if (clrName == std::string("darkslategray") || clrName == std::string("DARKSLATEGRAY")) return DARKSLATEGRAY;
	if (clrName == std::string("springgreen") || clrName == std::string("SPRINGGREEN")) return SPRINGGREEN;
	if (clrName == std::string("seagreen") || clrName == std::string("SEAGREEN")) return SEAGREEN;
	if (clrName == std::string("emeraldgreen") || clrName == std::string("EMERALDGREEN")) return EMERALDGREEN;
	if (clrName == std::string("aquamarine") || clrName == std::string("AQUAMARINE")) return AQUAMARINE;
	if (clrName == std::string("teal") || clrName == std::string("TEAL")) return TEAL;
	if (clrName == std::string("gold") || clrName == std::string("GOLD")) return GOLD;
	if (clrName == std::string("orange") || clrName == std::string("ORANGE")) return ORANGE;
	if (clrName == std::string("brick") || clrName == std::string("BRICK")) return BRICK;
	if (clrName == std::string("tan") || clrName == std::string("TAN")) return TAN;
	if (clrName == std::string("chocolate") || clrName == std::string("CHOCOLATE")) return CHOCOLATE;
	if (clrName == std::string("sienna") || clrName == std::string("SIENNA")) return SIENNA;
	if (clrName == std::string("brown") || clrName == std::string("BROWN")) return BROWN;
	if (clrName == std::string("gray") || clrName == std::string("GRAY")) return GRAY;
	return BLACK;
}

const Color Color::RED(1.0f, 0.0f, 0.0f, 1.0f);
const Color Color::GREEN(0.0f, 1.0f, 0.0f, 1.0f);
const Color Color::BLUE(0.0f, 0.0f, 1.0f, 1.0f);
const Color Color::YELLOW(1.0f, 1.0f, 0.0f, 1.0f);
const Color Color::WHITE(1.0f, 1.0f, 1.0f, 1.0f);
const Color Color::BLACK(0.0f, 0.0f, 0.0f, 1.0f);
const Color Color::PINK(1.0f, 0.75294f, 0.79608f, 1.0f);
const Color Color::VIOLET(0.933333f, 0.5098f, 0.933333f, 1.0f);
const Color Color::PURPLE(0.50196f, 0.0f, 0.50196f, 1.0f);
const Color Color::DARKSLATEGRAY(0.184314f, 0.3098f, 0.3098f, 1.0f);
const Color Color::SPRINGGREEN(0, 255, 127, 255);
const Color Color::SEAGREEN(84, 255, 159, 255);
const Color Color::EMERALDGREEN(0, 201, 87, 255);
const Color Color::AQUAMARINE(127, 255, 212, 255);
const Color Color::TEAL(0, 128, 128, 255);
const Color Color::GOLD(255, 215, 0, 255);
const Color Color::ORANGE(255, 165, 0, 255);
const Color Color::BRICK(156, 102, 31, 255);
const Color Color::TAN(255, 165, 79, 255);
const Color Color::CHOCOLATE(210, 105, 30, 255);
const Color Color::SIENNA(160, 82, 45, 255);
const Color Color::BROWN(165, 42, 42, 255);
const Color Color::GRAY(128, 128, 128, 255);
