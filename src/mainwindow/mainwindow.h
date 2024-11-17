#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

#include <QList>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class Canvas; // Canvas используется для окна с полотном

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() {delete ui;}; // Удаляем интерфейс, чтобы освободить память

private slots:
    void on_create_button_project_clicked();  // Обработчик нажатия кнопки создания проекта
    void on_choose_button_project_clicked();  // Обработчик нажатия кнопки выбора проекта

private:
    Ui::MainWindow *ui;
    Canvas *canvas;

};

#endif
