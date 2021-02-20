#include "KmlSpecialPoint.h"


namespace Kml
{
SpecialPoint::SpecialPoint(const std::string &name, const SimplePoint &p, const std::string &styleUrl, AltitudeMode altMode) :
	AbstractItem{name}
{
	m_point = p;
	this->setStyleUrl(styleUrl);
	m_altMode = altMode;
}

SpecialPoint::SpecialPoint(const std::string &name, double lon, double lat, double alt, const std::string &styleUrl, AltitudeMode altMode) :
	AbstractItem{name}
{
	m_point = SimplePoint{lon,lat,alt};
	this->setStyleUrl(styleUrl);
	m_altMode = altMode;
}

SpecialPoint::SpecialPoint(const std::string &name, double lon, double lat, const std::string &styleUrl, AltitudeMode altMode) :
	AbstractItem{name}
{
	m_point = SimplePoint{lon,lat,0.0};
	this->setStyleUrl(styleUrl);
	m_altMode = altMode;
}


std::string SpecialPoint::toString(std::size_t tabs) const
{
	std::string prefix(tabs,'\t');
	std::string str;
	str += prefix + "<Placemark>\n";
	str += prefix + "\t<name>" + this->name() + "</name>\n";
	str += prefix + "\t<description>" + this->description() + "</description>\n";
	str += prefix + "\t<styleUrl>" + this->styleUrl() + "</styleUrl>\n";
	str += prefix + "\t<visible>" + (this->isVisible() ? "1" : "0") + "</visible>\n";
	str += prefix + "\t<Point>\n";
	str += prefix + "\t\t<extrude>" + (m_extruded ? "1" : "0") + "</extrude>\n";
	str += prefix + "\t\t" + altitudeModeToStr(m_altMode) + "\n";
	str += prefix + "\t\t<coordinates>" + std::to_string(m_point.lon) + "," + std::to_string(m_point.lat) + "," + std::to_string(m_point.alt) + "</coordinates>\n";
	str += prefix + "\t</Point>\n";
	str += prefix + "</Placemark>\n";
	return str;
}

SpecialPoint& SpecialPoint::setPoint(const SimplePoint &p)
{
	m_point = p;
	return *this;
}

SpecialPoint& SpecialPoint::setPoint(double lon, double lat, double alt)
{
	m_point = SimplePoint{lon,lat,alt};
	return *this;
}

SpecialPoint& SpecialPoint::setPoint(double lon, double lat)
{
	m_point = SimplePoint{lon,lat};
	m_altMode = AltitudeMode::ClampToGround;
	return *this;
}

const SimplePoint& SpecialPoint::point() const
{
	return m_point;
}

SpecialPoint& SpecialPoint::setExtruded(bool b)
{
	m_extruded = b;
	return *this;
}

bool SpecialPoint::isExtruded() const
{
	return m_extruded;
}

SpecialPoint& SpecialPoint::setAltitudeMode(AltitudeMode am)
{
	m_altMode = am;
	return *this;
}

AltitudeMode SpecialPoint::altitudeMode() const
{
	return m_altMode;
}
}

