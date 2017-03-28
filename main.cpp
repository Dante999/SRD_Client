#include <QApplication>
#include <QDebug>
#include "srdclient.h"


int main(int argc, char *argv[])
{    
    QApplication a(argc, argv);

    qDebug() << "starting client...";

    SrdClient *client = new SrdClient();
    client->start();

    return a.exec();
}


