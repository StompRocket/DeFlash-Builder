#include "config.h"

#include <QDir>
#include <QDebug>
#include <QRegularExpression>
#include <functional>
#include <iterator>

Config::Config(QString file, bool autosave, QObject *parent)
    : QObject(parent)
    , updateInPlace(autosave)
    , sourceFile(file)
{
    update();
}

void Config::update()
{
    data.clear();
    // opening for read-write so it will create the file if it doesn't exist
    sourceFile.open(QIODevice::ReadWrite);
    for (QByteArray k = sourceFile.readLine(); k.length() > 0; k = sourceFile.readLine())
    {
        QRegularExpression re{"^([a-zA-Z_\\.\\-]+) +(.+)$"};
        auto t = QString(k).trimmed();
        if (t.length() == 0) // ignore empty lines
            continue;

        auto match = re.match(t);
        if (!match.hasMatch())
        {
            qDebug() << "Could not match line" << QString(k);
        }

        data[match.captured(1)] = parse(match.captured(2));
    }
    sourceFile.close();
}

void Config::save()
{
    sourceFile.open(QIODevice::WriteOnly);
    for (auto k : data.keys())
    {
        auto str = QString("%1 %2\n").arg(k).arg(stringify(data[k])).toUtf8();
        qDebug() << str;
        sourceFile.write(str);
    }
    sourceFile.flush();
    sourceFile.close();
}

QVariant Config::parse(QString stuff)
{
    bool ok = true;
    int i = stuff.toInt(&ok);
    if (ok)
        return QVariant(i);
    double d = stuff.toDouble(&ok);
    if (ok)
        return QVariant(d);
    if (stuff == "true" || stuff == "false")
        // ? true : false is needed so it's not an int.
        return QVariant(stuff == "true" ? true : false);
    return QVariant(stuff);
}

QString Config::stringify(QVariant var)
{
    switch (var.type())
    {
    case QVariant::Type::Int:
        return QString::number(var.toInt());
    case QVariant::Type::Double:
        return QString::number(var.toDouble());
    case QVariant::Type::Bool:
        return QString(var.toBool());
    case QVariant::Type::String:
        return var.toString();
    default:
        return "#INVALID_DATA#";
    }
}

QVariant &Config::get(QString key)
{
    return data[key];
}

void Config::set(QString key, QVariant val)
{
    data[key] = val;
    if (updateInPlace)
        save();
}

QVariant Config::getOrSet(QString key, QVariant val)
{
    if (!data.contains(key))
        set(key, val);
    return get(key);
}

bool Config::exists(QString key)
{
    return data.contains(key);
}
