#include "KmlSubStyles.h"


namespace Kml
{
std::string colorModeToString(ColorMode cm)
{
	if (cm == ColorMode::Normal)      {return "normal";}
	else if (cm == ColorMode::Random) {return "random";}
	return "normal";
}

std::string hotspotUnitToString(HotspotUnit hsu)
{
	if (hsu == HotspotUnit::Fraction)         {return "fraction";}
	else if (hsu == HotspotUnit::Pixels)      {return "pixels";}
	else if (hsu == HotspotUnit::InsetPixels) {return "insetPixels";}
	return "fraction";
}

std::string refreshModeToString(RefreshMode rm)
{
	if (rm == RefreshMode::OnChange)        {return "onChange";}
	else if (rm == RefreshMode::OnInterval) {return "onInterval";}
	else if (rm == RefreshMode::OnExpire)   {return "onExpire";}
	return "onChange";
}

std::string viewRefreshModeToString(ViewRefreshMode vrm)
{
	if (vrm == ViewRefreshMode::Never)          {return "never";}
	else if (vrm == ViewRefreshMode::OnStop)    {return "onStop";}
	else if (vrm == ViewRefreshMode::OnRequest) {return "onRequest";}
	else if (vrm == ViewRefreshMode::OnRegion)  {return "onRegion";}
	return "never";
}


// @1: IconStyle
Icon::Icon(const std::string &href) {m_href = href;}

Icon& Icon::setHref(const std::string &href) {m_href = href; return *this;}
Icon& Icon::setX(int x) {m_x = x; return *this;}
Icon& Icon::setY(int y) {m_y = y; return *this;}
Icon& Icon::setW(int w) {m_w = w; return *this;}
Icon& Icon::setH(int h) {m_h = h; return *this;}
Icon& Icon::setRefreshMode(RefreshMode rm) {m_refreshMode = rm; return *this;}
Icon& Icon::setRefreshInterval(double ri) {m_refreshInterval = ri; return *this;}
Icon& Icon::setViewRefreshMode(ViewRefreshMode vrm) {m_viewRefreshMode = vrm; return *this;}
Icon& Icon::setViewRefreshTime(double vrt) {m_viewRefreshTime = vrt; return *this;}
Icon& Icon::setViewBoundScale(double vbs) {m_viewBoundScale = vbs; return *this;}
Icon& Icon::setViewFormat(const std::string &vf) {m_viewFormat = vf; return *this;}
Icon& Icon::setHttpQuery(const std::string &httpQuery) {m_httpQuery = httpQuery; return *this;}

std::string Icon::toString(std::size_t tabs) const
{
	std::string prefix(tabs,'\t');
	std::string str;
	str += prefix + "<Icon>\n";
	if (m_href)            str += prefix + "\t<href>" + *m_href + "</href>\n";
	if (m_x)               str += prefix + "\t<gx:x>" + std::to_string(*m_x) + "</gx:x>\n";
	if (m_y)               str += prefix + "\t<gx:y>" + std::to_string(*m_y) + "</gx:y>\n";
	if (m_w)               str += prefix + "\t<gx:w>" + std::to_string(*m_w) + "</gx:w>\n";
	if (m_h)               str += prefix + "\t<gx:h>" + std::to_string(*m_h) + "</gx:h>\n";
	if (m_refreshMode)     str += prefix + "\t<refreshMode>" + refreshModeToString(*m_refreshMode) + "</refreshMode>\n";
	if (m_refreshInterval) str += prefix + "\t<refreshInterval>" + std::to_string(*m_refreshInterval) + "</refreshInterval>\n";
	if (m_viewRefreshMode) str += prefix + "\t<viewRefreshMode>" + viewRefreshModeToString(*m_viewRefreshMode) + "</viewRefreshMode>\n";
	if (m_viewRefreshTime) str += prefix + "\t<viewRefreshTime>" + std::to_string(*m_viewRefreshTime) + "</viewRefreshTime>\n";
	if (m_viewBoundScale)  str += prefix + "\t<viewBoundScale>" + std::to_string(*m_viewBoundScale) + "</viewBoundScale>\n";
	if (m_viewFormat)      str += prefix + "\t<viewFormat>" + *m_viewFormat + "</viewFormat>\n";
	if (m_httpQuery)       str += prefix + "\t<httpQuery>" + *m_httpQuery + "</httpQuery>\n";
	str += prefix + "</Icon>\n";
	return str;
}


IconStyle& IconStyle::setColor(Color c) {m_color = c; return *this;}
IconStyle& IconStyle::setColorMode(ColorMode cm) {m_colorMode = cm; return *this;}
IconStyle& IconStyle::setScale(double s) {m_scale = s; return *this;}
IconStyle& IconStyle::setHeading(double h) {m_heading = h; return *this;}
IconStyle& IconStyle::setIcon(const Icon &icon) {m_icon = icon; return *this;}
IconStyle& IconStyle::setHotspot(Hotspot hs) {m_hotspot = hs; return *this;}

std::string IconStyle::toString(std::size_t tabs) const
{
	std::string prefix(tabs,'\t');
	std::string str;
	str += prefix + "<IconStyle>\n";
	if (m_color)     str += prefix + "\t<color>" + m_color->toStringAbgr() + "</color>\n";
	if (m_colorMode) str += prefix + "\t<colorMode>" + colorModeToString(*m_colorMode) + "</colorMode>\n";
	if (m_scale)     str += prefix + "\t<scale>" + std::to_string(*m_scale) + "</scale>\n";
	if (m_heading)   str += prefix + "\t<heading>" + std::to_string(*m_heading) + "</heading>\n";
	if (m_icon)      str += prefix + m_icon->toString(tabs+1);
	if (m_hotspot)   str += prefix + "\t<hotSpot x=\"" + std::to_string(m_hotspot->x) + "\" y=\"" + std::to_string(m_hotspot->y) + "\" xunits=\"" + hotspotUnitToString(m_hotspot->xUnits) + "\" yunits=\""+ hotspotUnitToString(m_hotspot->yUnits) + "\"/>\n";
	str += prefix + "</IconStyle>\n";
	return str;
}


// @1: LabelStyle
LabelStyle& LabelStyle::setColor(Color c) {m_color = c; return *this;}
LabelStyle& LabelStyle::setColorMode(ColorMode cm) {m_colorMode = cm; return *this;}
LabelStyle& LabelStyle::setScale(double s) {m_scale = s; return *this;}

std::string LabelStyle::toString(std::size_t tabs) const
{
	std::string prefix(tabs,'\t');
	std::string str;
	str += prefix + "<LabelStyle>\n";
	if (m_color)     str += prefix + "\t<color>" + m_color->toStringAbgr() + "</color>\n";
	if (m_colorMode) str += prefix + "\t<colorMode>" + colorModeToString(*m_colorMode) + "</colorMode>\n";
	if (m_scale)     str += prefix + "\t<scale>" + std::to_string(*m_scale) + "</scale>\n";
	str += prefix + "</LabelStyle>\n";
	return str;
}


// @1: LineStyle
LineStyle& LineStyle::setColor(Color c) {m_color = c; return *this;}
LineStyle& LineStyle::setColorMode(ColorMode cm) {m_colorMode = cm; return *this;}
LineStyle& LineStyle::setWidth(double w) {m_width = w; return *this;}
LineStyle& LineStyle::setOuterColor(Color oc) {m_outerColor = oc; return *this;}
LineStyle& LineStyle::setOuterWidth(double ow) {m_outerWidth = ow; return *this;}
LineStyle& LineStyle::setPhysicalWidth(double pw) {m_physicalWidth = pw; return *this;}
LineStyle& LineStyle::setLabelVisible(bool visible) {m_labelVisible = visible; return *this;}

std::string LineStyle::toString(std::size_t tabs) const
{
	std::string prefix(tabs,'\t');
	std::string str;
	str += prefix + "<LineStyle>\n";
	if (m_color)         str += prefix + "\t<color>" + m_color->toStringAbgr() + "</color>\n";
	if (m_colorMode)     str += prefix + "\t<colorMode>" + colorModeToString(*m_colorMode) + "</colorMode>\n";
	if (m_width)         str += prefix + "\t<width>" + std::to_string(*m_width) + "</width>\n";
	if (m_outerColor)    str += prefix + "\t<gx:outerColor>" + m_outerColor->toStringAbgr() + "</gx:outerColor>\n";
	if (m_outerWidth)    str += prefix + "\t<gx:outerWidth>" + std::to_string(*m_outerWidth) + "</gx:outerWidth>\n";
	if (m_physicalWidth) str += prefix + "\t<gx:physicalWidth>" + std::to_string(*m_physicalWidth) + "</gx:physicalWidth>\n";
	if (m_labelVisible)  str += prefix + "\t<gx:labelVisibility>" + (*m_labelVisible ? "1" : "0") + "</gx:labelVisibility>\n";
	str += prefix + "</LineStyle>\n";
	return str;
}


// @1: PolyStyle
PolyStyle& PolyStyle::setColor(Color c) {m_color = c; return *this;}
PolyStyle& PolyStyle::setColorMode(ColorMode cm) {m_colorMode = cm; return *this;}
PolyStyle& PolyStyle::setFill(bool fill) {m_fill = fill; return *this;}
PolyStyle& PolyStyle::setOutline(bool outline) {m_outline = outline; return *this;}

std::string PolyStyle::toString(std::size_t tabs) const
{
	std::string prefix(tabs,'\t');
	std::string str;
	str += prefix + "<LineStyle>\n";
	if (m_color)     str += prefix + "\t<color>" + m_color->toStringAbgr() + "</color>\n";
	if (m_colorMode) str += prefix + "\t<colorMode>" + colorModeToString(*m_colorMode) + "</colorMode>\n";
	if (m_fill)      str += prefix + "\t<fill>" + (*m_fill ? "1" : "0") + "</fill>\n";
	if (m_outline)   str += prefix + "\t<outline>" + (*m_outline ? "1" : "0") + "</outline>\n";
	str += prefix + "</LineStyle>\n";
	return str;
}


// @1: BalloonStyle
BalloonStyle& BalloonStyle::setBackgroundColor(Color c) {m_backgroundColor = c; return *this;}
BalloonStyle& BalloonStyle::setTextColor(Color c) {m_textColor = c; return *this;}
BalloonStyle& BalloonStyle::setText(const std::string &text) {m_text = text; return *this;}

std::string BalloonStyle::toString(std::size_t tabs) const
{
	std::string prefix(tabs,'\t');
	std::string str;
	str += prefix + "<LineStyle>\n";
	if (m_backgroundColor) str += prefix + "\t<bgColor>" + m_backgroundColor->toStringAbgr() + "</bgColor>\n";
	if (m_textColor)       str += prefix + "\t<textColor>" + m_textColor->toStringAbgr() + "</textColor>\n";
	if (m_text)            str += prefix + "\t<text>" + *m_text + "</text>\n";
	str += prefix + "</LineStyle>\n";
	return str;
}
}

