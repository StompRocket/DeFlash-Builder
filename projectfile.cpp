#include "projectfile.h"

#include <tuple>
#include <QtXmlPatterns/QXmlQuery>
#include <QDebug>

ProjectFile::ProjectFile(QString file)
    : file(file)
{
    const auto query = QString("doc('%1')//project/%2/%3/string()").arg(file);

    typedef std::tuple<int &, QString, QString> tpl;

    QList<tpl> data(
        {
            tpl(fps, "window", "fps"),
            tpl(width, "window", "width"),
            tpl(height, "window", "height"),
        }
    );
    QXmlQuery q;

    for (auto [var, tag, key] : data)
    {
        qDebug() << "Getting" << tag << key;
        q.setQuery(query.arg(tag).arg(key));
        q.evaluateTo(&libs);
        var = libs.first().toInt();
    }

    q.setQuery(query.arg("haxelib").arg("name"));
    q.evaluateTo(&libs);
}

QString ProjectFile::toString()
{
    QString str;

    str = "<?xml version=\"1.0\" encoding=\"utf-8\"?> <project>";

    str += "</project>";
}
