#ifndef CONFIG_H
#define CONFIG_H

#include <QFile>
#include <QString>
#include <QMap>


/**
 * @defgroup configKeys macros for the config keys
 *
 *
*/
/** @{ */
#define CFG_SERIALPORT      "serialport"
#define CFG_FULLSCREEN      "fullscreen"

#define CFG_TYRE_TEMP_COLD  "tyreTempCold"
#define CFG_TYRE_TEMP_HOT   "tyreTempHot"
#define CFG_BRAKE_TEMP_COLD "brakeTempCold"
#define CFG_BRAKE_TEMP_HOT  "brakeTempHot"
#define CFG_OIL_TEMP_COLD   "oilTempCold"
#define CFG_OIL_TEMP_HOT    "oilTempHot"
#define CFG_WAT_TEMP_COLD   "waterTempCold"
#define CFG_WAT_TEMP_HOT    "waterTempHot"

#define CFG_DAMAGE_LOW      "damageLow"
#define CFG_DAMAGE_MID      "damageMid"
#define CFG_DAMAGE_HIGH     "damageHigh"

/** @} */


class Config
{

private:   
   Config();

   QFile m_configFile;
   QMap<QString, QString> m_cfgMap;

   void setDefaultValues();
   void parseLine(const QString line, const int number);
   void readFromFile();
   void writeToFile();

public:
    static Config *getInstance();

    ~Config();
    QString getValue(QString key);

};

#endif // CONFIG_H
