#ifndef POINT
#define POINT


struct Point
{
	Point()
	{
		lon = 0.0;
		lat = 0.0;
		alt = 0.0;
	};

	Point(double lonI, double latI, double altI)
	{
		lon = lonI;
		lat = latI;
		alt = altI;
	};

	double lon;
	double lat;
	double alt;
};


#endif

