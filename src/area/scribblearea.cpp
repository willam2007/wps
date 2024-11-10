#include <QtWidgets>
#include <QDir>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QPrinter>
#include <QPrintDialog>
#endif
#endif

#include "scribblearea.h"

ScribbleArea::ScribbleArea(QWidget *parent)
    : QWidget(parent)
{
    // Roots the widget to the top left even if resized

    // Set defaults for the monitored variables
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


// Save the current image
bool ScribbleArea::saveImage(const QString &fileName, const char *fileFormat)
{
    // Created to hold the image
    QImage visibleImage = image;
    resizeImage(&visibleImage, size());

    if (visibleImage.save(fileName, fileFormat)) {
        modified = false;
        return true;
    } else {
        return false;
    }
}

// Used to change the pen color
void ScribbleArea::setPenColor(const QColor &newColor)
{
    myPenColor = newColor;
}

// Used to change the pen width
void ScribbleArea::setPenWidth(int newWidth)
{
    myPenWidth = newWidth;
}

// Color the image area with white
void ScribbleArea::clearImage()
{
    image.fill(qRgb(255, 55, 255));
    modified = true;
    update();
}

// If a mouse button is pressed check if it was the
// left button and if so store the current position
// Set that we are currently drawing
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

// When the mouse moves if the left button is clicked
// we call the drawline function which draws a line
// from the last position to the current
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

// If the button is released we set variables to stop drawing
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

// QPainter provides functions to draw on the widget
// The QPaintEvent is sent to widgets that need to
// update themselves
void ScribbleArea::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);

    if (currentMode == Selecting && selecting) {
        painter.setPen(QPen(Qt::red, 1, Qt::DashLine));
        painter.drawRect(selectionRect.normalized());
    }
}

// Resize the image to slightly larger then the main window
// to cut down on the need to resize the image
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
    // Used to draw on the widget
    QPainter painter(&image);

    // Set the current settings for the pen
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));

    // Draw a line from the last registered point to the current
    painter.drawLine(lastPoint, endPoint);

    // Set that the image hasn't been saved
    modified = true;

    int rad = (myPenWidth / 2) + 2;

    // Call to update the rectangular space where we drew
    update(QRect(lastPoint, endPoint).normalized()
               .adjusted(-rad, -rad, +rad, +rad));

    // Update the last position where we left off drawing
    lastPoint = endPoint;
}

// When the app is resized create a new image using
// the changes made to the image
void ScribbleArea::resizeImage(QImage *image, const QSize &newSize)
{
    // Check if we need to redraw the image
    if (image->size() == newSize)
        return;

    // Create a new image to display and fill it with white
    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));

    // Draw the image
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

// Print the image
void ScribbleArea::print()
{
    // Check for print dialog availability
#if QT_CONFIG(printdialog)

    // Can be used to print
    QPrinter printer(QPrinter::HighResolution);

    // Open printer dialog and print if asked
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
