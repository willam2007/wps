#ifndef CANVAS_H
#define CANVAS_H

#include "scribblearea.h"
#include "ui_canvas.h"
#include "mainwindow.h"

#include <QMainWindow>
#include <qpropertyanimation.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class Canvas;
}
QT_END_NAMESPACE

class ScribbleArea;

class Canvas : public QMainWindow
{
    Q_OBJECT

public:
    explicit Canvas(int width = 1920, int height = 1080, QWidget *parent = nullptr);
    ~Canvas() {delete ui;}; // Удаляем интерфейс, чтобы освободить память
    void openIm();
    QSize getCanvasSpaceSize() const {return ui->canvas_space->size();}; // Получаем размер canvas_space
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_open_button_canvas_triggered() {this->openIm();}; // Обработчик нажатия кнопки выбора проекта
    bool on_save_button_canvas_triggered() {return saveFile("png");}; // Обработчик нажатия кнопки сохранения проекта
    void on_actionPen_triggered(); // Обработчик нажатия выбора режима рисования
    void on_actionSelecting_triggered() {scribbleArea->setMode(ScribbleArea::Selecting);}; // Обработчик нажатия выбора режима выбора
    void on_actionAbout_triggered() {this->about();}; // Обработчик нажатия кнопки о нашем WPS
    void on_actionClear_triggered() {scribbleArea->clearImage();}; // Обработчик нажатия очистки холста
    void on_actionNone_triggered(); // Обработчик нажатия выбора режима
    void on_horizontalSlider_valueChanged(int value) {scribbleArea->setPenWidth(value);};
    void on_actionReset_triggered();

private:
    Ui::Canvas *ui;
    ScribbleArea *scribbleArea;
    MainWindow *mainWindow;
    QPropertyAnimation *fadeAnimation;

    bool maybeSave();
    void setupPageTransition(QWidget *nextPage);
    void penWidth();
    void penColor();
    void about();
    bool saveFile(const QByteArray &fileFormat);

};

#endif // CANVAS_H
