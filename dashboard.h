#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>
#include <QVector>

#include "dashcontent/dashboardcontent.h"
#include "gameData.h"

class Dashboard : public QWidget
{
    Q_OBJECT


private:
    DashboardContent *m_dashContent;
    gameDataStruct *m_gameData;

    int m_contentIndex;
    QVector<DashboardContent*> m_contents;

    void showNextContent();
    void showPreviousContent();


public:

    Dashboard(gameDataStruct *m_gameData);
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent* e);


};

#endif // DASHBOARD_H
