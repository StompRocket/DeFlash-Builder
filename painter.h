#ifndef PAINTER_H
#define PAINTER_H

#include <QWidget>
#include <QMouseEvent>
#include <QPen>
#include <tool.h>
#include "animationframe.h"

class Painter : public QWidget
{
    Q_OBJECT
public:
    explicit Painter(QWidget *parent = nullptr);
    void setSize(int width, int height);
    void setPenWidth(int width);
    int getPenWidth();
    void setPenColor(QColor &color);
    QColor getPenColor();
    double aspectRatio = 480 / 640; // height / width
    void setFrame(AnimationFrame *f);
    Tool tool = Tool::pen;

public slots:
    void clearImage();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void drawLineTo(const QPoint &point);
    void resizeImage(QImage *image, const QSize &newSize);
    QPen pen;
    bool modified = false;
    bool drawing = false;
    AnimationFrame *frame = nullptr;
    QPoint lastPoint;
    QColor penColor;
};

#endif // PAINTER_H
