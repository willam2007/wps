#ifndef SCRIBBLEAREA_H
#define SCRIBBLEAREA_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>

class ScribbleArea : public QWidget
{
    Q_OBJECT

public:
    enum Mode { Inactive, Drawing, Selecting };

    ScribbleArea(QWidget *parent = nullptr);

    bool openImage(const QString &fileName, const QSize &targetSize);
    bool saveImage(const QString &fileName, const char *fileFormat);
    void setPenColor(const QColor &newColor);
    void setPenWidth(int newWidth);
    // Сохранить выделенную область
    bool saveSelection(const QString &filePath = "ml/selection.png");

    bool isModified() const;
    QColor penColor() const { return myPenColor; }
    int penWidth() const { return myPenWidth; }
    void setMode(Mode newMode);

public slots:
    void clearImage();
    void print();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void drawLineTo(const QPoint &endPoint);
    void resizeImage(QImage *image, const QSize &newSize);

    bool modified;
    bool scribbling;
    bool selecting;
    int myPenWidth;
    QColor myPenColor;
    QImage image;
    QPoint lastPoint;
    QRect selectionRect;

    Mode currentMode; // Режим работы ScribbleArea
};

#endif // SCRIBBLEAREA_H
