#include "mainwindow/mainwindow.h"
#include "canvas/canvas.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    //w.resize(280, 215);
    w.setFixedSize(280, 215);
    //w.setWindowState(Qt::WindowMaximized);
    w.show();

    return a.exec();
}

