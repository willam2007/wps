#include "rainbowlabel.h"

RainbowLabel::RainbowLabel(QWidget *parent)
    : QLabel(parent), hue(0.0)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &RainbowLabel::updateGradient);
    timer->start(30); // обновлять каждые 30 мс для плавности
}

void RainbowLabel::setText(const QString &text)
{
    QLabel::setText(text);
    update();
}

void RainbowLabel::updateGradient()
{
    hue += 0.005;
    if (hue > 1.0) hue = 0.0;
    update();
}

void RainbowLabel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QFont font = this->font();
    painter.setFont(font);

    QRect rect = this->rect();
    QString text = this->text();

    QLinearGradient gradient(rect.topLeft(), rect.topRight());
    for (int i = 0; i <= 6; ++i) {
        qreal pos = i / 6.0;
        QColor color;
        color.setHsvF(fmod(hue + pos, 1.0), 1.0, 1.0);
        gradient.setColorAt(pos, color);
    }
    painter.setPen(QPen(QBrush(gradient), 0));
    painter.drawText(rect, alignment(), text);
}