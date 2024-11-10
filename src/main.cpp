#include "mainwindow/mainwindow.h"
#include "canvas/canvas.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    system("chcp 65001");
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "wps_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    Canvas c;
    w.resize(280, 215);
    //w.setWindowState(Qt::WindowMaximized);
    w.show();
    //c.show();

    return a.exec();
}
