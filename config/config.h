#ifndef CONFIG_H
#define CONFIG_H

#include <QFile>
#include <QString>
#include <QMap>



#define CFG_SERIALPORT  "serialport"
#define CFG_FULLSCREEN  "fullscreen"



class Config
{

private:
    QFile fConfig;

public:
    Config();
    void init();




    void writeToFile();
    QString getValue(QString key);
private:
    QMap<QString, QString> cfgMap;


    void setDefaultValues();
    void parseLine(const QString line, const int number);
    void readFromFile();
};

#endif // CONFIG_H
