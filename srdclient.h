#ifndef SRDCLIENT_H
#define SRDCLIENT_H

#include "QObject"
#include "config.h"
#include "gameData.h"
#include "serialcom.h"
#include "dashboard.h"


class SrdClient : public QObject
{
   Q_OBJECT

private:
   Config *m_config;
   gameDataStruct m_gameData;
   Dashboard *m_dashboard;
   SerialCom *m_serialCom;


public:
   SrdClient();
   void start();

private slots:
   void executeCommand(serialPackage serialData);

};

#endif // SRDCLIENT_H
