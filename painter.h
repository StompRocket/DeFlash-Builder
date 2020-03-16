#ifndef PAINTER_H
#define PAINTER_H

#include <QWidget>
#include <QMouseEvent>
#include <tool.h>

class Painter : public QWidget
{
    Q_OBJECT
public:
    explicit Painter(QWidget *parent = nullptr);
    void setSize(int width, int height);
    int penWidth = 10;
    double aspectRatio = 480 / 640; // height / width
    QColor penColor = Qt::black;
    Tool tool = Tool::pen;

public slots:
    void clearImage();
    // void print();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void drawLineTo(const QPoint &point);
    void resizeImage(QImage *image, const QSize &newSize);

    bool modified = false;
    bool drawing = false;
    QImage image;
    QPoint lastPoint;
};

#endif // PAINTER_H
