#include <iostream>
#include <QCoreApplication>
#include <QString>
#include <QFile>

#include "KmlFile.h"


int main(int argc, char *argv[])
{
	QCoreApplication app{argc,argv};
	Q_UNUSED(app)

	KmlFile kml{"My kml test file"};

	// point 1
	SpecialPoint p1{"Departure", Point{1.37,43.63,151}, AltitudeMode::ClampToGround};
	p1.setStyleUrl("#start");
	kml.addSpecialPoints(p1);

	// point 2
	SpecialPoint p2{"Arrival", Point{1.47,43.63,163}, AltitudeMode::ClampToGround};
	p2.setStyleUrl("#end");
	kml.addSpecialPoints(p2);

	// trajectory
	Trajectory traj{"Trajectory", AltitudeMode::ClampToGround};
	traj.setStyleUrl("#track");
	traj.addPoint(Point{1.37,43.63,151});
	traj.addPoint(Point{1.37,43.53,154});
	traj.addPoint(Point{1.47,43.53,158});
	traj.addPoint(Point{1.47,43.63,162});
	kml.addTrajectory(traj);

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

