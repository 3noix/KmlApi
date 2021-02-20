CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}


TEMPLATE = app
TARGET = KmlApp
CONFIG += c++17 console
DESTDIR = $$MODE
OBJECTS_DIR = $$MODE/objects
MOC_DIR = $$MODE/moc
QT = core


SOURCES += main.cpp \
		   KmlDocument.cpp \
		   KmlAbstractItem.cpp \
		   KmlFolder.cpp \
		   KmlSpecialPoint.cpp \
		   KmlTrajectory.cpp \
		   KmlStyle.cpp \
		   KmlSubStyles.cpp \
		   KmlColor.cpp

