#include "painter.h"
#include <QPainter>
#include <QDebug>
#include <QSizePolicy>

Painter::Painter(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
}

void Painter::setSize(int width, int height)
{
    setFixedSize(width, height);
    if (frame != nullptr)
    {
    }
}

void Painter::setFrame(AnimationFrame *f)
{
    frame = f;
    setSize(frame->getWidth(), frame->getHeight());
}

void Painter::clearImage()
{
    if (frame == nullptr) return;
    frame->image.fill(qRgb(255, 255, 255));
    modified = true;
    update();
}

void Painter::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        lastPoint = event->pos();
        drawing = true;
        drawLineTo(event->pos());
    }

    qDebug() << "Clicked at" << event->pos();
}

void Painter::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && drawing)
    {
        drawLineTo(event->pos());
    }
}

void Painter::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && drawing)
    {
        drawLineTo(event->pos());
        drawing = false;
    }
}

void Painter::paintEvent(QPaintEvent *event)
{
    if (frame == nullptr) return;
    QPainter painter(this);
    painter.setPen(pen);
    QRect r = event->rect();
    painter.drawImage(r, frame->image, r);
}

void Painter::resizeEvent(QResizeEvent *event)
{
    if (frame == nullptr) return;
    auto image = &frame->image;
    if (width() > image->width() || height() > image->height()) {
        int newWidth = qMax(width() + 128, image->width());
        int newHeight = qMax(height() + 128, image->height());
        resizeImage(image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

void Painter::drawLineTo(const QPoint &point)
{
    if (frame == nullptr) return;

    qDebug() << "Is frame image null?" << frame->image.isNull();

    QPainter painter(&frame->image);
    if (tool == Tool::pen)
        pen = QPen(penColor, penWidth, Qt::SolidLine, Qt::RoundCap,
                   Qt::RoundJoin);
    else
        pen = QPen(Qt::white, penWidth, Qt::SolidLine,
                   Qt::RoundCap, Qt::RoundJoin);
    painter.drawLine(lastPoint, point);
    modified = true;

    frame->update();

    int rad = (penWidth / 2) + 2;
    update(QRect(lastPoint, point)
           .normalized()
           .adjusted(-rad, -rad, +rad, +rad));
    lastPoint = point;
}

void Painter::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}
