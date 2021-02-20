#include "KmlTrajectory.h"
#include <cmath>


namespace Kml
{
Trajectory::Trajectory(const std::string &name, const std::string &styleUrl, AltitudeMode altMode) :
	AbstractItem{name}
{
	this->setStyleUrl(styleUrl);
	m_altMode = altMode;
}


std::string Trajectory::toString(std::size_t tabs) const
{
	std::string prefix(tabs,'\t');
	std::string str;
	str += prefix + "<Placemark>\n";
	str += prefix + "\t<name>" + this->name() + "</name>\n";
	str += prefix + "\t<description>" + this->description() + "</description>\n";
	str += prefix + "\t<styleUrl>" + this->styleUrl() + "</styleUrl>\n";
	str += prefix + "\t<visible>" + (this->isVisible() ? "1" : "0") + "</visible>\n";
	str += prefix + "\t<LineString>\n";
	str += prefix + "\t\t" + altitudeModeToStr(m_altMode) + "\n";
	str += prefix + "\t\t<extrude>" + (m_extruded ? "1" : "0") + "</extrude>\n";
	if (m_altitudeOffset != 0.0) {str += prefix + "\t\t<gx:altitudeOffset>" + std::to_string(m_altitudeOffset) + "</gx:altitudeOffset>\n";}
	str += prefix + "\t\t<tessellate>1</tessellate>\n";
	str += prefix + "\t\t<coordinates>\n";
	for (const SimplePoint &p : m_points) {str += prefix + "\t\t\t" + std::to_string(p.lon) + "," + std::to_string(p.lat) + "," + std::to_string(p.alt) + "\n";}
	str += prefix + "\t\t</coordinates>\n";
	str += prefix + "\t</LineString>\n";
	str += prefix + "</Placemark>\n";
	return str;
}

bool Trajectory::setPoints(double t1, double t2, double dt, Function lon, Function lat, Function alt)
{
	if (t1 > t2 || dt <= 0) {return false;}
	int n = 1 + std::floor((t2-t1)/dt);
	m_points.clear();
	m_points.reserve(n+10);

	for (double t=t1; t<=t2; t+=dt) {m_points.emplace_back(lon(t),lat(t),alt(t));}
	return true;
}

bool Trajectory::setPoints(double t1, double t2, double dt, Function lon, Function lat)
{
	if (t1 > t2 || dt <= 0) {return false;}
	int n = 1 + std::floor((t2-t1)/dt);
	m_points.clear();
	m_points.reserve(n+10);

	for (double t=t1; t<=t2; t+=dt) {m_points.emplace_back(lon(t),lat(t));}
	m_altMode = AltitudeMode::ClampToGround;
	return true;
}

Trajectory& Trajectory::setPoints(const std::vector<SimplePoint> &points)
{
	m_points = points;
	return *this;
}

Trajectory& Trajectory::addPoint(const SimplePoint &p)
{
	m_points.push_back(p);
	return *this;
}

Trajectory& Trajectory::addPoint(double lon, double lat, double alt)
{
	m_points.emplace_back(lon,lat,alt);
	return *this;
}

Trajectory& Trajectory::addPoint(double lon, double lat)
{
	m_points.emplace_back(lon,lat);
	return *this;
}

Trajectory& Trajectory::setExtruded(bool b)
{
	m_extruded = b;
	return *this;
}

bool Trajectory::isExtruded() const
{
	return m_extruded;
}

Trajectory& Trajectory::setAltitudeOffset(double o)
{
	m_altitudeOffset = o;
	return *this;
}

double Trajectory::altitudeOffset() const
{
	return m_altitudeOffset;
}

Trajectory& Trajectory::setAltitudeMode(AltitudeMode am)
{
	m_altMode = am;
	return *this;
}

AltitudeMode Trajectory::altitudeMode() const
{
	return m_altMode;
}
}

