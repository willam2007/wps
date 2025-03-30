#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "canvas.h"
#include "choose.h"

#include <QtWidgets>
#include <QDebug>

// Конструктор MainWindow
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)  // Инициализируем объект Ui::MainWindow
{
    setAttribute(Qt::WA_StaticContents); // Устанавливаем атрибут статического содержимого
    ui->setupUi(this);  // Настраиваем интерфейс из файла .ui
}

// Обработчик нажатия кнопки "Создать проект"
void MainWindow::on_create_button_project_clicked()
{
    choose = new Choose();
    choose->show();
    this->hide();
    /*
    canvas = new Canvas();
    canvas->setWindowState(Qt::WindowMaximized);
    //canvas->setFixedSize(1920, 1080);
    canvas->show();
    this->hide();
    */
}

// Обработчик нажатия кнопки "Выбрать проект"
void MainWindow::on_choose_button_project_clicked()
{
    canvas = new Canvas();
    canvas->setWindowState(Qt::WindowMaximized);
    //canvas->setFixedSize(1920, 1080);
    canvas->show();
    canvas->hide();
    canvas->openIm();
    canvas->show();
    this->hide();
}
