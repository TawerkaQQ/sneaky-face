#include "videowidget.h"
#include <QPainter>

VideoWidget::VideoWidget(QWidget *parent) : QWidget(parent)
{
}

void VideoWidget::setImage(const QImage &image)
{
    currentImage = image;
    update(); // Обновляем виджет, чтобы вызвать paintEvent
}

void VideoWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if (!currentImage.isNull()) {
        painter.drawImage(this->rect(), currentImage);
    }
}
