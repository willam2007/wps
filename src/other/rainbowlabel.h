#ifndef RAINBOWLABEL_H
#define RAINBOWLABEL_H

#include <QLabel>
#include <QTimer>
#include <QLinearGradient>
#include <QPainter>

class RainbowLabel : public QLabel {
    Q_OBJECT
public:
    explicit RainbowLabel(QWidget *parent = nullptr);
    void setText(const QString &text);

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void updateGradient();

private:
    QTimer *timer;
    qreal hue;
};

#endif // RAINBOWLABEL_H