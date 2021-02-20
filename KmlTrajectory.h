#ifndef KML_TRAJECTORY
#define KML_TRAJECTORY


#include "KmlAbstractItem.h"
#include "KmlSimplePoint.h"
#include "KmlAltitudeMode.h"

#include <vector>
#include <functional>


namespace Kml
{
using Function = std::function<double(double)>;

class Trajectory : public AbstractItem
{
	public:
		Trajectory(const std::string &name, const std::string &styleUrl = {}, AltitudeMode altMode = AltitudeMode::Absolute);

		Trajectory(const Trajectory &other) = default;
		Trajectory(Trajectory &&other) = default;
		Trajectory& operator=(const Trajectory &other) = default;
		Trajectory& operator=(Trajectory &&other) = default;
		virtual ~Trajectory() = default;


		virtual std::string toString(std::size_t tabs = 0) const override final;

		bool setPoints(double t1, double t2, double dt, Function lon, Function lat, Function alt);
		bool setPoints(double t1, double t2, double dt, Function lon, Function lat);
		Trajectory& setPoints(const std::vector<SimplePoint> &points);

		Trajectory& addPoint(const SimplePoint &p);
		Trajectory& addPoint(double lon, double lat, double alt);
		Trajectory& addPoint(double lon, double lat);

		Trajectory& setExtruded(bool b);
		bool isExtruded() const;

		Trajectory& setAltitudeOffset(double o);
		double altitudeOffset() const;

		Trajectory& setAltitudeMode(AltitudeMode am);
		AltitudeMode altitudeMode() const;
		

	private:
		std::vector<SimplePoint> m_points;
		bool m_extruded = true;
		double m_altitudeOffset = 0.0;
		AltitudeMode m_altMode = AltitudeMode::Absolute;
};
}


#endif

