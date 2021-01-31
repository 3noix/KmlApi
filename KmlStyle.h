#ifndef KML_STYLE
#define KML_STYLE


#include <optional>
#include "KmlSubStyles.h"


namespace Kml
{
class Style
{
	public:
		Style() = default;
		Style(const Style &other) = default;
		Style(Style &&other) = default;
		Style& operator=(const Style &other) = default;
		Style& operator=(Style &&other) = default;
		~Style() = default;

		std::string toString(std::size_t tabs, const std::string &id) const
		{
			std::string prefix(tabs,'\t');
			std::string str;
			str += prefix + "<Style id=\"" + id + "\">\n";

			if (rawContent)
			{
				str += prefix + "\t" + rawContent.value() + "\n";
			}
			else
			{
				if (iconStyle)   {str += iconStyle->toString(tabs+1);}
				if (labelStyle)  {str += labelStyle->toString(tabs+1);}
				if (lineStyle)   {str += lineStyle->toString(tabs+1);}
				if (polyStyle)   {str += polyStyle->toString(tabs+1);}
				if (balloonStyle) {str += balloonStyle->toString(tabs+1);}
			}

			str += prefix + "</Style>\n";
			return str;
		};
		
		std::optional<IconStyle>    iconStyle;
		std::optional<LabelStyle>   labelStyle;
		std::optional<LineStyle>    lineStyle;
		std::optional<PolyStyle>    polyStyle;
		std::optional<BalloonStyle> balloonStyle;
		
		std::optional<std::string> rawContent;
};
}


#endif

