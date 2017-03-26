#include "config.h"
#include <QDebug>

#define CONFIG_FILENAME     "config.cfg"



/*******************************************************************************
 * @brief   constructor
 *
 * the constructor checks if the configfile exists. If it doesn't a configfile
 * with default values will be created and used.
 *
 * @param   none
 *
 * @return  none
 *
*******************************************************************************/
Config::Config()
{
    qDebug() << "checking configfile...";
    m_configFile.setFileName(CONFIG_FILENAME);

    if(m_configFile.exists())
    {
        qDebug() << CONFIG_FILENAME << "found!";
    }
    else
    {
        qDebug() << "[W]" << CONFIG_FILENAME << "not found!";
        qDebug() << "creating configfile with default values...";
        setDefaultValues();
        writeToFile();
    }

    readFromFile();
}


/*******************************************************************************
 * @brief   destructor
 *
 * writes all keys with its values to the configfile
 *
 * @param   none
 *
 * @return  none
 *
*******************************************************************************/
Config::~Config()
{
    writeToFile();
}


/*******************************************************************************
 * @brief   reads the configfile
 *
 * reads all keys with its values from the configfile and saves them in a class
 * member. All values can be accessed with the 'getValue()' function.
 *
 * @param   none
 *
 * @return  none
 *
*******************************************************************************/
void Config::readFromFile()
{
    int lineCounter = 0;

    qDebug() << "start reading from configfile";
    m_configFile.open(QIODevice::ReadWrite | QIODevice::Text);

    QTextStream in(&m_configFile);

    while(!in.atEnd())
    {
        lineCounter++;        
        parseLine(in.readLine(), lineCounter);
    }

    qDebug() << "finished reading from configfile";
    m_configFile.close();
}

void Config::writeToFile()
{
    qDebug() << "start writing values to configfile";

    QMapIterator<QString,QString> i(m_cfgMap);

    m_configFile.open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream out(&m_configFile);

    out << "#Config-file for SRD_Client\n";
    out << "#Created by Dante999\n";
    out << "##############################\n\n";

    while(i.hasNext())
    {
        i.next();
        out << i.key() + "=\"" + i.value() + "\"\n";
    }

    qDebug() << "finished writing values to configfile";
    m_configFile.close();
}


void Config::setDefaultValues()
{
    m_cfgMap.insert(CFG_SERIALPORT,     "ttyAMA0");
    m_cfgMap.insert(CFG_FULLSCREEN,     "1");

    m_cfgMap.insert(CFG_TYRE_TEMP_COLD, "90");
    m_cfgMap.insert(CFG_TYRE_TEMP_HOT,  "120");
    m_cfgMap.insert(CFG_OIL_TEMP_COLD,  "90");
    m_cfgMap.insert(CFG_OIL_TEMP_HOT,   "120");
    m_cfgMap.insert(CFG_WAT_TEMP_COLD,  "90");
    m_cfgMap.insert(CFG_WAT_TEMP_HOT,   "120");

    m_cfgMap.insert(CFG_DAMAGE_LOW,     "5");
    m_cfgMap.insert(CFG_DAMAGE_MID,     "10");
    m_cfgMap.insert(CFG_DAMAGE_HIGH,    "15");
}

void Config::parseLine(const QString line, const int number)
{
    QString key;
    QString value;
    int posStart = 0;
    int posLength = 0;

    if(!line.startsWith('#') && !line.isEmpty())
    {
        try
        {
            if(!line.contains('=')) throw (QString)"No delimiter '=' found!";

            posStart = 0;
            posLength = line.indexOf('=') - posStart;

            key = line.mid(posStart, posLength);

            posStart = line.indexOf('"', posStart+posLength) + 1;
            posLength = line.indexOf('"', posStart) - posStart;

            if(posStart < 0 || posLength < 0) throw (QString)"Uncomplete value!";

            value = line.mid(posStart, posLength);

            qDebug() << key << "->" << value;

            m_cfgMap.insert(key, value);

        }
        catch(QString &msg)
        {
            qDebug() << "[E] Line" << number << ":" << msg;
        }
    }



}


/*******************************************************************************
 * @brief   returns the value of the given key
 *
 * searches in the class member for the key and gives its value back.
 * For example the configvalue entry "fullscreen=1" has the key "fullscreen"
 * and the value "1". So the function call getValue("fullscreen"); will
 * return "1".
 *
 * @param   key     key of the value
 *
 * @return  the value of the key
 *
*******************************************************************************/
QString Config::getValue(QString key)
{
    if(m_cfgMap.contains(key))
    {
        return m_cfgMap.value(key);
    }
    else
    {
        return "";
    }
}




