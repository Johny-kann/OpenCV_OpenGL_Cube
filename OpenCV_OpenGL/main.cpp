#include "mainwindow.h"
#include "openglwindow.h"
#include <QApplication>
#include "texturemapping.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TextureMapping w;

    QSurfaceFormat format;
    format.setSamples(16);

    w.setFormat(format);
    w.resize(640,480);

    w.show();

    w.setAnimating(true);

    return a.exec();
}
