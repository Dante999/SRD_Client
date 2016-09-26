#ifndef SRD_CLIENT_H
#define SRD_CLIENT_H

#include "config/config.h"
#include "clientData.h"
#include "serialcom.h"
#include "dashboard/dashboard.h"

class srd_client : public QObject
{

    Q_OBJECT

private:
    Config config;
    gameDataStruct gameData;

    Dashboard *dashboard;
    SerialCom *serialcom;

    void init_config();
    void init_dashboard();
    void init_serialport();

public:
    srd_client();
    void start();



private slots:

    void dataFromSerial(serialPackage serialData);

};

#endif // SRD_CLIENT_H
