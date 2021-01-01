#ifndef KML_SIMPLE_POINT
#define KML_SIMPLE_POINT


namespace Kml
{
struct SimplePoint
{
	SimplePoint()
	{
		lon = 0.0;
		lat = 0.0;
		alt = 0.0;
	};

	SimplePoint(double lonI, double latI, double altI)
	{
		lon = lonI;
		lat = latI;
		alt = altI;
	};

	double lon;
	double lat;
	double alt;
};
}


#endif

