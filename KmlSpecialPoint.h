#ifndef KML_SPECIAL_POINT
#define KML_SPECIAL_POINT


#include "KmlAbstractItem.h"
#include "KmlSimplePoint.h"


namespace Kml
{
class SpecialPoint : public AbstractItem
{
	public:
		SpecialPoint(const QString &name, const SimplePoint &p, const QString &styleUrl = {}, AltitudeMode altMode = AltitudeMode::Absolute) : AbstractItem{name}
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
		

		virtual QString toString(int tabs = 0) const override final
		{
			QString prefix{tabs,'\t'};
			QString str;
			str += prefix + "<Placemark>\n";
			str += prefix + "\t<name>" + this->name() + "</name>\n";
			str += prefix + "\t<description>" + this->description() + "</description>\n";
			str += prefix + "\t<styleUrl>" + this->styleUrl() + "</styleUrl>\n";
			str += prefix + "\t<visible>" + (this->isVisible() ? "1" : "0") + "</visible>\n";
			str += prefix + "\t<Point>\n";
			str += prefix + "\t\t" + altitudeModeToStr(m_altMode) + "\n";
			str += prefix + "\t\t<coordinates>" + QString::number(m_point.lon) + "," + QString::number(m_point.lat) + "," + QString::number(m_point.alt) + "</coordinates>\n";
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

