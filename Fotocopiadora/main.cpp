#include <QtGui/QApplication>
#include "mainwindow.h"
#include "fotocopiadora.h"

int main(int argc, char *argv[])
{
    Fotocopiadora _Fotocopiadora;


    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    _Fotocopiadora.initAll();

    return a.exec();
}
