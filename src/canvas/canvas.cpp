#include "canvas.h"
#include "ui_canvas.h"
#include "../area/scribblearea.h"
#include "../mainwindow/mainwindow.h"
#include "../other/rainbowlabel.h"

#include <qboxlayout.h>
#include <qpainter.h>
#include <QtWidgets>
#include <QDebug>

Canvas::Canvas(int width, int height, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Canvas)
    , fadeAnimation(nullptr)
{
    // Set initial opacity to 0
    setWindowOpacity(0.0);
    
    //setAttribute(Qt::WA_StaticContents); // Устанавливаем статическое содержимое
    ui->setupUi(this); // Настраиваем интерфейс из файла .ui
    RainbowLabel *rainbowLabel = findChild<RainbowLabel*>("WPSLabel");
    if (rainbowLabel) {
        rainbowLabel->setText("Ваш WPS");
        rainbowLabel->setAlignment(Qt::AlignCenter);
        rainbowLabel->setFont(QFont("Segoe UI", 32, QFont::Bold));
    }
    ui->canvas_pages->setCurrentWidget(ui->inactive_page);
    // Минималистичный современный стиль для окна и элементов
    QString style = "QMainWindow { background-color:rgb(36, 36, 36); } "
                    "QLabel { color: #f7f7fa; font-size: 20px; font-weight: 500; letter-spacing: 0.5px; } "
                    "QPushButton { background-color: #eebbc3; color:rgb(26, 25, 25); border-radius: 14px; padding: 4px 12px; font-size: 16px; font-weight: 500; box-shadow: 0 2px 12px rgba(180,193,236,0.10); border: none; transition: background 0.2s, color 0.2s; } "
                    "QPushButton:hover { background-color:rgb(237, 148, 161); color: #232946; } "
                    "QPushButton:pressed { background-color:rgb(241, 118, 136); color:rgb(26, 25, 25); } "
                    "QMessageBox { background-color: rgb(36, 36, 36); color: #f7f7fa; font-size: 18px; } "
                    "QMessageBox QLabel { color: #f7f7fa; font-size: 20px; font-weight: 500; letter-spacing: 0.5px; } "
                    "QMessageBox QPushButton { background-color: #eebbc3; color: #232946; border-radius: 10px; padding: 4px 16px; font-size: 16px; } ";
    this->setStyleSheet(style);
    // Стилизация canvas_space и frame
    ui->canvas_space->setStyleSheet("#canvas_space { background-color:rgb(159, 160, 161); }");
    ui->frame_2->setStyleSheet("#frame_2 { border: 2px solid #eebbc3; border-radius: 15px; background: rgb(36, 36, 36);  }");
    ui->frame->setStyleSheet("#frame { border: 2px solid #eebbc3; border-radius: 15px; background: rgb(36, 36, 36); padding: 10px; margin: 5px; }");
    ui->canvas_pages->setStyleSheet(
        "QStackedWidget#canvas_pages { background: rgb(36, 36, 36); } "
        "QWidget#pen_page, QWidget#selecting_page, QWidget#text_page { border: 2px solid #eebbc3; border-radius: 15px; padding: 10px; margin: 5px; } "
        "QLabel { color: #f7f7fa; font-size: 16px; font-weight: 500; letter-spacing: 0.5px; } "
        "QSlider::groove:horizontal { border: 1px solid #bdc3c7; height: 8px; background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #dfe6e9, stop:1 #b2bec3); margin: 2px 0; border-radius: 4px; } "
        "QSlider::handle:horizontal { background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #2980b9, stop:1 #3498db); border: 1px solid #2980b9; width: 18px; margin: -5px 0; border-radius: 9px; } "
    );
    // Create window fade-in animation
    QPropertyAnimation* windowFadeIn = new QPropertyAnimation(this, "windowOpacity");
    windowFadeIn->setDuration(600);
    windowFadeIn->setStartValue(0.0);
    windowFadeIn->setEndValue(1.0);
    windowFadeIn->start(QPropertyAnimation::DeleteWhenStopped);
    scribbleArea = new ScribbleArea(this); // Создаем область для рисования
    QVBoxLayout *layout = new QVBoxLayout(ui->canvas_space); // Устанавливаем вертикальный компоновщик в canvas_space
    layout->addWidget(scribbleArea); // Добавляем область для рисования в компоновщик

    // Connect color button to penColor slot
    connect(ui->colorButton, &QPushButton::clicked, this, &Canvas::penColor);
    
    // Connect text color and font buttons to their slots
    connect(ui->textColorButton, &QPushButton::clicked, this, &Canvas::textColor);
    connect(ui->fontButton, &QPushButton::clicked, this, &Canvas::textFont);





    //ui->canvas_space->setFixedSize(width, height);
    ui->canvas_space->setFixedSize(1780, 1080);




    // Set up fade effect for page transitions
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(ui->canvas_pages);
    ui->canvas_pages->setGraphicsEffect(effect);
    effect->setOpacity(1.0);
    // Подключаем кнопки инструментов из панели frame
    connect(ui->penButton, &QPushButton::clicked, this, &Canvas::on_actionPen_triggered);
    connect(ui->selectingButton, &QPushButton::clicked, this, &Canvas::on_actionSelecting_triggered);
    connect(ui->textButton, &QPushButton::clicked, this, &Canvas::on_actionText_triggered);
    connect(ui->clearButton, &QPushButton::clicked, this, &Canvas::on_actionClear_triggered);
    connect(ui->resetButton, &QPushButton::clicked, this, &Canvas::on_actionReset_triggered);
    connect(ui->noneButton, &QPushButton::clicked, this, &Canvas::on_actionNone_triggered);
    connect(ui->openButton, &QPushButton::clicked, this, &Canvas::openIm);
    connect(ui->saveButton, &QPushButton::clicked, [this]() { saveFile("png"); });
    connect(ui->aboutButton, &QPushButton::clicked, this, &Canvas::about);
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

// Функция для открытия изображения
void Canvas::openIm()
{
    if (maybeSave()) { // Проверяем, нужно ли сохранить изменения
        QDir dir(QDir::current());
        dir.cdUp(); // Переходим на уровень выше
        dir.cdUp(); // Переходим на уровень выше

        // Открываем диалог выбора файла
        QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("Открыть проект"), dir.absolutePath());
        // Если выбрали файл, загружаем его в scribbleArea
        if (!fileName.isEmpty()) {
            QSize canvasSize = getCanvasSpaceSize(); // Получаем размер canvas_space
            scribbleArea->openImage(fileName, canvasSize); // Передаем файл и размер
            this->show();
        } else {
            MainWindow *mainWindow = new MainWindow();
            mainWindow->show();
            this->close();
        } 
    }
}

// Проверяем, нужно ли сохранить изменения
bool Canvas::maybeSave()
{
    // Проверяем, были ли изменения
    if (scribbleArea->isModified()) {
        QMessageBox msgBox(this);
        msgBox.setWindowTitle(tr("Уверены?"));
        msgBox.setText(tr("Изображение было изменено.\nХотите сохранить изменения?"));
        QPushButton *yesButton = msgBox.addButton(tr("Да"), QMessageBox::YesRole);
        QPushButton *noButton = msgBox.addButton(tr("Нет"), QMessageBox::NoRole);
        QPushButton *cancelButton = msgBox.addButton(tr("Отмена"), QMessageBox::RejectRole);
        msgBox.setDefaultButton(yesButton);
        msgBox.exec();
        if (msgBox.clickedButton() == yesButton) {
            return saveFile("png");
        } else if (msgBox.clickedButton() == cancelButton) {
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

void Canvas::setupPageTransition(QWidget *nextPage) {
    // Clean up previous animation and its connections
    if (fadeAnimation) {
        fadeAnimation->stop();
        disconnect(fadeAnimation, nullptr, nullptr, nullptr);
        delete fadeAnimation;
        fadeAnimation = nullptr;
    }

    // Create and configure opacity effect if it doesn't exist
    QGraphicsOpacityEffect *effect = qobject_cast<QGraphicsOpacityEffect*>(ui->canvas_pages->graphicsEffect());
    if (!effect) {
        effect = new QGraphicsOpacityEffect(ui->canvas_pages);
        ui->canvas_pages->setGraphicsEffect(effect);
    }

    // Create new fade-out animation
    fadeAnimation = new QPropertyAnimation(effect, "opacity");
    fadeAnimation->setDuration(400); // Reduced duration for smoother transition
    fadeAnimation->setStartValue(1.0);
    fadeAnimation->setEndValue(0.0);

    // Connect only once and handle both fade-out and fade-in
    connect(fadeAnimation, &QPropertyAnimation::finished, this, [this, nextPage]() {
        if (fadeAnimation->direction() == QPropertyAnimation::Forward) {
            // Fade-out finished, switch page and start fade-in
            ui->canvas_pages->setCurrentWidget(nextPage);
            fadeAnimation->setDirection(QPropertyAnimation::Backward);
            fadeAnimation->start();
        } else {
            // Fade-in finished, clean up
            disconnect(fadeAnimation, nullptr, nullptr, nullptr);
            delete fadeAnimation;
            fadeAnimation = nullptr;
        }
    });

    // Start the fade-out animation
    fadeAnimation->setDirection(QPropertyAnimation::Forward);
    fadeAnimation->start();
}

void Canvas::on_actionPen_triggered()
{
    // Устанавливаем режим рисования для ScribbleArea
    scribbleArea->setMode(ScribbleArea::Drawing);

    // Анимируем переход на страницу pen_page
    setupPageTransition(ui->pen_page);
}

void Canvas::on_actionNone_triggered()
{
    scribbleArea->setMode(ScribbleArea::Inactive); // Обработчик нажатия выбора режима
    setupPageTransition(ui->inactive_page);
}

void Canvas::on_actionReset_triggered()
{
    // Сбрасываем масштаб к исходному значению (1.0) и центрируем изображение
    scribbleArea->setZoomFactor(1.0);
    scribbleArea->resetViewport();
    update();
}

void Canvas::on_actionSelecting_triggered()
{
    // Устанавливаем режим выделения для ScribbleArea
    scribbleArea->setMode(ScribbleArea::Selecting);
    setupPageTransition(ui->selecting_page);
}

void Canvas::on_actionText_triggered()
{
    // Устанавливаем режим текста для ScribbleArea
    scribbleArea->setMode(ScribbleArea::Text);
    setupPageTransition(ui->text_page);
}

// Открывает диалог для изменения цвета текста
void Canvas::textColor()
{
    // Сохраняем выбранный цвет из диалога
    QColor newColor = QColorDialog::getColor(scribbleArea->getTextColor());

    // Если цвет валиден, устанавливаем его
    if (newColor.isValid())
        scribbleArea->setTextColor(newColor);
}

// Открывает диалог для изменения шрифта текста
void Canvas::textFont()
{
    bool ok;
    QFont newFont = QFontDialog::getFont(&ok, scribbleArea->getTextFont(), this, tr("Выбор шрифта"));
    
    if (ok) {
        scribbleArea->setTextFont(newFont);
    }
}