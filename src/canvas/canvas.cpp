#include "canvas.h"
#include "ui_canvas.h"
#include "../area/scribblearea.h"
#include <qboxlayout.h>
#include <qpainter.h>
#include <QtWidgets>

Canvas::Canvas(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Canvas)

{
    setAttribute(Qt::WA_StaticContents);
    ui->setupUi(this);
    scribbleArea = new ScribbleArea(this);
    QVBoxLayout *layout = new QVBoxLayout(ui->canvas_space);
    layout->addWidget(scribbleArea);
    ui->canvas_space->setStyleSheet("border: 2px solid black; border-radius: 10px; background-color: lightgray;");
    QPushButton *drawButton = new QPushButton("Draw", this);
    QPushButton *selectButton = new QPushButton("Select", this);

    connect(drawButton, &QPushButton::clicked, this, [this]() {
        scribbleArea->setMode(ScribbleArea::Drawing);
    });
    connect(selectButton, &QPushButton::clicked, this, [this]() {
        scribbleArea->setMode(ScribbleArea::Selecting);
    });

    layout->addWidget(drawButton);
    layout->addWidget(selectButton);

}

Canvas::~Canvas()
{
    delete ui;
}

// User tried to close the app
void Canvas::closeEvent(QCloseEvent *event)
{
    // If they try to close maybeSave() returns true
    // if no changes have been made and the app closes
    if (maybeSave()) {
        event->accept();
    } else {
        // If there have been changes ignore the event
        event->ignore();
    }
}

void Canvas::openIm()
{
    if (maybeSave()) {
        QDir dir(QDir::current());
        dir.cdUp(); // Поднимаемся на уровень выше
        dir.cdUp(); // Поднимаемся на уровень выше

        QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("Open File"), dir.absolutePath());
        // If we have a file name load the image and place
        // it in the scribbleArea
        if (!fileName.isEmpty()) {
            QSize canvasSize = getCanvasSpaceSize();
            scribbleArea->openImage(fileName,canvasSize); // Передаем размер canvas_space
        }
    }
}

bool Canvas::maybeSave()
{
    // Check for changes since last save
    if (scribbleArea->isModified()) {
        QMessageBox::StandardButton ret;

        // Scribble is the title
        // Add text and the buttons
        ret = QMessageBox::warning(this, tr("Scribble"),
                                   tr("The image has been modified.\n"
                                      "Do you want to save your changes?"),
                                   QMessageBox::Save | QMessageBox::Discard
                                       | QMessageBox::Cancel);

        // If save button clicked call for file to be saved
        if (ret == QMessageBox::Save) {
            return saveFile("png");

            // If cancel do nothing
        } else if (ret == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}

bool Canvas::saveFile(const QByteArray &fileFormat)
{
    // Define path, name and default file type
    QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;

    // Get selected file from dialog
    // Add the proper file formats and extensions
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                                                    initialPath,
                                                    tr("%1 Files (*.%2);;All Files (*)")
                                                        .arg(QString::fromLatin1(fileFormat.toUpper()))
                                                        .arg(QString::fromLatin1(fileFormat)));

    // If no file do nothing
    if (fileName.isEmpty()) {
        return false;
    } else {

        // Call for the file to be saved
        return scribbleArea->saveImage(fileName, fileFormat.constData());
    }
}


QSize Canvas::getCanvasSpaceSize() const
{
    return ui->canvas_space->size();
}


void Canvas::on_open_button_canvas_triggered()
{
    this->openIm();
}

