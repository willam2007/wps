#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    isOriginalText = true;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{
    if (isOriginalText) {
        ui->label->setText("Сделано Артемом");
    } else {
        ui->label->setText("Привет, это наш редактор wps");
    }
    isOriginalText = !isOriginalText;  // Переключаем состояние
}
