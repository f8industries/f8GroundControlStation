#ifndef SYSTEMPARAMETERS_H
#define SYSTEMPARAMETERS_H

#include <QSettings>
#include <QApplication>
#include <QDebug>

class SystemParameters
{
public:
    SystemParameters();
    ~SystemParameters();

    bool IsValid();

    void createSchema();
    QString getValue(QString &key);
    QString fileName;


signals:

public slots:

};

#endif // SYSTEMPARAMETERS_H
