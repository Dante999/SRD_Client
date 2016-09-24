#include "dashboardthread.h"

DashboardThread::DashboardThread(Dashboard *dashboard)
{
    loop = true;
    this->dashboard = dashboard;
}

void DashboardThread::run()
{
    while(loop == true)
    {
        dashboard->update();
        msleep(100);
    }

}

void DashboardThread::stopLoop()
{
    loop = false;
}

