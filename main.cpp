#include <QCoreApplication>
#include <QString>
#include <QFile>

#include <iostream>
#include <vector>
#include <cmath>
#include <functional>


// @3: enums and structures
enum class AltitudeMode
{
	Absolute,
	ClampToGround,
	ClampToSeaFloor,
	RelativeToGround,
	RelativeToSeaFloor
};

struct Point
{
	double lon = 0.0;
	double lat = 0.0;
	double alt = 0.0;
};

struct SpecialPoint
{
	QString name;
	QString description = "<![CDATA[]]>";
	QString styleUrl;
	Point point;
};

struct Trajectory
{
	QString name;
	QString description = "<![CDATA[]]>";
	QString styleUrl;
	std::vector<Point> points;
};


// @3: creation of trajectory points from lambdas
using Function = std::function<double(double)>;

std::vector<Point> createPoints(double t1, double t2, double dt, Function lat, Function lon, Function alt)
{
	if (t1 > t2 || dt <= 0) {return {};}
	int n = 1 + std::floor((t2-t1)/dt);
	std::vector<Point> points;
	points.reserve(n+10);

	for (double t=t1; t<=t2; t+=dt) {points.push_back(Point{lat(t),lon(t),alt(t)});}
	return points;
}


// @3: KmlFile
class KmlFile
{
	public:
		KmlFile()
		{
			description = "<![CDATA[]]>";
			styles.insert({"start","<IconStyle><Icon><href>http://maps.gstatic.com/mapfiles/ms2/micons/green-dot.png</href></Icon></IconStyle>"});
			styles.insert({"end","<IconStyle><Icon><href>http://maps.gstatic.com/mapfiles/ms2/micons/red-dot.png</href></Icon></IconStyle>"});
			styles.insert({"track","<LineStyle><color>73FF0000</color><width>5</width></LineStyle>"});
		};
		
		KmlFile(const KmlFile &other) = delete;
		KmlFile(KmlFile &&other) = delete;
		KmlFile& operator=(const KmlFile &other) = delete;
		KmlFile& operator=(KmlFile &&other) = delete;
		~KmlFile() = default;

		QString toString() const
		{
			QString str = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
			str += "<kml xmlns=\"http://www.opengis.net/kml/2.2\" xmlns:gx=\"http://www.google.com/kml/ext/2.2\">\n";
			str += "\t<Document>\n";
			str += "\t\t<name>" + this->name + "</name>\n";
			str += "\t\t<description>" + this->description + "</description>\n";

			// styles
			for (const auto& [id, content] : this->styles) {str += "\t\t<Style id=\"" + id + "\">" + content + "</Style>\n";}

			// points
			for (const SpecialPoint &sp : this->specialPoints)
			{
				str += "\t\t<Placemark>\n";
				str += "\t\t\t<name>" + sp.name + "</name>\n";
				str += "\t\t\t<description>" + sp.description + "</description>\n";
				str += "\t\t\t<styleUrl>" + sp.styleUrl + "</styleUrl>\n";
				str += "\t\t\t<Point>\n";
				str += "\t\t\t\t" + getAltitudeModeStr() + "\n";
				str += "\t\t\t\t<coordinates>" + QString::number(sp.point.lon) + "," + QString::number(sp.point.lat) + "," + QString::number(sp.point.alt) + "</coordinates>\n";
				str += "\t\t\t</Point>\n";
				str += "\t\t</Placemark>\n";
			}

			// trajectories
			for (const Trajectory &traj : this->trajectories)
			{
				str += "\t\t<Placemark>\n";
				str += "\t\t\t<name>" + traj.name + "</name>\n";
				str += "\t\t\t<description>" + traj.description + "</description>\n";
				str += "\t\t\t<styleUrl>" + traj.styleUrl + "</styleUrl>\n";
				str += "\t\t\t<LineString>\n";
				str += "\t\t\t\t" + getAltitudeModeStr() + "\n";
				str += "\t\t\t\t<tessellate>1</tessellate>\n";
				str += "\t\t\t\t<coordinates>\n";
				for (const Point &p : traj.points) {str += "\t\t\t\t\t" + QString::number(p.lon) + "," + QString::number(p.lat) + "," + QString::number(p.alt) + "\n";}
				str += "\t\t\t\t</coordinates>\n";
				str += "\t\t\t</LineString>\n";
				str += "\t\t</Placemark>\n";
			}

			str += "\t</Document>\n";
			str += "</kml>\n";
			return str;
		};
		
		
	public:
		QString name;
		QString description;
		std::map<QString,QString> styles; // the key is the id (or url), the value is the xml content
		std::vector<SpecialPoint> specialPoints;
		std::vector<Trajectory> trajectories;
		AltitudeMode altitudeMode = AltitudeMode::Absolute;


	private:
		QString getAltitudeModeStr() const
		{
			if (this->altitudeMode == AltitudeMode::Absolute)           {return "<altitudeMode>absolute</altitudeMode>";}
			if (this->altitudeMode == AltitudeMode::ClampToGround)      {return "<altitudeMode>clampToGround</altitudeMode>";}
			if (this->altitudeMode == AltitudeMode::ClampToSeaFloor)    {return "<gx:altitudeMode>clampToSeaFloor</gx:altitudeMode>";}
			if (this->altitudeMode == AltitudeMode::RelativeToGround)   {return "<altitudeMode>relativeToGround</altitudeMode>";}
			if (this->altitudeMode == AltitudeMode::RelativeToSeaFloor) {return "<gx:altitudeMode>relativeToSeaFloor</gx:altitudeMode>";}
			return "<altitudeMode>absolute</altitudeMode>";
		};
};


// @3: main
int main(int argc, char *argv[])
{
	QCoreApplication app{argc,argv};
	Q_UNUSED(app)

	KmlFile kml;
	kml.name = "My kml test file";
	kml.altitudeMode = AltitudeMode::ClampToGround;

	// point 1
	SpecialPoint p1;
	p1.name = "Departure";
	p1.styleUrl = "#start";
	p1.point = Point{1.37,43.63,151};
	kml.specialPoints.push_back(p1);

	// point 2
	SpecialPoint p2;
	p2.name = "Arrival";
	p2.styleUrl = "#end";
	p2.point = Point{1.47,43.63,163};
	kml.specialPoints.push_back(p2);

	// trajectory
	Trajectory traj;
	traj.name = "Trajectory";
	traj.styleUrl = "#track";
	traj.points.push_back(Point{1.37,43.63,151});
	traj.points.push_back(Point{1.37,43.53,154});
	traj.points.push_back(Point{1.47,43.53,158});
	traj.points.push_back(Point{1.47,43.63,162});
	kml.trajectories.push_back(traj);

	// write file
	QString filePath = QCoreApplication::applicationDirPath() + "/test.kml";
	QFile file{filePath};
	if (!file.open(QIODevice::WriteOnly))
	{
		std::cout << "Failed to create kml file" << std::endl;
		std::cout << "Press Enter to terminate" << std::endl;
		std::cin.get();
		return 1;
	}
	file.write(kml.toString().toUtf8());
	file.close();
	
	// the end
	std::cout << "Kml file created" << std::endl;
	std::cout << "Press Enter to terminate" << std::endl;
	std::cin.get();
	return 0;
}

