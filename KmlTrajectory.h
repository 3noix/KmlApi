#ifndef KML_TRAJECTORY
#define KML_TRAJECTORY


#include "AbstractKmlItem.h"
#include <vector>
#include <functional>
#include <cmath>
#include "Point.h"

using Function = std::function<double(double)>;


class KmlTrajectory : public AbstractKmlItem
{
	public:
		KmlTrajectory(const QString &name, const QString &styleUrl = {}, AltitudeMode altMode = AltitudeMode::Absolute) : AbstractKmlItem{name}
		{
			this->setStyleUrl(styleUrl);
			m_altMode = altMode;
		};

		KmlTrajectory(const KmlTrajectory &other) = default;
		KmlTrajectory(KmlTrajectory &&other) = default;
		KmlTrajectory& operator=(const KmlTrajectory &other) = default;
		KmlTrajectory& operator=(KmlTrajectory &&other) = default;
		virtual ~KmlTrajectory() = default;


		virtual QString toString(int tabs = 0) const override final
		{
			QString prefix{tabs,'\t'};
			QString str;
			str += prefix + "<Placemark>\n";
			str += prefix + "\t<name>" + this->name() + "</name>\n";
			str += prefix + "\t<description>" + this->description() + "</description>\n";
			str += prefix + "\t<styleUrl>" + this->styleUrl() + "</styleUrl>\n";
			str += prefix + "\t<visible>" + (this->isVisible() ? "1" : "0") + "</visible>\n";
			str += prefix + "\t<LineString>\n";
			str += prefix + "\t\t" + AbstractKmlItem::altitudeModeToStr(m_altMode) + "\n";
			str += prefix + "\t\t<tessellate>1</tessellate>\n";
			str += prefix + "\t\t<coordinates>\n";
			for (const Point &p : m_points) {str += prefix + "\t\t\t" + QString::number(p.lon) + "," + QString::number(p.lat) + "," + QString::number(p.alt) + "\n";}
			str += prefix + "\t\t</coordinates>\n";
			str += prefix + "\t</LineString>\n";
			str += prefix + "</Placemark>\n";
			return str;
		};

		bool setPoints(double t1, double t2, double dt, Function lon, Function lat, Function alt)
		{
			if (t1 > t2 || dt <= 0) {return false;}
			int n = 1 + std::floor((t2-t1)/dt);
			m_points.clear();
			m_points.reserve(n+10);

			for (double t=t1; t<=t2; t+=dt) {m_points.emplace_back(lon(t),lat(t),alt(t));}
			return true;
		};
		void setPoints(const std::vector<Point> &points) {m_points = points;};
		void addPoint(const Point &p) {m_points.push_back(p);};

		void setAltitudeMode(AltitudeMode am) {m_altMode = am;};
		AltitudeMode altitudeMode() const {return m_altMode;};
		

	private:
		std::vector<Point> m_points;
		AltitudeMode m_altMode = AltitudeMode::Absolute;
};


#endif

