#ifndef CANVAS_H
#define CANVAS_H

#include "../area/scribblearea.h"
#include <QMainWindow>

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
    explicit Canvas(QWidget *parent = nullptr);
    ~Canvas();

    void openIm();
    QSize getCanvasSpaceSize() const;
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_open_button_canvas_triggered();


private:
    Ui::Canvas *ui;
    ScribbleArea *scribbleArea;

    bool maybeSave();

    bool saveFile(const QByteArray &fileFormat);


};

#endif // CANVAS_H
