#include "choose.h"
#include "ui_choose.h"

#include <qboxlayout.h>
#include <qpainter.h>
#include <QtWidgets>
#include <QDebug>

Choose::Choose(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Choose)
{
    ui->setupUi(this); // Настраиваем интерфейс из файла .ui
    setFixedSize(size()); // Фиксируем текущий размер окна
    // Create window fade-in animation
}

void Choose::on_pushButton_1920_1080_clicked()
{
    ui->spinBox_width->setValue(1920);
    ui->spinBox_height->setValue(1080);
}


void Choose::on_pushButton_1280_720_clicked()
{
    ui->spinBox_width->setValue(1280);
    ui->spinBox_height->setValue(720);
}


void Choose::on_pushButton__1080_1080_clicked()
{
    ui->spinBox_width->setValue(1080);
    ui->spinBox_height->setValue(1080);
}


void Choose::on_pushButton_random_clicked()
{
    // Генерируем случайные значения в пределах допустимых значений spinBox
    int randomWidth = QRandomGenerator::global()->bounded(ui->spinBox_width->minimum(), ui->spinBox_width->maximum() + 1);
    int randomHeight = QRandomGenerator::global()->bounded(ui->spinBox_height->minimum(), ui->spinBox_height->maximum() + 1);
    
    ui->spinBox_width->setValue(randomWidth);
    ui->spinBox_height->setValue(randomHeight);
}


void Choose::on_pushButton_create_clicked()
{

}


void Choose::on_pushButton_back_clicked()
{
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
    this->close();
}

