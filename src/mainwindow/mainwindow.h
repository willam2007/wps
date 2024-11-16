#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

// ScribbleArea используется для рисования изображения
class ScribbleArea;
class Canvas;

class MainWindow : public QMainWindow
{
    // Объявляет наш класс как QObject, который является базовым
    // классом для всех объектов Qt
    // QObjects обрабатывают события
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    // События, которые могут быть вызваны
private slots:              // Сохранение
    void penColor();            // Изменение цвета пера
    void penWidth();            // Изменение толщины пера
    void about();               // Отображение информации о программе

    void on_create_button_project_clicked();  // Обработчик нажатия кнопки создания проекта
    void on_choose_button_project_clicked();  // Обработчик нажатия кнопки выбора проекта

private:
    Ui::MainWindow *ui;
    // Поле для рисования
    ScribbleArea *scribbleArea;
    Canvas *canvas;
};

#endif
