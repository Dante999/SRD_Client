#ifndef DAMAGEMONITOR_H
#define DAMAGEMONITOR_H

#include <QImage>
#include <QPainterPath>
#include "dashboardcontent.h"
#include "carshape.h"
#include "textframe.h"

namespace DMG
{
    enum {
        STATUS_MSG = 0,
        TYRE_FRONT_LEFT,
        TYRE_FRONT_RIGHT,
        TYRE_REAR_LEFT,
        TYRE_REAR_RIGHT,
        SUSP_FRONT_LEFT,
        SUSP_FRONT_RIGHT,
        SUSP_REAR_LEFT,
        SUSP_REAR_RIGHT,
        BRAKE_FRONT_LEFT,
        BRAKE_FRONT_RIGHT,
        BRAKE_REAR_LEFT,
        BRAKE_REAR_RIGHT,
        AERO,
        ENGINE,
        //-----
        DMG_MAX
    };
}




class DamageMonitor : public DashboardContent
{

    friend class DashboardContent;


private:



    CarShape carshape;
    TextFrame values[DMG::DMG_MAX];
    TextFrame labels[DMG::DMG_MAX];

    void calculateFrames();
    void refreshCarshape();
    void drawLabels();




public:
    DamageMonitor();

    void drawValues(clientDataStruct data);

};

#endif // DAMAGEMONITOR_H
