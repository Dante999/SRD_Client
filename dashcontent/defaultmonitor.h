#ifndef DEFAULTMONITOR_H
#define DEFAULTMONITOR_H


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
    DESIGNATOR_MAX
};

class DefaultMonitor : public DashboardContent
{
private:
    TextFrame m_labels[DESIGNATOR_MAX];
    TextFrame m_values[DESIGNATOR_MAX];

    void setLayout();
    void repaintLabels();
    void repaintValues(gameDataStruct data);
    void repaintCarshape(gameDataStruct data);

public:
    DefaultMonitor();


};




#endif // DEFAULTMONITOR_H
