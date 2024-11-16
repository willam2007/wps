/********************************************************************************
** Form generated from reading UI file 'canvas_editor.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CANVAS_EDITOR_H
#define UI_CANVAS_EDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_canvas_editor
{
public:
    QFrame *frame;
    QListWidget *listWidget;
    QPushButton *pushButton;

    void setupUi(QWidget *canvas_editor)
    {
        if (canvas_editor->objectName().isEmpty())
            canvas_editor->setObjectName("canvas_editor");
        canvas_editor->resize(1021, 616);
        frame = new QFrame(canvas_editor);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 1021, 51));
        frame->setFrameShape(QFrame::Shape::Box);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        frame->setLineWidth(3);
        listWidget = new QListWidget(frame);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(10, 10, 61, 31));
        pushButton = new QPushButton(frame);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(10, 10, 75, 24));

        retranslateUi(canvas_editor);

        QMetaObject::connectSlotsByName(canvas_editor);
    } // setupUi

    void retranslateUi(QWidget *canvas_editor)
    {
        canvas_editor->setWindowTitle(QCoreApplication::translate("canvas_editor", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("canvas_editor", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class canvas_editor: public Ui_canvas_editor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CANVAS_EDITOR_H
