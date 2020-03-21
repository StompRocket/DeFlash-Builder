#include "videoexporter.h"

#include <QDebug>

VideoExporter::VideoExporter(QObject *parent)
    : QObject(parent)
{

}

void VideoExporter::setSize(QSize &newSize)
{
    size = newSize;
}

void VideoExporter::setFps(int newFps)
{
    fps = newFps;
}


bool VideoExporter::render(QDir &frames, QString fileName)
{
    auto cmd = QString("ffmpeg -framerate %1 -i '%3%d.png' '%2'")
            .arg(fps).arg(fileName).arg(frames.filePath("frame"));
    qDebug() << cmd;
    return system(cmd.toUtf8()) == 0;
}
