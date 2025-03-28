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
            update();

            // Цикл для повторного показа окна, если текст пустой
            while (true) {
                QInputDialog inputDialog;
                inputDialog.setWindowTitle(tr("Введите текст"));
                inputDialog.setLabelText(tr("Введите текст для сохранения:"));
                inputDialog.setInputMode(QInputDialog::TextInput);
                inputDialog.setTextValue(""); // Пустое значение по умолчанию

                // Устанавливаем стиль
                inputDialog.setStyleSheet(R"(
                    QDialog {
                        background-color: #f0f0f0;
                        border: 2px solid #5a5a5a;
                        border-radius: 10px;
                    }
                    QLabel {
                        font-size: 14px;
                        color: #333333;
                    }
                    QLineEdit {
                        background-color: #ffffff;
                        border: 1px solid #cccccc;
                        border-radius: 5px;
                        padding: 5px;
                        font-size: 14px;
                    }
                    QPushButton {
                        background-color: #4CAF50;
                        border: none;
                        color: white;
                        padding: 10px 20px;
                        text-align: center;
                        text-decoration: none;
                        display: inline-block;
                        font-size: 14px;
                        margin: 4px 2px;
                        cursor: pointer;
                        border-radius: 5px;
                    }
                    QPushButton:hover {
                        background-color: #45a049;
                    }
                    QPushButton:pressed {
                        background-color: #3e8e41;
                    }
                )");

                // Обрабатываем результат
                if (inputDialog.exec() == QDialog::Accepted) {
                    QString userText = inputDialog.textValue();
                    if (!userText.isEmpty()) {
                        // Сохраняем текст в файл
                        QFile file("../../ml/user_text.txt");
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
    qDebug() << "Начало функции saveSelection";
    
    // Читаем текст промпта из файла
    QString prompt;
    QFile promptFile("../../ml/user_text.txt");
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
    QNetworkRequest request(QUrl("http://192.168.0.7:5000/generate"));
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
