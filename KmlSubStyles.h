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


std::string colorModeToString(ColorMode cm);
std::string hotspotUnitToString(HotspotUnit hsu);
std::string refreshModeToString(RefreshMode rm);
std::string viewRefreshModeToString(ViewRefreshMode vrm);


// @1: IconStyle
class Icon
{
	public:
		Icon() = default;
		Icon(const std::string &href);
		Icon(const Icon &other) = default;
		Icon(Icon &&other) = default;
		Icon& operator=(const Icon &other) = default;
		Icon& operator=(Icon &&other) = default;
		~Icon() = default;

		Icon& setHref(const std::string &href);
		Icon& setX(int x);
		Icon& setY(int y);
		Icon& setW(int w);
		Icon& setH(int h);
		Icon& setRefreshMode(RefreshMode rm);
		Icon& setRefreshInterval(double ri);
		Icon& setViewRefreshMode(ViewRefreshMode vrm);
		Icon& setViewRefreshTime(double vrt);
		Icon& setViewBoundScale(double vbs);
		Icon& setViewFormat(const std::string &vf);
		Icon& setHttpQuery(const std::string &httpQuery);

		std::string toString(std::size_t tabs = 0) const;
		
		
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

		IconStyle& setColor(Color c);
		IconStyle& setColorMode(ColorMode cm);
		IconStyle& setScale(double s);
		IconStyle& setHeading(double h);
		IconStyle& setIcon(const Icon &icon);
		IconStyle& setHotspot(Hotspot hs);

		std::string toString(std::size_t tabs = 0) const;
		
		
	private:
		std::optional<Color> m_color;			// default = #ffffffff
		std::optional<ColorMode> m_colorMode;	// default = Normal
		std::optional<double> m_scale;			// default = 1
		std::optional<double> m_heading;		// default = 0
		std::optional<Icon> m_icon;
		std::optional<Hotspot> m_hotspot;
};


// @1: LabelStyle
class LabelStyle
{
	public:
		LabelStyle() = default;
		LabelStyle(const LabelStyle &other) = default;
		LabelStyle(LabelStyle &&other) = default;
		LabelStyle& operator=(const LabelStyle &other) = default;
		LabelStyle& operator=(LabelStyle &&other) = default;
		~LabelStyle() = default;

		LabelStyle& setColor(Color c);
		LabelStyle& setColorMode(ColorMode cm);
		LabelStyle& setScale(double s);

		std::string toString(std::size_t tabs = 0) const;
		
		
	private:
		std::optional<Color> m_color;			// default = #ffffffff
		std::optional<ColorMode> m_colorMode;	// default = Normal
		std::optional<double> m_scale;			// default = 1
};


// @1: LineStyle
class LineStyle
{
	public:
		LineStyle() = default;
		LineStyle(const LineStyle &other) = default;
		LineStyle(LineStyle &&other) = default;
		LineStyle& operator=(const LineStyle &other) = default;
		LineStyle& operator=(LineStyle &&other) = default;
		~LineStyle() = default;

		LineStyle& setColor(Color c);
		LineStyle& setColorMode(ColorMode cm);
		LineStyle& setWidth(double w);
		LineStyle& setOuterColor(Color oc);
		LineStyle& setOuterWidth(double ow);
		LineStyle& setPhysicalWidth(double pw);
		LineStyle& setLabelVisible(bool visible);

		std::string toString(std::size_t tabs = 0) const;
		
		
	private:
		std::optional<Color> m_color;			// default = #ffffffff
		std::optional<ColorMode> m_colorMode;	// default = Normal
		std::optional<double> m_width;			// default = 1
		std::optional<Color> m_outerColor;		// default = #ffffffff
		std::optional<double> m_outerWidth;		// default = 0
		std::optional<double> m_physicalWidth;	// default = 0
		std::optional<bool> m_labelVisible;		// default = false
};


// @1: PolyStyle
class PolyStyle
{
	public:
		PolyStyle() = default;
		PolyStyle(const PolyStyle &other) = default;
		PolyStyle(PolyStyle &&other) = default;
		PolyStyle& operator=(const PolyStyle &other) = default;
		PolyStyle& operator=(PolyStyle &&other) = default;
		~PolyStyle() = default;

		PolyStyle& setColor(Color c);
		PolyStyle& setColorMode(ColorMode cm);
		PolyStyle& setFill(bool fill);
		PolyStyle& setOutline(bool outline);

		std::string toString(std::size_t tabs = 0) const;
		
		
	private:
		std::optional<Color> m_color;			// default = #ffffffff
		std::optional<ColorMode> m_colorMode;	// default = Normal
		std::optional<bool> m_fill;				// default = true
		std::optional<bool> m_outline;			// default = true
};


// @1: BalloonStyle
class BalloonStyle
{
	public:
		BalloonStyle() = default;
		BalloonStyle(const BalloonStyle &other) = default;
		BalloonStyle(BalloonStyle &&other) = default;
		BalloonStyle& operator=(const BalloonStyle &other) = default;
		BalloonStyle& operator=(BalloonStyle &&other) = default;
		~BalloonStyle() = default;

		BalloonStyle& setBackgroundColor(Color c);
		BalloonStyle& setTextColor(Color c);
		BalloonStyle& setText(const std::string &text);

		std::string toString(std::size_t tabs = 0) const;
		
		
	private:
		std::optional<Color> m_backgroundColor;	// default = #ffffffff
		std::optional<Color> m_textColor;		// default = #ffffffff
		std::optional<std::string> m_text;		// default = ""
};
}


#endif

