#ifndef KML_POINT
#define KML_POINT


#include "AbstractKmlItem.h"
#include "Point.h"


class KmlPoint : public AbstractKmlItem
{
	public:
		KmlPoint(const QString &name, const Point &p, const QString &styleUrl = {}, AltitudeMode altMode = AltitudeMode::Absolute) : AbstractKmlItem{name}
		{
			m_point = p;
			this->setStyleUrl(styleUrl);
			m_altMode = altMode;
		};

		KmlPoint(const KmlPoint &other) = default;
		KmlPoint(KmlPoint &&other) = default;
		KmlPoint& operator=(const KmlPoint &other) = default;
		KmlPoint& operator=(KmlPoint &&other) = default;
		virtual ~KmlPoint() = default;
		

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
			str += prefix + "\t\t" + AbstractKmlItem::altitudeModeToStr(m_altMode) + "\n";
			str += prefix + "\t\t<coordinates>" + QString::number(m_point.lon) + "," + QString::number(m_point.lat) + "," + QString::number(m_point.alt) + "</coordinates>\n";
			str += prefix + "\t</Point>\n";
			str += prefix + "</Placemark>\n";
			return str;
		};

		void setPoint(const Point &p) {m_point = p;};
		const Point& point() const {return m_point;};

		void setAltitudeMode(AltitudeMode am) {m_altMode = am;};
		AltitudeMode altitudeMode() const {return m_altMode;};


	private:
		Point m_point;
		AltitudeMode m_altMode = AltitudeMode::Absolute;
};


#endif

