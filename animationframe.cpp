#include "animationframe.h"

#include <QPainter>
#include <memory>

AnimationFrame::AnimationFrame(int width, int height, QObject *parent)
    : QObject(parent)
    , image(width, height, QImage::Format::Format_ARGB32)
    , tableWidget(" ")
    , height(height)
    , width(width)
{
    clear();
}

AnimationFrame::AnimationFrame(const AnimationFrame &frame, QObject *parent)
    : QObject(parent)
    , image(frame.image)
    , tableWidget(frame.tableWidget)
    , height(frame.height)
    , width(frame.width)
{

}

AnimationFrame &AnimationFrame::operator=(const AnimationFrame &frame)
{
    image = frame.image;
    tableWidget = frame.tableWidget;
    height = frame.height;
    width = frame.width;
    return *this;
}

void AnimationFrame::clear()
{
    image.fill(QColor(255, 255, 255));
    blank = true;
}

void AnimationFrame::resize(const QSize newSize)
{
    if (image.size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), image);
    image = newImage;
}

void AnimationFrame::update()
{
    blank = false;
    tableWidget.setText("•");
    QFont font{};
    font.setPixelSize(32);
    tableWidget.setFont(font);
    tableWidget.setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    tableWidget.setTextColor(QColor(252, 190, 3));
}

bool AnimationFrame::getIsBlank()
{
    return blank;
}

int AnimationFrame::getHeight() const
{
    return height;
}

int AnimationFrame::getWidth() const
{
    return width;
}
