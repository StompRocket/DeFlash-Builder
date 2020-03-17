#ifndef PROJECTFILE_H
#define PROJECTFILE_H


#include <QString>
#include <QList>
#include <QStringList>

class ProjectFile
{
public:
    ProjectFile(QString file);
    QString toString();

    QString name;
    double swfVersion = 11.8;
    int width = 640;
    int height = 480;
    int fps = 24;
    QStringList libs;

private:
    QString file;
};

#endif // PROJECTFILE_H
