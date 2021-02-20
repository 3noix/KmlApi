#include "KmlStyle.h"


namespace Kml
{
std::string Style::toString(std::size_t tabs, const std::string &id) const
{
	std::string prefix(tabs,'\t');
	std::string str;
	str += prefix + "<Style id=\"" + id + "\">\n";

	if (rawContent)
	{
		str += prefix + "\t" + rawContent.value() + "\n";
	}
	else
	{
		if (iconStyle)   {str += iconStyle->toString(tabs+1);}
		if (labelStyle)  {str += labelStyle->toString(tabs+1);}
		if (lineStyle)   {str += lineStyle->toString(tabs+1);}
		if (polyStyle)   {str += polyStyle->toString(tabs+1);}
		if (balloonStyle) {str += balloonStyle->toString(tabs+1);}
	}

	str += prefix + "</Style>\n";
	return str;
}
}

