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
		SpecialPoint(const std::string &name, const SimplePoint &p, const std::string &styleUrl = {}, AltitudeMode altMode = AltitudeMode::Absolute);
		SpecialPoint(const std::string &name, double lon, double lat, double alt, const std::string &styleUrl = {}, AltitudeMode altMode = AltitudeMode::Absolute);
		SpecialPoint(const std::string &name, double lon, double lat, const std::string &styleUrl = {}, AltitudeMode altMode = AltitudeMode::Absolute);

		SpecialPoint(const SpecialPoint &other) = default;
		SpecialPoint(SpecialPoint &&other) = default;
		SpecialPoint& operator=(const SpecialPoint &other) = default;
		SpecialPoint& operator=(SpecialPoint &&other) = default;
		virtual ~SpecialPoint() = default;
		

		virtual std::string toString(std::size_t tabs = 0) const override final;

		SpecialPoint& setPoint(const SimplePoint &p);
		SpecialPoint& setPoint(double lon, double lat, double alt);
		SpecialPoint& setPoint(double lon, double lat);
		const SimplePoint& point() const;

		SpecialPoint& setExtruded(bool b);
		bool isExtruded() const;

		SpecialPoint& setAltitudeMode(AltitudeMode am);
		AltitudeMode altitudeMode() const;


	private:
		SimplePoint m_point;
		bool m_extruded = true;
		AltitudeMode m_altMode = AltitudeMode::Absolute;
};
}


#endif

