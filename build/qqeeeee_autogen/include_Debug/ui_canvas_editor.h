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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_canvas_editor
{
public:

    void setupUi(QWidget *canvas_editor)
    {
        if (canvas_editor->objectName().isEmpty())
            canvas_editor->setObjectName("canvas_editor");
        canvas_editor->resize(400, 300);

        retranslateUi(canvas_editor);

        QMetaObject::connectSlotsByName(canvas_editor);
    } // setupUi

    void retranslateUi(QWidget *canvas_editor)
    {
        canvas_editor->setWindowTitle(QCoreApplication::translate("canvas_editor", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class canvas_editor: public Ui_canvas_editor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CANVAS_EDITOR_H
