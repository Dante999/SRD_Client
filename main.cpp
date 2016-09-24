#include <QCoreApplication>
#include <QDebug>
#include "srd_client.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "starting client...";

    srd_client *client = new srd_client();


    return a.exec();
}
