#include <iostream>
#include <QCoreApplication>
#include <QString>

#include "KmlFile.h"
#include "KmlFolder.h"
#include "KmlPoint.h"
#include "KmlTrajectory.h"


int main(int argc, char *argv[])
{
	QCoreApplication app{argc,argv};
	Q_UNUSED(app)

	KmlFile kmlFile{"My kml test file"};

	// point 1
	auto pt1 = std::make_unique<KmlPoint>("Departure", Point{1.37,43.63,151}, "#paddleGreenDot", AltitudeMode::ClampToGround);
	kmlFile.addItem(std::move(pt1));

	// point 2
	auto pt2 = std::make_unique<KmlPoint>("Arrival", Point{1.47,43.63,163}, "#paddleRedDot", AltitudeMode::ClampToGround);
	kmlFile.addItem(std::move(pt2));

	// trajectory
	auto traj = std::make_unique<KmlTrajectory>("Trajectory", "#blueLine5", AltitudeMode::ClampToGround);
	traj->addPoint(Point{1.37,43.63,151});
	traj->addPoint(Point{1.37,43.53,154});
	traj->addPoint(Point{1.47,43.53,158});
	traj->addPoint(Point{1.47,43.63,162});
	kmlFile.addItem(std::move(traj));

	// folder test
	auto pt3 = std::make_unique<KmlPoint>("Point 3", Point{1.335454,43.586060,151.539028}, "#paddleGreenDot", AltitudeMode::ClampToGround);
	auto folder = std::make_unique<KmlFolder>("TestFolder");
	folder->addItem(std::move(pt3));
	kmlFile.addItem(std::move(folder));

	// write file
	QString filePath = QCoreApplication::applicationDirPath() + "/test.kml";
	if (!kmlFile.write(filePath))
	{
		std::cout << "Failed to create kml file" << std::endl;
		std::cout << "Press Enter to terminate" << std::endl;
		std::cin.get();
		return 1;
	}

	std::cout << "Kml file created" << std::endl;
	std::cout << "Press Enter to terminate" << std::endl;
	std::cin.get();
	return 0;
}

