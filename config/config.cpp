#include "config.h"
#include <QDebug>

Config::Config()
{




}

void Config::init()
{
    qDebug() << "Checking config.cfg file...";
    fConfig.setFileName("config.cfg");

    if(fConfig.exists() == true)
    {
        qDebug() << "File config.cfg found!";
    }
    else
    {
        qDebug() << "File config.cfg not found!";
    }
}
