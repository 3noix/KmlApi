#include <iostream>
#include <QCoreApplication>
#include "KmlApi.h"


int main(int argc, char *argv[])
{
	QCoreApplication app{argc,argv};
	Q_UNUSED(app)


	Kml::Document kmlDoc{"My kml test file"};

	// styles test
	Kml::Style styleTest;
	Kml::LineStyle lineStyle;
	Kml::PolyStyle polyStyle;
	lineStyle.setColor(Kml::Color{"#ff00ff7f"});
	lineStyle.setWidth(5);
	polyStyle.setFill(true);
	polyStyle.setOutline(true);
	styleTest.lineStyle = lineStyle;
	styleTest.polyStyle = polyStyle;
	kmlDoc.addStyle("styleTest", styleTest);

	// point 1
	auto pt1 = std::make_unique<Kml::SpecialPoint>("Departure", Kml::SimplePoint{1.37,43.63,151}, "#paddleGreenDot", Kml::AltitudeMode::ClampToGround);
	kmlDoc.addItem(std::move(pt1));

	// point 2
	auto pt2 = std::make_unique<Kml::SpecialPoint>("Arrival", Kml::SimplePoint{1.47,43.63,163}, "#paddleRedDot", Kml::AltitudeMode::ClampToGround);
	kmlDoc.addItem(std::move(pt2));

	// trajectory
	auto traj = std::make_unique<Kml::Trajectory>("Trajectory", "#blueLine5", Kml::AltitudeMode::ClampToGround);
	traj->addPoint(Kml::SimplePoint{1.37,43.63,151});
	traj->addPoint(Kml::SimplePoint{1.37,43.53,154});
	traj->addPoint(Kml::SimplePoint{1.47,43.53,158});
	traj->addPoint(Kml::SimplePoint{1.47,43.63,162});
	traj->setAltitudeOffset(10);
	kmlDoc.addItem(std::move(traj));

	// folder test
	auto pt3 = std::make_unique<Kml::SpecialPoint>("Point 3", Kml::SimplePoint{1.335454,43.586060,151.539028}, "#paddleGreenDot", Kml::AltitudeMode::ClampToGround);
	auto folder = std::make_unique<Kml::Folder>("TestFolder");
	folder->addItem(std::move(pt3));
	kmlDoc.addItem(std::move(folder));

	// write file
	std::string filePath = QCoreApplication::applicationDirPath().toStdString() + "/test.kml";
	if (!kmlDoc.write(filePath))
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

