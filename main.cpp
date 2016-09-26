#include <QApplication>
#include <QDebug>
#include "srd_client.h"


int main(int argc, char *argv[])
{    
    QApplication a(argc, argv);

    qDebug() << "starting client...";

    srd_client *client = new srd_client();

    client->start();

    return a.exec();
}


