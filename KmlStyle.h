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

		std::string toString(std::size_t tabs, const std::string &id) const;
		
		std::optional<IconStyle>    iconStyle;
		std::optional<LabelStyle>   labelStyle;
		std::optional<LineStyle>    lineStyle;
		std::optional<PolyStyle>    polyStyle;
		std::optional<BalloonStyle> balloonStyle;
		
		std::optional<std::string> rawContent;
};
}


#endif

