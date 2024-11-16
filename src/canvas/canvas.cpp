#include "canvas.h"
#include "ui_canvas.h"
#include "../area/scribblearea.h"

#include <qboxlayout.h>
#include <qpainter.h>
#include <QtWidgets>

Canvas::Canvas(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Canvas)
{
    //setAttribute(Qt::WA_StaticContents); // Устанавливаем статическое содержимое
    ui->setupUi(this); // Настраиваем интерфейс из файла .ui
    scribbleArea = new ScribbleArea(this); // Создаем область для рисования
    QVBoxLayout *layout = new QVBoxLayout(ui->canvas_space); // Устанавливаем вертикальный компоновщик в canvas_space
    layout->addWidget(scribbleArea); // Добавляем область для рисования в компоновщик

    // Задаем стиль для canvas_space
    ui->canvas_space->setStyleSheet("border: 2px solid black; border-radius: 10px; background-color: lightgray;");
}

// Пользователь пытается закрыть приложение
void Canvas::closeEvent(QCloseEvent *event)
{
    // Если maybeSave() возвращает true, то закрываем приложение
    if (maybeSave()) {
        event->accept();
    } else {
        // Если были несохраненные изменения, отменяем закрытие
        event->ignore();
    }
}

// Открывает диалог для изменения цвета пера
void Canvas::penColor()
{
    // Сохраняем выбранный цвет из диалога
    QColor newColor = QColorDialog::getColor(scribbleArea->penColor());

    // Если цвет валиден, устанавливаем его
    if (newColor.isValid())
        scribbleArea->setPenColor(newColor);
}

// Открывает диалог "О программе"
void Canvas::about()
{
    // Заголовок окна и текст для отображения
    QMessageBox::about(this, tr("О WPS"),
                       tr("<p>На этом этапе все делал Артём. Какой он молодец</p>"));
}

// Открывает диалог для изменения толщины пера
void Canvas::penWidth()
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

// Функция для открытия изображения
void Canvas::openIm()
{
    if (maybeSave()) { // Проверяем, нужно ли сохранить изменения
        QDir dir(QDir::current());
        dir.cdUp(); // Переходим на уровень выше
        dir.cdUp(); // Переходим на уровень выше

        // Открываем диалог выбора файла
        QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("Open File"), dir.absolutePath());
        // Если выбрали файл, загружаем его в scribbleArea
        if (!fileName.isEmpty()) {
            QSize canvasSize = getCanvasSpaceSize(); // Получаем размер canvas_space
            scribbleArea->openImage(fileName, canvasSize); // Передаем файл и размер
        }
    }
}

// Проверяем, нужно ли сохранить изменения
bool Canvas::maybeSave()
{
    // Проверяем, были ли изменения
    if (scribbleArea->isModified()) {
        QMessageBox::StandardButton ret;

        // Показываем диалоговое окно с предложением сохранить изменения
        ret = QMessageBox::warning(this, tr("Уверены?"),
                                   tr("Изображение было изменено.\n"
                                      "Хотите сохранить изменения?"),
                                   QMessageBox::Yes | QMessageBox::Cancel
                                       | QMessageBox::No);

        // Если нажали "Сохранить", вызываем сохранение
        if (ret == QMessageBox::Yes) {
            return saveFile("png");
        } else if (ret == QMessageBox::Cancel) {
            // Если нажали "Отмена", не закрываем окно
            return false;
        }
    }
    return true; // Если изменений не было, возвращаем true
}

// Функция для сохранения файла
bool Canvas::saveFile(const QByteArray &fileFormat)
{
    QDir dir(QDir::current());
    dir.cdUp(); // Переходим на уровень выше
    dir.cdUp(); // Переходим на уровень выше
    // Определяем начальный путь и формат файла
    QString initialPath = dir.absolutePath() + "/untitled." + fileFormat;

    // Открываем диалог сохранения файла
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save"),
                                                    initialPath,
                                                    tr("%1 Files (*.%2);;All Files (*)")
                                                        .arg(QString::fromLatin1(fileFormat.toUpper()))
                                                        .arg(QString::fromLatin1(fileFormat)));

    // Если файл не выбран, возвращаем false
    if (fileName.isEmpty()) {
        return false;
    } else {
        // Вызываем сохранение файла
        return scribbleArea->saveImage(fileName, fileFormat.constData());
    }
}