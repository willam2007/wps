#include "scribblearea.h"

#include <QtWidgets>
#include <QDebug>
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
        
    // Инициализируем сетевой менеджер
    networkManager = new QNetworkAccessManager(this);
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
    image.fill(qRgb(255, 255, 255));
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
            // Передаем текущую позицию мыши с учетом смещения viewport
            QPoint adjustedPos = event->pos();
            drawLineTo(adjustedPos);
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
            update();

            // Цикл для повторного показа окна, если текст пустой
            while (true) {
                QInputDialog inputDialog;
                inputDialog.setWindowTitle(tr("Введите текст"));
                inputDialog.setLabelText(tr("Введите текст для отпрвки:"));
                inputDialog.setInputMode(QInputDialog::TextInput);
                inputDialog.setTextValue(""); // Пустое значение по умолчанию

                // Устанавливаем стиль
                inputDialog.setStyleSheet(R"(
                    QDialog {
                        background: rgb(36, 36, 36);
                        border: 2px solid #eebbc3;
                        border-radius: 15px;
                    }
                     QLabel { color: #f7f7fa; font-size: 20px; font-weight: 500; letter-spacing: 0.5px; }
                    QPushButton { background-color: #eebbc3; color:rgb(26, 25, 25); border-radius: 14px; padding: 4px 12px; font-size: 16px; font-weight: 500; box-shadow: 0 2px 12px rgba(180,193,236,0.10); border: none; transition: background 0.2s, color 0.2s; }
                    QPushButton:hover { background-color:rgb(237, 148, 161); color: #232946; }
                    QPushButton:pressed { background-color:rgb(241, 118, 136); color:rgb(26, 25, 25); }
                    QLabel { color: #f7f7fa; font-size: 20px; font-weight: 500; letter-spacing: 0.5px; }
                    QPushButton { background-color: #eebbc3; color: #232946; border-radius: 10px; padding: 4px 16px; font-size: 16px; }
                )");

                // Обрабатываем результат
                if (inputDialog.exec() == QDialog::Accepted) {
                    QString userText = inputDialog.textValue();
                    if (!userText.isEmpty()) {
                        // Сохраняем текст в файл
                        QFile file("../ml/user_text.txt");
                        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                            QTextStream out(&file);
                            out << userText << "\n"; // Перезаписываем файл новым текстом
                            file.close();
                        }

                        // Сохраняем выделенную область
                        saveSelection();

                        // Завершаем цикл, если текст введён
                        break;
                    } else {
                        QMessageBox::warning(nullptr, tr("Ошибка"), tr("Текст не может быть пустым!"));
                    }
                } else {
                    // Пользователь отменил ввод
                    break;
                }
            }

            selecting = false;
            update();
        }
    }
}

bool ScribbleArea::isModified() const
{
    return modified;
}

// QPainter предоставляет функции для рисования на виджете
// Событие QPaintEvent отправляется виджетам, которым нужно обновиться
void ScribbleArea::setZoomFactor(double factor) {
    m_zoomFactor = factor;
    update();
}

void ScribbleArea::resetViewport() {
    // Вычисляем размеры изображения с учетом масштаба
    QSizeF imageSize = image.size() * m_zoomFactor;
    QSizeF viewportSize = size();
    
    // Центрируем изображение
    viewportOffset.setX((imageSize.width() - viewportSize.width()) / 2);
    viewportOffset.setY((imageSize.height() - viewportSize.height()) / 2);
    
    update();
}

void ScribbleArea::wheelEvent(QWheelEvent *event) {
    // Сохраняем позицию курсора до масштабирования
    QPointF oldPos = event->position();
    QPointF scenePos = (oldPos + viewportOffset) / m_zoomFactor;
    
    // Изменяем масштаб
    double oldZoom = m_zoomFactor;
    if (event->angleDelta().y() > 0) {
        setZoomFactor(qMin(m_zoomFactor * 1.1, 1.1)); // Ограничиваем максимальный масштаб
    } else {
        setZoomFactor(qMax(m_zoomFactor / 1.1, 0.7)); // Ограничиваем минимальный масштаб
    }
    
    // Вычисляем новое смещение, чтобы сохранить позицию под курсором
    QPointF newPos = scenePos * m_zoomFactor - oldPos;
    viewportOffset = newPos;
    
    // Ограничиваем смещение, чтобы изображение не уходило за пределы видимой области
    QSizeF imageSize = image.size() * m_zoomFactor;
    QSizeF viewportSize = size();
    
    // Ограничиваем смещение по X
    if (imageSize.width() <= viewportSize.width()) {
        // Если изображение меньше viewport, центрируем его
        viewportOffset.setX((imageSize.width() - viewportSize.width()) / 2);
    } else {
        // Иначе ограничиваем смещение
        viewportOffset.setX(qBound(viewportSize.width() - imageSize.width(), viewportOffset.x(), 0.0));
    }
    
    // Ограничиваем смещение по Y
    if (imageSize.height() <= viewportSize.height()) {
        // Если изображение меньше viewport, центрируем его
        viewportOffset.setY((imageSize.height() - viewportSize.height()) / 2);
    } else {
        // Иначе ограничиваем смещение
        viewportOffset.setY(qBound(viewportSize.height() - imageSize.height(), viewportOffset.y(), 0.0));
    }
}

void ScribbleArea::resizeEvent(QResizeEvent *event) {
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

    // Применяем масштабирование и учитываем смещение viewport
    QPoint scaledLastPoint = ((lastPoint + viewportOffset) / m_zoomFactor).toPoint();
    QPoint scaledEndPoint = ((endPoint + viewportOffset) / m_zoomFactor).toPoint();

    // Рисуем линию от последней зафиксированной точки до текущей
    painter.drawLine(scaledLastPoint, scaledEndPoint);

    // Отмечаем, что изображение не сохранено
    modified = true;

    // Вычисляем радиус обновления с учетом масштаба
    int rad = (myPenWidth / m_zoomFactor / 2) + 2;

    // Создаем прямоугольник обновления в координатах исходного изображения
    QRect updateRect = QRect(scaledLastPoint, scaledEndPoint).normalized()
                           .adjusted(-rad, -rad, +rad, +rad);

    // Преобразуем прямоугольник обновления в экранные координаты
    QRect screenUpdateRect = QRect(
        (updateRect.topLeft() * m_zoomFactor - viewportOffset).toPoint(),
        (updateRect.bottomRight() * m_zoomFactor - viewportOffset).toPoint()
    ).normalized();

    // Обновляем область экрана
    update(screenUpdateRect);

    // Обновляем последнюю точку рисования
    lastPoint = endPoint;
}

void ScribbleArea::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    
    // Сохраняем текущее состояние painter
    painter.save();
    
    // Применяем смещение и масштабирование
    painter.translate(-viewportOffset);
    painter.scale(m_zoomFactor, m_zoomFactor);
    
    // Рисуем все изображение
    painter.drawImage(0, 0, image);
    
    // Восстанавливаем состояние painter
    painter.restore();
    
    // Если есть выделение, рисуем его с учетом масштаба
    if (currentMode == Selecting && selecting) {
        painter.setPen(QPen(Qt::red, 1, Qt::DashLine));
        painter.drawRect(selectionRect.normalized());
    }
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
    qDebug() << "Начало функции saveSelection";
    
    // Читаем текст промпта из файла
    QString prompt;
    QFile promptFile("../ml/user_text.txt");
    if (promptFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&promptFile);
        prompt = in.readLine();
        promptFile.close();
        qDebug() << "Прочитан текст промпта:" << prompt;
    } else {
        qDebug() << "Ошибка при открытии файла с текстом";
    }

    // Формируем JSON для запроса
    QJsonObject requestData;
    requestData["prompt"] = prompt;
    requestData["size"] = QString("%1x%2").arg(selectionRect.width()).arg(selectionRect.height());

    QJsonDocument doc(requestData);
    QByteArray jsonData = doc.toJson();

    // Создаем POST запрос
    QNetworkRequest request(QUrl("http://77.34.3.142:5000/generate"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    qDebug() << "Отправляем POST запрос на сервер";
    qDebug() << "JSON данные:" << QString(jsonData);
    
    // Отправляем запрос
    QNetworkReply *reply = networkManager->post(request, jsonData);

    // Подключаем обработчик завершения запроса
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "Успешно получен ответ от сервера";
            // Получаем ответ
            QByteArray responseData = reply->readAll();
            qDebug() << "Ответ сервера:" << QString(responseData);
            
            QJsonDocument response = QJsonDocument::fromJson(responseData);
            QJsonObject jsonResponse = response.object();

            // Декодируем base64 в изображение
            QByteArray imageData = QByteArray::fromBase64(jsonResponse["image"].toString().toLatin1());
            QImage generatedImage;
            generatedImage.loadFromData(imageData);

            // Отображаем изображение в выделенной области
            QPainter painter(&image);
            painter.drawImage(selectionRect, generatedImage);
            update();
        } else {
            QString errorString = reply->errorString();
            qDebug() << "Ошибка при получении ответа:" << errorString;
            QMessageBox::warning(this, tr("Ошибка"), tr("Не удалось получить изображение с сервера: %1").arg(errorString));
        }
        reply->deleteLater();
    });

    return true;
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