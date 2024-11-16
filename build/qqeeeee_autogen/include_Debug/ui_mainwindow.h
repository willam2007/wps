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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QFrame *choose_project_frame;
    QVBoxLayout *verticalLayout;
    QSpacerItem *choose_project_verticalSpacer;
    QLabel *choose_label;
    QSpacerItem *choose_project_verticalSpacer_2;
    QFrame *choose_project_frame1;
    QHBoxLayout *horizontalLayout;
    QPushButton *create_button_project;
    QSpacerItem *choose_project_horizontalSpacer;
    QPushButton *choose_button_project;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->setEnabled(true);
        MainWindow->resize(279, 215);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
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
        centralwidget->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy1);
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        choose_project_frame = new QFrame(centralwidget);
        choose_project_frame->setObjectName("choose_project_frame");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(choose_project_frame->sizePolicy().hasHeightForWidth());
        choose_project_frame->setSizePolicy(sizePolicy2);
        choose_project_frame->setFrameShape(QFrame::Shape::Box);
        choose_project_frame->setFrameShadow(QFrame::Shadow::Plain);
        choose_project_frame->setLineWidth(3);
        verticalLayout = new QVBoxLayout(choose_project_frame);
        verticalLayout->setObjectName("verticalLayout");
        choose_project_verticalSpacer = new QSpacerItem(40, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        verticalLayout->addItem(choose_project_verticalSpacer);

        choose_label = new QLabel(choose_project_frame);
        choose_label->setObjectName("choose_label");
        sizePolicy1.setHeightForWidth(choose_label->sizePolicy().hasHeightForWidth());
        choose_label->setSizePolicy(sizePolicy1);
        QFont font;
        font.setPointSize(16);
        choose_label->setFont(font);
        choose_label->setTextFormat(Qt::TextFormat::RichText);
        choose_label->setScaledContents(false);
        choose_label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(choose_label);

        choose_project_verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        verticalLayout->addItem(choose_project_verticalSpacer_2);

        choose_project_frame1 = new QFrame(choose_project_frame);
        choose_project_frame1->setObjectName("choose_project_frame1");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(choose_project_frame1->sizePolicy().hasHeightForWidth());
        choose_project_frame1->setSizePolicy(sizePolicy3);
        choose_project_frame1->setFrameShape(QFrame::Shape::Box);
        choose_project_frame1->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout = new QHBoxLayout(choose_project_frame1);
        horizontalLayout->setObjectName("horizontalLayout");
        create_button_project = new QPushButton(choose_project_frame1);
        create_button_project->setObjectName("create_button_project");
        sizePolicy1.setHeightForWidth(create_button_project->sizePolicy().hasHeightForWidth());
        create_button_project->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(create_button_project);

        choose_project_horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(choose_project_horizontalSpacer);

        choose_button_project = new QPushButton(choose_project_frame1);
        choose_button_project->setObjectName("choose_button_project");
        sizePolicy1.setHeightForWidth(choose_button_project->sizePolicy().hasHeightForWidth());
        choose_button_project->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(choose_button_project);


        verticalLayout->addWidget(choose_project_frame1);


        gridLayout->addWidget(choose_project_frame, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "wps", nullptr));
        choose_label->setText(QCoreApplication::translate("MainWindow", "Choose what to do", nullptr));
        create_button_project->setText(QCoreApplication::translate("MainWindow", "Create", nullptr));
        choose_button_project->setText(QCoreApplication::translate("MainWindow", "Choose Project", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
