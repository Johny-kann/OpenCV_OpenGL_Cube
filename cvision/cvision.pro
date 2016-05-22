TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

INCLUDEPATH += `pkg-config --cflags opencv`
LIBS += `pkg-config --libs opencv`

RESOURCES += \
    resource.qrc

OTHER_FILES +=
