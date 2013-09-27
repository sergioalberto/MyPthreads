#include <QtGui/QApplication>
#include "mainwindow.h"
#include "fotocopiadora.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Fotocopiadora _Fotocopiadora;
    //_Fotocopiadora.initAll();

    return a.exec();
}
