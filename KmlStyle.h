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

		RawStyle& rawStyle();
		IconStyle& iconStyle();
		LabelStyle& labelStyle();
		LineStyle& lineStyle();
		PolyStyle& polyStyle();
		BalloonStyle& balloonStyle();


	private:
		std::optional<RawStyle> m_rawStyle;

		std::optional<IconStyle>    m_iconStyle;
		std::optional<LabelStyle>   m_labelStyle;
		std::optional<LineStyle>    m_lineStyle;
		std::optional<PolyStyle>    m_polyStyle;
		std::optional<BalloonStyle> m_balloonStyle;
};
}


#endif

