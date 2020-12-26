#ifndef TRAJECTORY
#define TRAJECTORY


#include <vector>
#include <functional>
#include <cmath>
#include <QString>
#include "Point.h"
#include "AltitudeMode.h"

using Function = std::function<double(double)>;


class Trajectory
{
	public:
		Trajectory(const QString &name, const QString &styleUrl, AltitudeMode altMode = AltitudeMode::Absolute)
		{
			m_name = name;
			m_styleUrl = styleUrl;
			m_altMode = altMode;
		};

		Trajectory(const Trajectory &other) = default;
		Trajectory(Trajectory &&other) = default;
		Trajectory& operator=(const Trajectory &other) = default;
		Trajectory& operator=(Trajectory &&other) = default;
		~Trajectory() = default;


		void setName(const QString &name) {m_name = name;};
		QString name() const {return m_name;};

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

		void setDescription(const QString &description) {m_description = description;};
		QString description() const {return m_description;};

		void setStyleUrl(const QString &styleUrl) {m_styleUrl = styleUrl;};
		QString styleUrl() const {return m_styleUrl;};

		void setAltitudeMode(AltitudeMode am) {m_altMode = am;};
		AltitudeMode altitudeMode() const {return m_altMode;};
		

	private:
		QString m_name;
		std::vector<Point> m_points;
		QString m_description = "<![CDATA[]]>";
		QString m_styleUrl;
		AltitudeMode m_altMode = AltitudeMode::Absolute;
		friend class KmlFile;
};


#endif

