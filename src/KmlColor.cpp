#include "KmlColor.h"
#include <algorithm>
#include <iomanip>
#include <cstdint>


namespace Kml
{
Color::Color(uint8 red, uint8 green, uint8 blue, uint8 alpha) : m_red{red}, m_green{green}, m_blue{blue}, m_alpha{alpha}
{
}

Color::Color(const std::string &s)
{
	// check size and first character
	int n = s.size();
	bool ok1a = (n == 8);
	bool ok1b = (n == 9 && s[0] == '#');
	if (!ok1a && !ok1b) {return;}

	int offset = ok1b ? 1 : 0;
	std::array<char,16> hexChars = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
	auto b = hexChars.begin();
	auto e = hexChars.end();

	auto a0 = std::find(b, e, std::tolower(s[offset+0]));
	auto a1 = std::find(b, e, std::tolower(s[offset+1]));
	auto b0 = std::find(b, e, std::tolower(s[offset+2]));
	auto b1 = std::find(b, e, std::tolower(s[offset+3]));
	auto g0 = std::find(b, e, std::tolower(s[offset+4]));
	auto g1 = std::find(b, e, std::tolower(s[offset+5]));
	auto r0 = std::find(b, e, std::tolower(s[offset+6]));
	auto r1 = std::find(b, e, std::tolower(s[offset+7]));
	if (a0 == e || a1 == e) {return;}
	if (b0 == e || b1 == e) {return;}
	if (g0 == e || g1 == e) {return;}
	if (r0 == e || r1 == e) {return;}

	m_red   = 16 * (r0-b) + (r1-b);
	m_green = 16 * (g0-b) + (g1-b);
	m_blue  = 16 * (b0-b) + (b1-b);
	m_alpha = 16 * (a0-b) + (a1-b);
}


uint8 Color::red() const   {return m_red;}
uint8 Color::green() const {return m_green;}
uint8 Color::blue() const  {return m_blue;}
uint8 Color::alpha() const {return m_alpha;}

Color& Color::setRed(uint8 r)   {m_red   = r; return *this;}
Color& Color::setGreen(uint8 g) {m_green = g; return *this;}
Color& Color::setBlue(uint8 b)  {m_blue  = b; return *this;}
Color& Color::setAlpha(uint8 a) {m_alpha = a; return *this;}

std::string Color::toStringAbgr() const
{
	std::stringstream s;
	s << "#" << std::setfill('0') << std::hex;
	s << std::setw(2) << static_cast<int>(m_alpha);
	s << std::setw(2) << static_cast<int>(m_blue);
	s << std::setw(2) << static_cast<int>(m_green);
	s << std::setw(2) << static_cast<int>(m_red);
	return s.str();
}

std::string Color::toStringRgba() const
{
	std::stringstream s;
	s << "#" << std::setfill('0') << std::hex;
	s << std::setw(2) << static_cast<int>(m_red);
	s << std::setw(2) << static_cast<int>(m_green);
	s << std::setw(2) << static_cast<int>(m_blue);
	s << std::setw(2) << static_cast<int>(m_alpha);
	return s.str();
}
}

