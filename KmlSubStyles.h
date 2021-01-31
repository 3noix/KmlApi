#ifndef KML_SUBSTYLES
#define KML_SUBSTYLES


#include "KmlColor.h"
#include <optional>


namespace Kml
{
enum ColorMode {Normal, Random};
enum HotspotUnit {Fraction, Pixels, InsetPixels};
enum RefreshMode {OnChange, OnInterval, OnExpire};
enum ViewRefreshMode {Never, OnStop, OnRequest, OnRegion};


static std::string colorModeToString(ColorMode cm)
{
	if (cm == ColorMode::Normal)      {return "normal";}
	else if (cm == ColorMode::Random) {return "random";}
	return "normal";
};

static std::string hotspotUnitToString(HotspotUnit hsu)
{
	if (hsu == HotspotUnit::Fraction)         {return "fraction";}
	else if (hsu == HotspotUnit::Pixels)      {return "pixels";}
	else if (hsu == HotspotUnit::InsetPixels) {return "insetPixels";}
	return "fraction";
};

static std::string refreshModeToString(RefreshMode rm)
{
	if (rm == RefreshMode::OnChange)        {return "onChange";}
	else if (rm == RefreshMode::OnInterval) {return "onInterval";}
	else if (rm == RefreshMode::OnExpire)   {return "onExpire";}
	return "onChange";
};

static std::string viewRefreshModeToString(ViewRefreshMode vrm)
{
	if (vrm == ViewRefreshMode::Never)          {return "never";}
	else if (vrm == ViewRefreshMode::OnStop)    {return "onStop";}
	else if (vrm == ViewRefreshMode::OnRequest) {return "onRequest";}
	else if (vrm == ViewRefreshMode::OnRegion)  {return "onRegion";}
	return "never";
};


class Icon
{
	public:
		Icon() = default;
		Icon(const std::string &href) {m_href = href;};
		Icon(const Icon &other) = default;
		Icon(Icon &&other) = default;
		Icon& operator=(const Icon &other) = default;
		Icon& operator=(Icon &&other) = default;
		~Icon() = default;

		Icon& setHref(const std::string &href) {m_href = href; return *this;}
		Icon& setX(int x) {m_x = x; return *this;};
		Icon& setY(int y) {m_y = y; return *this;};
		Icon& setW(int w) {m_w = w; return *this;};
		Icon& setH(int h) {m_h = h; return *this;};
		Icon& setRefreshMode(RefreshMode rm) {m_refreshMode = rm; return *this;};
		Icon& setRefreshInterval(double ri) {m_refreshInterval = ri; return *this;};
		Icon& setViewRefreshMode(ViewRefreshMode vrm) {m_viewRefreshMode = vrm; return *this;};
		Icon& setViewRefreshTime(double vrt) {m_viewRefreshTime = vrt; return *this;};
		Icon& setViewBoundScale(double vbs) {m_viewBoundScale = vbs; return *this;};
		Icon& setViewFormat(const std::string &vf) {m_viewFormat = vf; return *this;};
		Icon& setHttpQuery(const std::string &httpQuery) {m_httpQuery = httpQuery; return *this;};

		std::string toString(std::size_t tabs = 0) const
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
		};
		
		
	private:
		std::optional<std::string> m_href;					// default = ""
		std::optional<int> m_x = 0;							// default = 0
		std::optional<int> m_y = 0;							// default = 0
		std::optional<int> m_w = -1;						// default = 1
		std::optional<int> m_h = -1;						// default = 1
		std::optional<RefreshMode> m_refreshMode;			// default = OnChange
		std::optional<double> m_refreshInterval;			// default = 4
		std::optional<ViewRefreshMode> m_viewRefreshMode;	// default = Never
		std::optional<double> m_viewRefreshTime;			// default = 4
		std::optional<double> m_viewBoundScale;				// default = 1
		std::optional<std::string> m_viewFormat;			// default = ""
		std::optional<std::string> m_httpQuery;				// default = ""
};


struct Hotspot
{
	double x = 0.5;
	double y = 0.5;
	HotspotUnit xUnits = HotspotUnit::Fraction;
	HotspotUnit yUnits = HotspotUnit::Fraction;
};

class IconStyle
{
	public:
		IconStyle() = default;
		IconStyle(const IconStyle &other) = default;
		IconStyle(IconStyle &&other) = default;
		IconStyle& operator=(const IconStyle &other) = default;
		IconStyle& operator=(IconStyle &&other) = default;
		~IconStyle() = default;

		IconStyle& setColor(Color c) {m_color = c; return *this;};
		IconStyle& setColorMode(ColorMode cm) {m_colorMode = cm; return *this;};
		IconStyle& setScale(double s) {m_scale = s; return *this;};
		IconStyle& setHeading(double h) {m_heading = h; return *this;};
		IconStyle& setIcon(const Icon &icon) {m_icon = icon; return *this;};
		IconStyle& setHotspot(Hotspot hs) {m_hotspot = hs; return *this;};

		std::string toString(std::size_t tabs = 0) const
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
		};
		
		
	private:
		std::optional<Color> m_color;			// default = #ffffffff
		std::optional<ColorMode> m_colorMode;	// default = Normal
		std::optional<double> m_scale;			// default = 1
		std::optional<double> m_heading;		// default = 0
		std::optional<Icon> m_icon;
		std::optional<Hotspot> m_hotspot;
};


class LabelStyle
{
	public:
		LabelStyle() = default;
		LabelStyle(const LabelStyle &other) = default;
		LabelStyle(LabelStyle &&other) = default;
		LabelStyle& operator=(const LabelStyle &other) = default;
		LabelStyle& operator=(LabelStyle &&other) = default;
		~LabelStyle() = default;

		LabelStyle& setColor(Color c) {m_color = c; return *this;};
		LabelStyle& setColorMode(ColorMode cm) {m_colorMode = cm; return *this;};
		LabelStyle& setScale(double s) {m_scale = s; return *this;};

		std::string toString(std::size_t tabs = 0) const
		{
			std::string prefix(tabs,'\t');
			std::string str;
			str += prefix + "<LabelStyle>\n";
			if (m_color)     str += prefix + "\t<color>" + m_color->toStringAbgr() + "</color>\n";
			if (m_colorMode) str += prefix + "\t<colorMode>" + colorModeToString(*m_colorMode) + "</colorMode>\n";
			if (m_scale)     str += prefix + "\t<scale>" + std::to_string(*m_scale) + "</scale>\n";
			str += prefix + "</LabelStyle>\n";
			return str;
		};
		
		
	private:
		std::optional<Color> m_color;			// default = #ffffffff
		std::optional<ColorMode> m_colorMode;	// default = Normal
		std::optional<double> m_scale;			// default = 1
};


class LineStyle
{
	public:
		LineStyle() = default;
		LineStyle(const LineStyle &other) = default;
		LineStyle(LineStyle &&other) = default;
		LineStyle& operator=(const LineStyle &other) = default;
		LineStyle& operator=(LineStyle &&other) = default;
		~LineStyle() = default;

		LineStyle& setColor(Color c) {m_color = c; return *this;};
		LineStyle& setColorMode(ColorMode cm) {m_colorMode = cm; return *this;};
		LineStyle& setWidth(double w) {m_width = w; return *this;};
		LineStyle& setOuterColor(Color oc) {m_outerColor = oc; return *this;};
		LineStyle& setOuterWidth(double ow) {m_outerWidth = ow; return *this;};
		LineStyle& setPhysicalWidth(double pw) {m_physicalWidth = pw; return *this;};
		LineStyle& setLabelVisible(bool visible) {m_labelVisible = visible; return *this;};

		std::string toString(std::size_t tabs = 0) const
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
		};
		
		
	private:
		std::optional<Color> m_color;			// default = #ffffffff
		std::optional<ColorMode> m_colorMode;	// default = Normal
		std::optional<double> m_width;			// default = 1
		std::optional<Color> m_outerColor;		// default = #ffffffff
		std::optional<double> m_outerWidth;		// default = 0
		std::optional<double> m_physicalWidth;	// default = 0
		std::optional<bool> m_labelVisible;		// default = false
};


class PolyStyle
{
	public:
		PolyStyle() = default;
		PolyStyle(const PolyStyle &other) = default;
		PolyStyle(PolyStyle &&other) = default;
		PolyStyle& operator=(const PolyStyle &other) = default;
		PolyStyle& operator=(PolyStyle &&other) = default;
		~PolyStyle() = default;

		PolyStyle& setColor(Color c) {m_color = c; return *this;};
		PolyStyle& setColorMode(ColorMode cm) {m_colorMode = cm; return *this;};
		PolyStyle& setFill(bool fill) {m_fill = fill; return *this;};
		PolyStyle& setOutline(bool outline) {m_outline = outline; return *this;};

		std::string toString(std::size_t tabs = 0) const
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
		};
		
		
	private:
		std::optional<Color> m_color;			// default = #ffffffff
		std::optional<ColorMode> m_colorMode;	// default = Normal
		std::optional<bool> m_fill;				// default = true
		std::optional<bool> m_outline;			// default = true
};


class BalloonStyle
{
	public:
		BalloonStyle() = default;
		BalloonStyle(const BalloonStyle &other) = default;
		BalloonStyle(BalloonStyle &&other) = default;
		BalloonStyle& operator=(const BalloonStyle &other) = default;
		BalloonStyle& operator=(BalloonStyle &&other) = default;
		~BalloonStyle() = default;

		BalloonStyle& setBackgroundColor(Color c) {m_backgroundColor = c; return *this;};
		BalloonStyle& setTextColor(Color c) {m_textColor = c; return *this;};
		BalloonStyle& setText(const std::string &text) {m_text = text; return *this;};

		std::string toString(std::size_t tabs = 0) const
		{
			std::string prefix(tabs,'\t');
			std::string str;
			str += prefix + "<LineStyle>\n";
			if (m_backgroundColor) str += prefix + "\t<bgColor>" + m_backgroundColor->toStringAbgr() + "</bgColor>\n";
			if (m_textColor)       str += prefix + "\t<textColor>" + m_textColor->toStringAbgr() + "</textColor>\n";
			if (m_text)            str += prefix + "\t<text>" + *m_text + "</text>\n";
			str += prefix + "</LineStyle>\n";
			return str;
		};
		
		
	private:
		std::optional<Color> m_backgroundColor;	// default = #ffffffff
		std::optional<Color> m_textColor;		// default = #ffffffff
		std::optional<std::string> m_text;		// default = ""
};
}


#endif

