#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>
#include <QString>
#include <QMap>
#include <QFile>
#include <QVariant>

class Config : public QObject
{
    Q_OBJECT

public:
    explicit Config(QString file = "", bool autosave = false, QObject *parent = nullptr);
    QVariant &get(QString key);
    void set(QString key, QVariant val);
    void save();
    void update();

private:
    bool updateInPlace = false;
    QFile sourceFile;
    QMap<QString, QVariant> data;
    QString stringify(QVariant var);
    QVariant parse(QString stuff);
};

#endif // CONFIG_H
