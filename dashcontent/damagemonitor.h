#ifndef DAMAGEMONITOR_H
#define DAMAGEMONITOR_H

#include <QImage>
#include <QPainterPath>
#include <QColor>
#include "dashboardcontent.h"
#include "carshape.h"
#include "textframe.h"
#include "../config.h"
namespace DMG
{
    enum part{
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

private:
   Config   *m_config;
   CarShape  m_carshape;
   TextFrame m_values[DMG::DMG_MAX];
   TextFrame m_labels[DMG::DMG_MAX];

   void setLayout();
   void repaintLabels();
   void repaintValues(gameDataStruct data);
   void repaintCarshape(gameDataStruct data);

   QColor getDamageIndicator(int damage);


public:
    DamageMonitor();


};

#endif // DAMAGEMONITOR_H
