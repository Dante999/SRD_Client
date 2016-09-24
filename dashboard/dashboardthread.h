#ifndef DASHBOARDTHREAD_H
#define DASHBOARDTHREAD_H

#include "dashboard.h"
#include <QThread>

class DashboardThread : public QThread
{

private:
    bool loop;
    Dashboard *dashboard;


public:

    DashboardThread(Dashboard *dashboard);
    void run();
    void stopLoop();

};

#endif // DASHBOARDTHREAD_H
