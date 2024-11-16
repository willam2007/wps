#include <QtWidgets>
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "../area/scribblearea.h"
#include "../canvas/canvas.h"
#include <QDebug>

// Конструктор MainWindow
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)  // Инициализируем объект Ui::MainWindow
{
    setAttribute(Qt::WA_StaticContents); // Устанавливаем атрибут статического содержимого
    ui->setupUi(this);  // Настраиваем интерфейс из файла .ui
}

MainWindow::~MainWindow()
{
    delete ui; // Удаляем интерфейс, чтобы освободить память
}

// Открывает диалог для изменения цвета пера
void MainWindow::penColor()
{
    // Сохраняем выбранный цвет из диалога
    QColor newColor = QColorDialog::getColor(scribbleArea->penColor());

    // Если цвет валиден, устанавливаем его
    if (newColor.isValid())
        scribbleArea->setPenColor(newColor);
}

// Открывает диалог для изменения толщины пера
void MainWindow::penWidth()
{
    bool ok; // Переменная для проверки, нажата ли кнопка OK

    // Создаем диалог выбора толщины пера
    int newWidth = QInputDialog::getInt(this, tr("Scribble"),
                                        tr("Выберите толщину пера:"),
                                        scribbleArea->penWidth(),
                                        1, 50, 1, &ok);

    // Устанавливаем толщину пера, если OK нажата
    if (ok)
        scribbleArea->setPenWidth(newWidth);
}

// Открывает диалог "О программе"
void MainWindow::about()
{
    // Заголовок окна и текст для отображения
    QMessageBox::about(this, tr("О Scribble"),
                       tr("<p>Пример <b>Scribble</b> великолепен</p>"));
}

// Обработчик нажатия кнопки "Создать проект"
void MainWindow::on_create_button_project_clicked()
{
    canvas = new Canvas();
    canvas->setWindowState(Qt::WindowMaximized);
    canvas->setFixedSize(1920, 1080);
    canvas->show();
    this->hide();   
}

// Обработчик нажатия кнопки "Выбрать проект"
void MainWindow::on_choose_button_project_clicked()
{
    canvas = new Canvas();
    canvas->openIm();
    canvas->setWindowState(Qt::WindowMaximized);
    canvas->setFixedSize(1920, 1080); 
    canvas->show();
    this->hide();
}
