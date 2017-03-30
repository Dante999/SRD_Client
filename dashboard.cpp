#include "dashboard.h"
#include <QPainter>
#include <QKeyEvent>
#include <QMessageBox>
#include <QDebug>

#include "dashcontent/defaultmonitor.h"
#include "dashcontent/damagemonitor.h"
#include "dashcontent/temperaturemonitor.h"


Dashboard::Dashboard(gameDataStruct *gameData)
{
    m_contentIndex = 0;
    m_gameData = gameData;

    m_contents.append(new DefaultMonitor());
    m_contents.append(new DamageMonitor());
    m_contents.append(new TemperatureMonitor());

}



void Dashboard::showNextContent()
{
    if(m_contentIndex < m_contents.count()-1)
    {
        m_contentIndex++;
    }
    else
    {
        m_contentIndex = 0;
    } 
}


void Dashboard::showPreviousContent()
{
    if(m_contentIndex > 0)
    {
        m_contentIndex--;
    }
    else
    {
        m_contentIndex = m_contents.count()-1;
    }
}




void Dashboard::paintEvent(QPaintEvent *)
{
    DashboardContent *content = m_contents.at(m_contentIndex);

    content->drawData(*m_gameData);

    QPixmap scaledPixmap = content->scaled(width(), height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QPainter painter(this);

    painter.drawPixmap(0, 0, this->width(), this->height(), scaledPixmap);
}



void Dashboard::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Left)
    {
        showPreviousContent();
        this->update();
    }
    else if(e->key() == Qt::Key_Right)
    {
        showNextContent();
        this->update();
    }
}






