#include "srd_client.h"
#include <QDebug>

srd_client::srd_client()
{
    memset(&gameData, 0, sizeof(gameData));




}

void srd_client::start()
{
    init_config();
    init_serialport();
    init_dashboard();

}

void srd_client::init_config()
{
    config.init();
}

void srd_client::init_serialport()
{
    serialcom = new SerialCom(config.getValue(CFG_SERIALPORT), 19200);

    connect(serialcom, SIGNAL(dataReceived(serialPackage)), this, SLOT(dataFromSerial(serialPackage)));

    serialcom->open();
}

void srd_client::init_dashboard()
{
    qDebug() << "Starting gui...";

    dashboard = new Dashboard(&gameData);    


    if(config.getValue(CFG_FULLSCREEN) == "1")
    {        
        dashboard->showFullScreen();
        qDebug() << "open in fullscreen";
    }
    else
    {
        dashboard->resize(1024,600);
        dashboard->show();
        qDebug() << "open in 1024x600";
    }

}


void srd_client::dataFromSerial(serialPackage package)
{

    qDebug() << "receiving data...";

    switch(package.cmd)
    {

    case CMD_REQUEST:
                        serialcom->writeCommand(CMD_ACK);


    case CMD_GAMEDATA:
                        if(package.length != sizeof(gameData))
                        {
                            qDebug() << "Error datalength!!";
                        }
                        else
                        {
                            memcpy(&gameData, &package.data, sizeof(gameData));
                        }

        break;

    }

    dashboard->update();




}
