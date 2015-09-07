#include "systemparameters.h"

SystemParameters::SystemParameters()
{
    fileName = "config.ini";
    QSettings s(fileName,QSettings::IniFormat);

}


SystemParameters::~SystemParameters()
{

}

QString SystemParameters::getValue(QString &key)
{
    QSettings s(fileName,QSettings::IniFormat);
    return s.value(key).toString();
}


bool SystemParameters::IsValid()
{
    QSettings s(fileName,QSettings::IniFormat);
    if(s.isWritable())
        {return true;}
    else
        {return false;};

}

void SystemParameters::createSchema()
{
    QSettings s(fileName,QSettings::IniFormat);

    s.beginGroup("app");

    s.setValue("active","1");

    s.endGroup();

    s.beginGroup("video");
        s.setValue("adress","localhost");
        s.setValue("port","1234");
        s.setValue("height","800");
        s.setValue("width","600");
    s.endGroup();

    s.beginGroup("map");
        s.setValue("adress","qrc:/html/google_maps.html");
    s.endGroup();

    if(s.isWritable())
    {
        qDebug()<<"ok";
    }
}
