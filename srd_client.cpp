#include "srd_client.h"
#include <QDebug>

srd_client::srd_client()
{



}

void srd_client::init_config()
{
    config.init();
}

void srd_client::init_dashboard()
{
    qDebug() << "Starting gui...";

    dashboard = new Dashboard(&gameData);

    dashboard->showFullScreen();
}
