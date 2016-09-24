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
        fConfig.open(QIODevice::ReadWrite | QIODevice::Text);
    }
    else
    {
        qDebug() << "[W] File config.cfg not found!";
        qDebug() << "Creating default config.cfg file:..";
        fConfig.open(QIODevice::ReadWrite | QIODevice::Text);
        setDefaultValues();
        writeToFile();
    }

    readFromFile();
}


void Config::readFromFile()
{
    int lineCounter = 0;

    qDebug() << "Start reading from config.cfg...";

    QTextStream in(&fConfig);

    while(!in.atEnd())
    {
        lineCounter++;

        QString line = in.readLine();
        parseLine(line, lineCounter);
    }

    qDebug() << "End reading from config.cfg!";
}

void Config::writeToFile()
{
    QMapIterator<QString,QString> i(values);
    QTextStream out(&fConfig);


    out << "#Config-file for SRD_Client\n";
    out << "#Created by Dante999\n";
    out << "##############################\n\n";

    while(i.hasNext())
    {
        i.next();

        out << i.key() + "=\"" + i.value() + "\"\n";
    }
}


void Config::setDefaultValues()
{
    values.insert(CFG_SERIALPORT, "ttyAMA0");
    values.insert(CFG_FULLSCREEN, "1");
}

void Config::parseLine(const QString line, const int number)
{
    QString key;
    QString value;

    int posStart = 0;
    int posLength = 0;

    if(line.startsWith('#')) return;
    if(line.isEmpty()) return;

    try
    {
        if(line.contains('=') == false) throw (QString)"No delimiter '=' found!";


        posStart = 0;
        posLength = line.indexOf('=') - posStart;

        key = line.mid(posStart, posLength);

        posStart = line.indexOf('"', posStart+posLength) + 1;
        posLength = line.indexOf('"', posStart) - posStart;

        if(posStart < 0 || posLength < 0) throw (QString)"Uncomplete value!";

        value = line.mid(posStart, posLength);

        qDebug() << key << "->" << value;

    }
    catch(QString &msg)
    {
        qDebug() << "[E] Line" << number << ":" << msg;
    }






}
