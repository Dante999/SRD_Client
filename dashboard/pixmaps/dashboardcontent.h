#ifndef INTERFACEMONITOR_H
#define INTERFACEMONITOR_H

#include "clientData.h"
#include <QPixmap>


class DashboardContent : public QPixmap
{

private:

    virtual void calculateFrames() = 0;
    virtual void drawLabels() = 0;


public:
    DashboardContent();
    virtual void drawValues(clientDataStruct data) = 0;


};

#endif // INTERFACEMONITOR_H
