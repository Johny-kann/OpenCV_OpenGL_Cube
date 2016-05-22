#-------------------------------------------------
#
# Project created by QtCreator 2016-05-11T11:22:22
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenCV_OpenGL
TEMPLATE = app


#INCLUDEPATH += `pkg-config --cflags opencv`
#LIBS += `pkg-config --libs opencv`


SOURCES += main.cpp\
        mainwindow.cpp \
    openglwindow.cpp \
    texturemapping.cpp \
    camera.cpp

HEADERS  += mainwindow.h \
    openglwindow.h \
    texturemapping.h \
    camera.h

FORMS    +=

RESOURCES += \
    resources.qrc
