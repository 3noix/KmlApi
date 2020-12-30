#include <iostream>
#include <QCoreApplication>
#include <QString>
#include <QFile>

#include "KmlFile.h"
#include "KmlFolder.h"
#include "KmlPoint.h"
#include "KmlTrajectory.h"


int main(int argc, char *argv[])
{
	QCoreApplication app{argc,argv};
	Q_UNUSED(app)

	KmlFile kml{"My kml test file"};

	// point 1
	std::unique_ptr<KmlPoint> p1 = std::make_unique<KmlPoint>("Departure", Point{1.37,43.63,151}, "#paddleGreenDot", AltitudeMode::ClampToGround);
	kml.addItem(std::move(p1));

	// point 2
	std::unique_ptr<KmlPoint> p2 = std::make_unique<KmlPoint>("Arrival", Point{1.47,43.63,163}, "#paddleRedDot", AltitudeMode::ClampToGround);
	kml.addItem(std::move(p2));

	// trajectory
	std::unique_ptr<KmlTrajectory> traj = std::make_unique<KmlTrajectory>("Trajectory", "#blueLine5", AltitudeMode::ClampToGround);
	traj->addPoint(Point{1.37,43.63,151});
	traj->addPoint(Point{1.37,43.53,154});
	traj->addPoint(Point{1.47,43.53,158});
	traj->addPoint(Point{1.47,43.63,162});
	kml.addItem(std::move(traj));

	// folder test
	std::unique_ptr<KmlPoint> p3 = std::make_unique<KmlPoint>("Point 3", Point{1.335454,43.586060,151.539028}, "#paddleGreenDot", AltitudeMode::ClampToGround);
	std::unique_ptr<KmlFolder> folder = std::make_unique<KmlFolder>("TestFolder");
	folder->addItem(std::move(p3));
	kml.addItem(std::move(folder));

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

