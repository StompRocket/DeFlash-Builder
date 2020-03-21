#ifndef VIDEOEXPORTER_H
#define VIDEOEXPORTER_H

#include "animationframe.h"

#include <QObject>
#include <QSize>
#include <QDir>
#include <QDir>
#include <QString>


class VideoExporter : public QObject
{
    Q_OBJECT

public:
    explicit VideoExporter(QObject *parent = nullptr);
    void setSize(QSize &size);
    void setFps(int newFps);
    bool render(QDir &frames, QString fileName);

private:
    QSize size{640, 480};
    int fps = 12;
};

#endif // VIDEOEXPORTER_H
