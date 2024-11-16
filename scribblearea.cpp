#include "scribblearea.h"

#include <QtWidgets>
#include <QDir>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QPrinter>
#include <QPrintDialog>
#endif
#endif

ScribbleArea::ScribbleArea(QWidget *parent)
    : QWidget(parent)
{
    // Устанавливаем значения по умолчанию для отслеживаемых переменных
    modified = false;
    scribbling = false;
    selecting = false;
    myPenWidth = 1;
    myPenColor = Qt::blue;
    currentMode = Inactive;
}

void ScribbleArea::setMode(Mode newMode) {
    currentMode = newMode;
    update();
}

bool ScribbleArea::openImage(const QString &fileName, const QSize &targetSize)
{
    QImage loadedImage;
    if (!loadedImage.load(fileName))
        return false;

    // Изменение размера загруженного изображения
    loadedImage = loadedImage.scaled(targetSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    image = loadedImage;
    modified = false;
    update();
    return true;
}


// Сохранение текущего изображения
bool ScribbleArea::saveImage(const QString &fileName, const char *fileFormat)
{
    // Создаем изображение для сохранения
    QImage visibleImage = image;
    resizeImage(&visibleImage, size());

    if (visibleImage.save(fileName, fileFormat)) {
        modified = false;
        return true;
    } else {
        return false;
    }
}

// Изменение цвета пера
void ScribbleArea::setPenColor(const QColor &newColor)
{
    myPenColor = newColor;
}

// Изменение ширины пера
void ScribbleArea::setPenWidth(int newWidth)
{
    myPenWidth = newWidth;
}

// Заливка изображения белым цветом
void ScribbleArea::clearImage()
{
    image.fill(qRgb(255, 55, 255));
    modified = true;
    update();
}

// При нажатии кнопки мыши проверяем, была ли нажата левая кнопка,
// и если да, сохраняем текущую позицию и начинаем рисование
void ScribbleArea::mousePressEvent(QMouseEvent *event) {
    if (currentMode == Inactive) {
        return;
    }

    if (event->button() == Qt::LeftButton) {
        if (currentMode == Drawing) {
            lastPoint = event->pos();
            scribbling = true;
        } else if (currentMode == Selecting) {
            selectionRect.setTopLeft(event->pos());
            selecting = true;
        }
    }
}

// При движении мыши с нажатой левой кнопкой вызываем функцию рисования,
// которая рисует линию от последней позиции до текущей
void ScribbleArea::mouseMoveEvent(QMouseEvent *event) {
    if ((event->buttons() & Qt::LeftButton)) {
        if (currentMode == Drawing && scribbling) {
            drawLineTo(event->pos());
        } else if (currentMode == Selecting && selecting) {
            selectionRect.setBottomRight(event->pos());
            update();
        }
    }
}

// При отпускании кнопки мыши прекращаем рисование
void ScribbleArea::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        if (currentMode == Drawing && scribbling) {
            drawLineTo(event->pos());
            scribbling = false;
        } else if (currentMode == Selecting && selecting) {
            selectionRect.setBottomRight(event->pos());
            selecting = false;
            update();
            // Сохраняем выделенную область
            saveSelection();
        }
    }
}

bool ScribbleArea::isModified() const
{
    return modified;
}

// QPainter предоставляет функции для рисования на виджете
// Событие QPaintEvent отправляется виджетам, которым нужно обновиться
void ScribbleArea::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);

    if (currentMode == Selecting && selecting) {
        painter.setPen(QPen(Qt::red, 1, Qt::DashLine));
        painter.drawRect(selectionRect.normalized());
    }
}

void ScribbleArea::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

void ScribbleArea::drawLineTo(const QPoint &endPoint)
{
    // Функция для рисования на виджете
    QPainter painter(&image);

    // Устанавливаем текущие настройки для пера
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));

    // Рисуем линию от последней зафиксированной точки до текущей
    painter.drawLine(lastPoint, endPoint);

    // Отмечаем, что изображение не сохранено
    modified = true;

    int rad = (myPenWidth / 2) + 2;

    // Вызываем обновление прямоугольной области, где был нарисован отрезок
    update(QRect(lastPoint, endPoint).normalized()
               .adjusted(-rad, -rad, +rad, +rad));

    // Обновляем последнюю точку рисования
    lastPoint = endPoint;
}

// При изменении размера приложения создаем новое изображение
// с изменениями, сделанными в изображении
void ScribbleArea::resizeImage(QImage *image, const QSize &newSize)
{

    // Проверяем, нужно ли перерисовывать изображение
    if (image->size() == newSize)
        return;

    // Создаем новое изображение и заполняем его белым цветом
    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));

    // Рисуем изображение
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

bool ScribbleArea::saveSelection(const QString &filePath) {
    // Извлекаем область из изображения
    QImage croppedImage = image.copy(selectionRect);

    // Проверяем, существует ли папка "ml", если нет - создаем её
    QDir dir;
    if (!dir.exists("../../ml")) {
        dir.mkpath("../../ml");
    }

    // Сохраняем выделенную область
    return croppedImage.save("../../ml/" + QFileInfo(filePath).fileName());
}

// Печать изображения
void ScribbleArea::print()
{
    // Проверяем наличие диалога печати
#if QT_CONFIG(printdialog)

    // Создаем объект для печати
    QPrinter printer(QPrinter::HighResolution);

    // Открываем диалог печати и печатаем, если пользователь согласен
    QPrintDialog printDialog(&printer, this);
    if (printDialog.exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = image.size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(image.rect());
        painter.drawImage(0, 0, image);
    }
#endif // QT_CONFIG(printdialog)
}
