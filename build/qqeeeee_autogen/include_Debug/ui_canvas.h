/********************************************************************************
** Form generated from reading UI file 'canvas.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CANVAS_H
#define UI_CANVAS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Canvas
{
public:
    QAction *open_button_canvas;
    QAction *saveAs_button_canvas;
    QAction *actionPen;
    QAction *actionEraiser;
    QWidget *centralwidget;
    QWidget *canvas_space;
    QMenuBar *menubar;
    QMenu *menuOpen;
    QMenu *menuTools;
    QMenu *menuOptions;

    void setupUi(QMainWindow *Canvas)
    {
        if (Canvas->objectName().isEmpty())
            Canvas->setObjectName("Canvas");
        Canvas->resize(1127, 590);
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::MediaRecord));
        Canvas->setWindowIcon(icon);
        open_button_canvas = new QAction(Canvas);
        open_button_canvas->setObjectName("open_button_canvas");
        saveAs_button_canvas = new QAction(Canvas);
        saveAs_button_canvas->setObjectName("saveAs_button_canvas");
        actionPen = new QAction(Canvas);
        actionPen->setObjectName("actionPen");
        actionEraiser = new QAction(Canvas);
        actionEraiser->setObjectName("actionEraiser");
        centralwidget = new QWidget(Canvas);
        centralwidget->setObjectName("centralwidget");
        canvas_space = new QWidget(centralwidget);
        canvas_space->setObjectName("canvas_space");
        canvas_space->setGeometry(QRect(30, 60, 1441, 761));
        canvas_space->setStyleSheet(QString::fromUtf8(" ui->canvas_space->setStyleSheet(\"border: 2px solid black; border-radius: 10px; background-color: lightgray;\");"));
        Canvas->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Canvas);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1127, 22));
        menuOpen = new QMenu(menubar);
        menuOpen->setObjectName("menuOpen");
        menuTools = new QMenu(menubar);
        menuTools->setObjectName("menuTools");
        menuOptions = new QMenu(menubar);
        menuOptions->setObjectName("menuOptions");
        Canvas->setMenuBar(menubar);

        menubar->addAction(menuOpen->menuAction());
        menubar->addAction(menuTools->menuAction());
        menubar->addAction(menuOptions->menuAction());
        menuOpen->addAction(open_button_canvas);
        menuOpen->addAction(saveAs_button_canvas);
        menuTools->addAction(actionPen);
        menuTools->addAction(actionEraiser);

        retranslateUi(Canvas);

        QMetaObject::connectSlotsByName(Canvas);
    } // setupUi

    void retranslateUi(QMainWindow *Canvas)
    {
        Canvas->setWindowTitle(QCoreApplication::translate("Canvas", "wps", nullptr));
        open_button_canvas->setText(QCoreApplication::translate("Canvas", "Open", nullptr));
        saveAs_button_canvas->setText(QCoreApplication::translate("Canvas", "Save As", nullptr));
        actionPen->setText(QCoreApplication::translate("Canvas", "Pen", nullptr));
        actionEraiser->setText(QCoreApplication::translate("Canvas", "Eraiser", nullptr));
        menuOpen->setTitle(QCoreApplication::translate("Canvas", "File", nullptr));
        menuTools->setTitle(QCoreApplication::translate("Canvas", "Tools", nullptr));
        menuOptions->setTitle(QCoreApplication::translate("Canvas", "Options", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Canvas: public Ui_Canvas {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CANVAS_H
