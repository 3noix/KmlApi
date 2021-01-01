#ifndef KML_ALTITUDE_MODE
#define KML_ALTITUDE_MODE


#include <string>


namespace Kml
{
enum class AltitudeMode
{
	Absolute,
	ClampToGround,
	ClampToSeaFloor,
	RelativeToGround,
	RelativeToSeaFloor
};

std::string altitudeModeToStr(AltitudeMode am)
{
	if (am == AltitudeMode::Absolute)           {return "<altitudeMode>absolute</altitudeMode>";}
	if (am == AltitudeMode::ClampToGround)      {return "<altitudeMode>clampToGround</altitudeMode>";}
	if (am == AltitudeMode::ClampToSeaFloor)    {return "<gx:altitudeMode>clampToSeaFloor</gx:altitudeMode>";}
	if (am == AltitudeMode::RelativeToGround)   {return "<altitudeMode>relativeToGround</altitudeMode>";}
	if (am == AltitudeMode::RelativeToSeaFloor) {return "<gx:altitudeMode>relativeToSeaFloor</gx:altitudeMode>";}
	return "<altitudeMode>absolute</altitudeMode>";
};
}


#endif

