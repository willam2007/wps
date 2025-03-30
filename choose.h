#ifndef CHOOSE_H
#define CHOOSE_H

#include "ui_choose.h"
#include "mainwindow.h"

#include <QMainWindow>
#include <qpropertyanimation.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class Choose;
}
QT_END_NAMESPACE

class Canvas; // Canvas используется для окна с полотном

class Choose : public QMainWindow
{
    Q_OBJECT

public:
    explicit Choose(QWidget *parent = nullptr);
    ~Choose() {delete ui;}; // Удаляем интерфейс, чтобы освободить память

private slots:
    void on_pushButton_1920_1080_clicked();

    void on_pushButton_1280_720_clicked();

    void on_pushButton__1080_1080_clicked();

    void on_pushButton_random_clicked();

    void on_pushButton_create_clicked();

    void on_pushButton_back_clicked();

private:
    Ui::Choose *ui;
    Canvas *canvas;
    QPropertyAnimation *fadeAnimation;
};

#endif // CHOOSE_H
