#ifndef KML_FILE
#define KML_FILE


#include <map>
#include <vector>
#include <QString>
#include "SpecialPoint.h"
#include "Trajectory.h"


class KmlFile
{
	public:
		KmlFile(const QString &name, const QString &description = "<![CDATA[]]>")
		{
			m_name = name;
			m_description = description;
			m_styles.insert({"start","<IconStyle><Icon><href>http://maps.gstatic.com/mapfiles/ms2/micons/green-dot.png</href></Icon></IconStyle>"});
			m_styles.insert({"end","<IconStyle><Icon><href>http://maps.gstatic.com/mapfiles/ms2/micons/red-dot.png</href></Icon></IconStyle>"});
			m_styles.insert({"track","<LineStyle><color>73FF0000</color><width>5</width></LineStyle>"});
		};

		KmlFile(const KmlFile &other) = delete;
		KmlFile(KmlFile &&other) = delete;
		KmlFile& operator=(const KmlFile &other) = delete;
		KmlFile& operator=(KmlFile &&other) = delete;
		~KmlFile() = default;


		void addSpecialPoints(const SpecialPoint &sp) {m_specialPoints.push_back(sp);};
		void addTrajectory(const Trajectory &traj) {m_trajectories.push_back(traj);};

		void setName(const QString &name) {m_name = name;};
		QString name() const {return m_name;};

		void setDescription(const QString &description) {m_description = description;};
		QString description() const {return m_description;};

		void addStyle(const QString &styleUrl, const QString &styleContent) {m_styles.insert({styleUrl,styleContent});};


		QString toString() const
		{
			QString str = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
			str += "<kml xmlns=\"http://www.opengis.net/kml/2.2\" xmlns:gx=\"http://www.google.com/kml/ext/2.2\">\n";
			str += "\t<Document>\n";
			str += "\t\t<name>" + m_name + "</name>\n";
			str += "\t\t<description>" + m_description + "</description>\n";

			// styles
			for (const auto& [id, content] : m_styles) {str += "\t\t<Style id=\"" + id + "\">" + content + "</Style>\n";}

			// points
			for (const SpecialPoint &sp : m_specialPoints)
			{
				str += "\t\t<Placemark>\n";
				str += "\t\t\t<name>" + sp.name() + "</name>\n";
				str += "\t\t\t<description>" + sp.description() + "</description>\n";
				str += "\t\t\t<styleUrl>" + sp.styleUrl() + "</styleUrl>\n";
				str += "\t\t\t<Point>\n";
				str += "\t\t\t\t" + altitudeModeToStr(sp.altitudeMode()) + "\n";
				str += "\t\t\t\t<coordinates>" + QString::number(sp.m_point.lon) + "," + QString::number(sp.m_point.lat) + "," + QString::number(sp.m_point.alt) + "</coordinates>\n";
				str += "\t\t\t</Point>\n";
				str += "\t\t</Placemark>\n";
			}

			// trajectories
			for (const Trajectory &traj : m_trajectories)
			{
				str += "\t\t<Placemark>\n";
				str += "\t\t\t<name>" + traj.name() + "</name>\n";
				str += "\t\t\t<description>" + traj.description() + "</description>\n";
				str += "\t\t\t<styleUrl>" + traj.styleUrl() + "</styleUrl>\n";
				str += "\t\t\t<LineString>\n";
				str += "\t\t\t\t" + altitudeModeToStr(traj.altitudeMode()) + "\n";
				str += "\t\t\t\t<tessellate>1</tessellate>\n";
				str += "\t\t\t\t<coordinates>\n";
				for (const Point &p : traj.m_points) {str += "\t\t\t\t\t" + QString::number(p.lon) + "," + QString::number(p.lat) + "," + QString::number(p.alt) + "\n";}
				str += "\t\t\t\t</coordinates>\n";
				str += "\t\t\t</LineString>\n";
				str += "\t\t</Placemark>\n";
			}

			str += "\t</Document>\n";
			str += "</kml>\n";
			return str;
		};
		
		
	private:
		static QString altitudeModeToStr(AltitudeMode am)
		{
			if (am == AltitudeMode::Absolute)           {return "<altitudeMode>absolute</altitudeMode>";}
			if (am == AltitudeMode::ClampToGround)      {return "<altitudeMode>clampToGround</altitudeMode>";}
			if (am == AltitudeMode::ClampToSeaFloor)    {return "<gx:altitudeMode>clampToSeaFloor</gx:altitudeMode>";}
			if (am == AltitudeMode::RelativeToGround)   {return "<altitudeMode>relativeToGround</altitudeMode>";}
			if (am == AltitudeMode::RelativeToSeaFloor) {return "<gx:altitudeMode>relativeToSeaFloor</gx:altitudeMode>";}
			return "<altitudeMode>absolute</altitudeMode>";
		};

		QString m_name;
		QString m_description;
		std::map<QString,QString> m_styles; // the key is the id (or url), the value is the xml content
		std::vector<SpecialPoint> m_specialPoints;
		std::vector<Trajectory> m_trajectories;
};


#endif

