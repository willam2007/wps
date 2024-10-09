/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QLabel *label;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->setEnabled(true);
        MainWindow->resize(793, 600);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setFocusPolicy(Qt::FocusPolicy::TabFocus);
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::MediaRecord));
        MainWindow->setWindowIcon(icon);
        MainWindow->setTabShape(QTabWidget::TabShape::Rounded);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(50, 260, 691, 181));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(78);
        font.setItalic(true);
        pushButton->setFont(font);
        pushButton->setCursor(QCursor(Qt::CursorShape::ForbiddenCursor));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(100, 50, 461, 91));
        QFont font1;
        font1.setPointSize(22);
        label->setFont(font1);
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(50, 260, 691, 181));
        QFont font2;
        font2.setPointSize(59);
        pushButton_2->setFont(font2);
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(410, 130, 201, 41));
        pushButton_3->setCursor(QCursor(Qt::CursorShape::WaitCursor));
        pushButton_3->setMouseTracking(true);
        pushButton_3->setTabletTracking(false);
        pushButton_3->setContextMenuPolicy(Qt::ContextMenuPolicy::DefaultContextMenu);
        pushButton_3->setAutoFillBackground(false);
        pushButton_3->setCheckable(false);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 793, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);

        retranslateUi(MainWindow);
        QObject::connect(pushButton, &QPushButton::clicked, MainWindow, qOverload<>(&QMainWindow::close));
        QObject::connect(pushButton_2, &QPushButton::clicked, pushButton_2, qOverload<>(&QPushButton::close));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "wps", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\320\235\320\265 \320\272\320\273\320\270\320\272\320\260\321\202\320\254!!!", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\270\320\262\320\265\321\202, \321\215\321\202\320\276 \320\275\320\260\321\210 \321\200\320\265\320\264\320\260\320\272\321\202\320\276\321\200 wps", nullptr));
#if QT_CONFIG(whatsthis)
        pushButton_2->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
#if QT_CONFIG(accessibility)
        pushButton_2->setAccessibleDescription(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273\321\217", nullptr));
#endif // QT_CONFIG(accessibility)
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\266\320\274\320\270", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_3->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>\320\232\320\276\320\273\321\217 \320\273\320\276\321\205</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(accessibility)
        pushButton_3->setAccessibleDescription(QString());
#endif // QT_CONFIG(accessibility)
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "\320\241\321\216\320\264\320\260 \320\274\320\276\320\266\320\275\320\276 \320\275\320\260\320\266\320\260\321\202\321\214\n"
"\320\220 \320\265\321\211\320\265 \321\202\320\265\320\272\321\201\321\202 \320\265\321\201\320\273\320\270 \320\264\320\276\320\273\320\263\320\276 \320\275\320\260\320\262\320\265\321\201\321\202\320\270", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
