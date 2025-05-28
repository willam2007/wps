#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "../canvas/canvas.h"
#include "../choose/choose.h"
#include "../other/rainbowlabel.h"

#include <QtWidgets>
#include <QDebug>

// Конструктор MainWindow
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)  // Инициализируем объект Ui::MainWindow
{
    setAttribute(Qt::WA_StaticContents); // Устанавливаем атрибут статического содержимого
    ui->setupUi(this);  // Настраиваем интерфейс из файла .ui
    // Минималистичный современный стиль для окна и элементов
    QString style = "QMainWindow { background-color:rgb(36, 36, 36); } "
                    "QFrame { background-color: transparent; border: none; } "
                    "QLabel { color: #f7f7fa; font-size: 25px; font-weight: 500; letter-spacing: 0.5px; } "
                    "QPushButton { background-color: #eebbc3; color:rgb(26, 25, 25); border-radius: 16px; padding: 10px 32px; font-size: 17px; font-weight: 500; box-shadow: 0 2px 12px rgba(180,193,236,0.10); border: none; transition: background 0.2s, color 0.2s; } "
                    "QPushButton:hover { background-color:rgb(237, 148, 161); color: #232946; } "
                    "QPushButton:pressed { background-color:rgb(241, 118, 136); color:rgb(26, 25, 25); } ";
    this->setStyleSheet(style);
    this->setFixedSize(382,195);

    // Заменяем QLabel на RainbowLabel для анимации текста
    RainbowLabel *rainbowLabel = new RainbowLabel(this);
    rainbowLabel->setText("Ваш WPS");
    rainbowLabel->setAlignment(Qt::AlignCenter);
    rainbowLabel->setGeometry(0, 40, 382, 40);
    rainbowLabel->setFont(QFont("Segoe UI", 40, QFont::Bold));
    rainbowLabel->show();
}

// Обработчик нажатия кнопки "Создать проект"
void MainWindow::on_create_button_project_clicked()
{
    choose = new Choose();
    choose->show();
    this->hide();
}

// Обработчик нажатия кнопки "Выбрать проект"
void MainWindow::on_choose_button_project_clicked()
{
    canvas = new Canvas(1920, 1080);
    canvas->setWindowState(Qt::WindowMaximized);
    //canvas->setFixedSize(1920, 1080);
    canvas->show();
    canvas->hide();
    canvas->openIm();
    this->hide();
}
