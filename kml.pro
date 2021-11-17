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


SOURCES += src/main.cpp \
		   src/KmlDocument.cpp \
		   src/KmlAbstractItem.cpp \
		   src/KmlFolder.cpp \
		   src/KmlSpecialPoint.cpp \
		   src/KmlTrajectory.cpp \
		   src/KmlStyle.cpp \
		   src/KmlSubStyles.cpp \
		   src/KmlColor.cpp

