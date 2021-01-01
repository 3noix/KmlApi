#ifndef KML_SPECIAL_POINT
#define KML_SPECIAL_POINT


#include "KmlAbstractItem.h"
#include "KmlSimplePoint.h"
#include "KmlAltitudeMode.h"


namespace Kml
{
class SpecialPoint : public AbstractItem
{
	public:
		SpecialPoint(const std::string &name, const SimplePoint &p, const std::string &styleUrl = {}, AltitudeMode altMode = AltitudeMode::Absolute) : AbstractItem{name}
		{
			m_point = p;
			this->setStyleUrl(styleUrl);
			m_altMode = altMode;
		};

		SpecialPoint(const SpecialPoint &other) = default;
		SpecialPoint(SpecialPoint &&other) = default;
		SpecialPoint& operator=(const SpecialPoint &other) = default;
		SpecialPoint& operator=(SpecialPoint &&other) = default;
		virtual ~SpecialPoint() = default;
		

		virtual std::string toString(std::size_t tabs = 0) const override final
		{
			std::string prefix(tabs,'\t');
			std::string str;
			str += prefix + "<Placemark>\n";
			str += prefix + "\t<name>" + this->name() + "</name>\n";
			str += prefix + "\t<description>" + this->description() + "</description>\n";
			str += prefix + "\t<styleUrl>" + this->styleUrl() + "</styleUrl>\n";
			str += prefix + "\t<visible>" + (this->isVisible() ? "1" : "0") + "</visible>\n";
			str += prefix + "\t<Point>\n";
			str += prefix + "\t\t" + altitudeModeToStr(m_altMode) + "\n";
			str += prefix + "\t\t<coordinates>" + std::to_string(m_point.lon) + "," + std::to_string(m_point.lat) + "," + std::to_string(m_point.alt) + "</coordinates>\n";
			str += prefix + "\t</Point>\n";
			str += prefix + "</Placemark>\n";
			return str;
		};

		void setPoint(const SimplePoint &p) {m_point = p;};
		const SimplePoint& point() const {return m_point;};

		void setAltitudeMode(AltitudeMode am) {m_altMode = am;};
		AltitudeMode altitudeMode() const {return m_altMode;};


	private:
		SimplePoint m_point;
		AltitudeMode m_altMode = AltitudeMode::Absolute;
};
}


#endif

