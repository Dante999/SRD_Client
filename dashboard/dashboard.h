#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>

#include "pixmaps/defaultmonitor.h"










class Dashboard : public QWidget
{
    Q_OBJECT


private:

    enum monitor{FIRST, DEFAULT, DAMAGE, /**/ LAST} curMonitor;
    DashboardContent *content;
    clientDataStruct *gameData;

    void selectMonitor();



public:

    Dashboard(clientDataStruct *gameData);
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent* e);


};

#endif // DASHBOARD_H
