#include "choose.h"
#include "../canvas/canvas.h"
#include "../other/rainbowlabel.h"
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
    this->setFixedSize(size()); // Фиксируем текущий размер окна
    // Применяем современный минималистичный стиль
    setStyleSheet("QMainWindow { background: rgb(36, 36, 36); }\n"
                  "QPushButton { background-color: #eebbc3; color:rgb(26, 25, 25); border-radius: 12px; padding: 10px 28px; font-size: 14px; font-weight: 500; box-shadow: 0 2px 12px rgba(180,193,236,0.10); border: none; transition: background 0.2s, color 0.2s; } \n"
                  "QPushButton:hover { background-color:rgb(237, 148, 161); color: #232946; }\n"
                  "QPushButton:pressed { background-color:rgb(241, 118, 136); color:rgb(26, 25, 25); }\n"
                  "QLabel { color: #f7f7fa; font-size: 18px; font-weight: 500; letter-spacing: 0.5px; } \n"
                  "QSpinBox { background-color: #eebbc3; color:rgb(26, 25, 25); border-radius: 16px; padding: 10px 18px; font-size: 14px; font-weight: 500; box-shadow: 0 2px 12px rgba(180,193,236,0.10); border: none; transition: background 0.2s, color 0.2s; }\n"
                  "QSpinBox::up-arrow { color: #f7f7fa; }\n"
                  "QSpinBox::down-arrow { color: #f7f7fa; }\n"
                  "QSpinBox::up-button, QSpinBox::down-button { width: 24px; height: 24px; }\n"
                  "QGroupBox { border: 1px solid #444; border-radius: 12px; margin-top: 10px; color: #fff; font-size: 16px; }\n"
                  "QGroupBox:title { subcontrol-origin: margin; left: 10px; padding: 0 3px 0 3px; }\n");

    // Заменяем QLabel на RainbowLabel для анимации текста
    RainbowLabel *rainbowLabel = new RainbowLabel(this);
    rainbowLabel->setText("Ваш WPS");
    rainbowLabel->setAlignment(Qt::AlignCenter);
    rainbowLabel->setGeometry(0, 15, 382, 40);
    rainbowLabel->setFont(QFont("Segoe UI", 55, QFont::Bold));
    rainbowLabel->show();
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
    int width = ui->spinBox_width->value();
    int height = ui->spinBox_height->value();
    canvas = new Canvas(width, height);
    canvas->setWindowState(Qt::WindowMaximized);
    //canvas->setFixedSize(1920, 1080);
    canvas->show();
    this->hide();
}


void Choose::on_pushButton_back_clicked()
{
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
    this->close();
}
