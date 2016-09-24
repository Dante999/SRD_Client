#include <QApplication>
#include <QDebug>
#include "srd_client.h"


int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
    QApplication a(argc, argv);

    qDebug() << "starting client...";

    srd_client *client = new srd_client();

    client->init_config();
    //client wait for serialPort
    client->init_dashboard();

    return a.exec();
}


