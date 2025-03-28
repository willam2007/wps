#ifndef SCRIBBLEAREA_H
#define SCRIBBLEAREA_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QBuffer>

// Класс ScribbleArea - область для рисования и выделения
class ScribbleArea : public QWidget
{
    Q_OBJECT

public:
    // Определяем режимы работы ScribbleArea
    enum Mode { Inactive, Drawing, Selecting };

    ScribbleArea(QWidget *parent = nullptr);

    // Открыть изображение с изменением размера под заданный размер
    bool openImage(const QString &fileName, const QSize &targetSize);
    // Сохранить текущее изображение в файл
    bool saveImage(const QString &fileName, const char *fileFormat);
    // Установить цвет пера
    void setPenColor(const QColor &newColor);
    // Установить ширину пера
    void setPenWidth(int newWidth);
    // Сохранить выделенную область в файл
    bool saveSelection(const QString &filePath = "ml/selection.png");

    // Проверка на наличие изменений
    bool isModified() const;
    // Получить текущий цвет пера
    QColor penColor() const { return myPenColor; }
    // Получить текущую ширину пера
    int penWidth() const { return myPenWidth; }
    // Установить режим работы (рисование, выделение и т.д.)
    void setMode(Mode newMode);

public slots:
    // Очистить изображение
    void clearImage();
    // Напечатать изображение
    void print();

protected:
    // Обработка нажатия кнопки мыши
    void mousePressEvent(QMouseEvent *event) override;
    // Обработка движения мыши
    void mouseMoveEvent(QMouseEvent *event) override;
    // Обработка отпускания кнопки мыши
    void mouseReleaseEvent(QMouseEvent *event) override;
    // Перерисовка изображения
    void paintEvent(QPaintEvent *event) override;
    // Обработка изменения размера виджета
    void resizeEvent(QResizeEvent *event) override;

private:
    // Нарисовать линию до указанной точки
    void drawLineTo(const QPoint &endPoint);
    // Изменить размер изображения
    void resizeImage(QImage *image, const QSize &newSize);

    bool modified;          // Флаг изменений
    bool scribbling;        // Флаг режима рисования
    bool selecting;         // Флаг режима выделения
    int myPenWidth;         // Ширина пера
    QColor myPenColor;      // Цвет пера
    QImage image;           // Изображение для рисования
    QPoint lastPoint;       // Последняя точка рисования
    QRect selectionRect;    // Прямоугольник выделенной области
    Mode currentMode;       // Текущий режим работы ScribbleArea
    QNetworkAccessManager *networkManager; // Менеджер сетевых запросов

};

#endif // SCRIBBLEAREA_H
