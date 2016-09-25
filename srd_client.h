#ifndef SRD_CLIENT_H
#define SRD_CLIENT_H

#include "config/config.h"
#include "clientData.h"
#include "dashboard/dashboard.h"

class srd_client
{

    Q_OBJECT

private:
    Config config;
    clientDataStruct gameData;
    Dashboard *dashboard;

public:
    srd_client();

    void init_config();
    void init_dashboard();
    void init_serialport();

private slots:

    void dataReceived();

    void refreshGameData(clientDataStruct data);
};

#endif // SRD_CLIENT_H
