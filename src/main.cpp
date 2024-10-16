#include "mainwindow/mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

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
    //w.setWindowState(Qt::WindowMaximized);
    w.show();
    return a.exec();
}

/*
// Create the ScribbleArea widget and make it
    // the central widget
    scribbleArea = new ScribbleArea;
    setCentralWidget(scribbleArea);

    // Create actions and menus
    createActions();
    createMenus();

    // Set the title
    setWindowTitle(tr("Scribble"));
*/