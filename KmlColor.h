#ifndef KML_COLOR
#define KML_COLOR


#include <string>
using uint8 = std::uint8_t;


namespace Kml
{
class Color
{
	public:
		Color() = default;
		Color(uint8 red, uint8 green, uint8 blue, uint8 alpha);
		Color(const Color &other) = default;
		Color(Color &&other) = default;
		Color& operator=(const Color &other) = default;
		Color& operator=(Color &&other) = default;
		~Color() = default;

		Color(const std::string &s);

		uint8 red() const;
		uint8 green() const;
		uint8 blue() const;
		uint8 alpha() const;

		Color& setRed(uint8 r);
		Color& setGreen(uint8 g);
		Color& setBlue(uint8 b);
		Color& setAlpha(uint8 a);

		std::string toStringAbgr() const;
		std::string toStringRgba() const;
		
		
	private:
		uint8 m_red   = 255;
		uint8 m_green = 255;
		uint8 m_blue  = 255;
		uint8 m_alpha = 255;
};
}


#endif

