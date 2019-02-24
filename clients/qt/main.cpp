#ifndef QT5
    #include <QtGui/QApplication>
#else
    #include <QtWidgets/QApplication>
#endif
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
