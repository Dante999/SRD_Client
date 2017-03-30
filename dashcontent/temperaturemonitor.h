#ifndef TEMPERATUREMONITOR_H
#define TEMPERATUREMONITOR_H

#include "dashboardcontent.h"
#include "carshape.h"
#include "textframe.h"
#include "../config.h"

namespace TEMP
{
    enum part{
        STATUS_MSG = 0,
        TYRE_FRONT_LEFT,
        TYRE_FRONT_RIGHT,
        TYRE_REAR_LEFT,
        TYRE_REAR_RIGHT,
        BRAKE_FRONT_LEFT,
        BRAKE_FRONT_RIGHT,
        BRAKE_REAR_LEFT,
        BRAKE_REAR_RIGHT,
        OIL,
        WATER,
        //-----
        TEMP_MAX
    };
}




class TemperatureMonitor : public DashboardContent
{

private:
   Config   *m_config;
   CarShape  m_carshape;
   TextFrame m_values[TEMP::TEMP_MAX];
   TextFrame m_labels[TEMP::TEMP_MAX];

   void setLayout();
   void repaintLabels();
   void repaintValues(gameDataStruct data);
   void repaintCarshape(gameDataStruct data);

   QColor getTempIndicator(int temperature, int limitLow, int limitHigh);


public:
    TemperatureMonitor();


};

#endif // TEMPERATUREMONITOR_H
