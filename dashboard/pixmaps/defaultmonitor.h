#ifndef DEFAULTMONITOR_H
#define DEFAULTMONITOR_H

#include <QPixmap>
#include "dashboardcontent.h"
#include "textframe.h"



enum
{
    STATUS_MSG = 0,
    GEAR,
    BEST_LAP,
    LAST_LAP,
    DELTA_LAP,
    DELTA_S1,
    DELTA_S2,
    DELTA_S3,
    TEMP_OIL,
    TEMP_WAT,
    PLACEHOLDER1,
    POSITION,
    DELTA_BEHIND,
    DELTA_AHEAD,


    //------
    DES_MAX
};


class DefaultMonitor : public DashboardContent
{

    friend class DashboardContent;


private:

    TextFrame labels[DES_MAX];
    TextFrame values[DES_MAX];


    void calculateFrames();
    void drawLabels();
    void drawValues(clientDataStruct data);




public:
    DefaultMonitor();


};

#endif // DEFAULTMONITOR_H

