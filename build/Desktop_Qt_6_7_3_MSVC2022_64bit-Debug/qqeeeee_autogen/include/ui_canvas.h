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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Canvas
{
public:
    QAction *open_button_canvas;
    QAction *save_button_canvas;
    QAction *actionPen;
    QAction *actionEraiser;
    QAction *actionSelecting;
    QAction *actionAbout;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer;
    QWidget *canvas_space;
    QSpacerItem *horizontalSpacer_2;
    QMenuBar *menubar;
    QMenu *menuOpen;
    QMenu *menuTools;
    QMenu *menuOptions;

    void setupUi(QMainWindow *Canvas)
    {
        if (Canvas->objectName().isEmpty())
            Canvas->setObjectName("Canvas");
        Canvas->resize(1127, 590);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Canvas->sizePolicy().hasHeightForWidth());
        Canvas->setSizePolicy(sizePolicy);
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::MediaRecord));
        Canvas->setWindowIcon(icon);
        open_button_canvas = new QAction(Canvas);
        open_button_canvas->setObjectName("open_button_canvas");
        save_button_canvas = new QAction(Canvas);
        save_button_canvas->setObjectName("save_button_canvas");
        actionPen = new QAction(Canvas);
        actionPen->setObjectName("actionPen");
        actionEraiser = new QAction(Canvas);
        actionEraiser->setObjectName("actionEraiser");
        actionSelecting = new QAction(Canvas);
        actionSelecting->setObjectName("actionSelecting");
        actionAbout = new QAction(Canvas);
        actionAbout->setObjectName("actionAbout");
        centralwidget = new QWidget(Canvas);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        horizontalSpacer = new QSpacerItem(200, 20, QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 30, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Maximum);

        gridLayout->addItem(verticalSpacer_2, 2, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 30, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Maximum);

        gridLayout->addItem(verticalSpacer, 0, 1, 1, 1);

        canvas_space = new QWidget(centralwidget);
        canvas_space->setObjectName("canvas_space");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(canvas_space->sizePolicy().hasHeightForWidth());
        canvas_space->setSizePolicy(sizePolicy1);
        canvas_space->setMaximumSize(QSize(1782, 917));
        canvas_space->setStyleSheet(QString::fromUtf8(" ui->canvas_space->setStyleSheet(\"border: 2px solid black; border-radius: 10px; background-color: lightgray;\");"));

        gridLayout->addWidget(canvas_space, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 0, 1, 1);

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
        menuOpen->addAction(save_button_canvas);
        menuOpen->addAction(actionAbout);
        menuTools->addAction(actionPen);
        menuTools->addAction(actionEraiser);
        menuTools->addAction(actionSelecting);

        retranslateUi(Canvas);

        QMetaObject::connectSlotsByName(Canvas);
    } // setupUi

    void retranslateUi(QMainWindow *Canvas)
    {
        Canvas->setWindowTitle(QCoreApplication::translate("Canvas", "wps", nullptr));
        open_button_canvas->setText(QCoreApplication::translate("Canvas", "Open", nullptr));
        save_button_canvas->setText(QCoreApplication::translate("Canvas", "Save", nullptr));
        actionPen->setText(QCoreApplication::translate("Canvas", "Pen", nullptr));
        actionEraiser->setText(QCoreApplication::translate("Canvas", "Eraiser", nullptr));
        actionSelecting->setText(QCoreApplication::translate("Canvas", "Selecting", nullptr));
        actionAbout->setText(QCoreApplication::translate("Canvas", "About", nullptr));
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
