#include <iostream>
#include <QCoreApplication>
#include <QString>
#include <QFile>

#include "KmlFile.h"
#include "KmlPoint.h"
#include "KmlTrajectory.h"


int main(int argc, char *argv[])
{
	QCoreApplication app{argc,argv};
	Q_UNUSED(app)

	KmlFile kml{"My kml test file"};

	// point 1
	KmlPoint *p1 = new KmlPoint{"Departure", Point{1.37,43.63,151}, "#paddleGreenDot", AltitudeMode::ClampToGround};
	kml.addItem(p1);

	// point 2
	KmlPoint *p2 = new KmlPoint{"Arrival", Point{1.47,43.63,163}, "#paddleRedDot", AltitudeMode::ClampToGround};
	kml.addItem(p2);

	// trajectory
	KmlTrajectory *traj = new KmlTrajectory{"Trajectory", "#blueLine5", AltitudeMode::ClampToGround};
	traj->addPoint(Point{1.37,43.63,151});
	traj->addPoint(Point{1.37,43.53,154});
	traj->addPoint(Point{1.47,43.53,158});
	traj->addPoint(Point{1.47,43.63,162});
	kml.addItem(traj);

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

