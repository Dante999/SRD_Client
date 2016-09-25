#include "srd_client.h"
#include <QDebug>

srd_client::srd_client()
{
    memset(&gameData, 0, sizeof(gameData));




}

void srd_client::init_config()
{
    config.init();
}

void srd_client::init_serialport()
{

}

void srd_client::dataReceived()
{

}

void srd_client::init_dashboard()
{
    qDebug() << "Starting gui...";

    dashboard = new Dashboard(&gameData);    


    if(config.getValue(CFG_FULLSCREEN) == "1")
    {
        dashboard->showFullScreen();
    }
    else
    {
        dashboard->resize(1024,600);
        dashboard->show();
    }

}
