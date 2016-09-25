#ifndef SRD_CLIENT_H
#define SRD_CLIENT_H

#include "config/config.h"
#include "clientData.h"
#include "dashboard/dashboard.h"

class srd_client
{
private:
    Config config;
    clientDataStruct gameData;
    Dashboard *dashboard;

public:
    srd_client();

    void init_config();
    void init_dashboard();
    void init_serialport();
};

#endif // SRD_CLIENT_H
