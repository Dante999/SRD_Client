#include "dashboard.h"
#include <QPainter>
#include <QKeyEvent>
#include <QMessageBox>
#include <QDebug>




Dashboard::Dashboard(gameDataStruct *gameData)
{
    //m_dashContent = Q_NULLPTR;
    //curMonitor = DAMAGE;

    this->m_gameData = gameData;

    m_contentIndex = 0;
    //m_contents.append(new DefaultMonitor());
    //m_contents.append(new DamageMonitor());
}



void Dashboard::showNextContent()
{
    qDebug() << "---------------------------------";
    qDebug() << "nextContent";
    qDebug() << "current: " << m_contentIndex;

    if(m_contentIndex < m_contents.count()-1)
    {
        m_contentIndex++;
    }
    else
    {
        m_contentIndex = 0;
    }

    qDebug() << "new: " << m_contentIndex;
}

void Dashboard::showPreviousContent()
{
    qDebug() << "---------------------------------";
    qDebug() << "nextContent";
    qDebug() << "current: " << m_contentIndex;

    if(m_contentIndex > 0)
    {
        m_contentIndex--;
    }
    else
    {
        m_contentIndex = m_contents.count()-1;
    }

    qDebug() << "new: " << m_contentIndex;
}




void Dashboard::paintEvent(QPaintEvent *)
{
    DashboardContent *content = m_contents.at(m_contentIndex);

    content->drawValues(*m_gameData);

    QPixmap scaledPixmap = content->scaled(this->width(),
                                            this->height(),
                                            Qt::KeepAspectRatio,
                                            Qt::SmoothTransformation);

    QPainter painter(this);

    painter.drawPixmap(0, 0, this->width(), this->height(), scaledPixmap);



    /*
    m_dashContent->drawValues(*m_gameData);

    QPainter painter(this);

    QPixmap scaledPixmap = m_dashContent->scaled(this->width(),
                                           this->height(),
                                           Qt::KeepAspectRatio,
                                           Qt::SmoothTransformation);

    painter.drawPixmap(0, 0, this->width(), this->height(), scaledPixmap);
    */
}

void Dashboard::keyPressEvent(QKeyEvent *e)
{

    if(e->key() == Qt::Key_Left)
    {
        showPreviousContent();
    }
    else if(e->key() == Qt::Key_Right)
    {
        showNextContent();
    }

    /*
      if(e->key() == Qt::Key_Left)
      {
          if(curMonitor == FIRST+1)
          {
              curMonitor = static_cast<monitor>(LAST-1);
          }
          else
          {
              int i = curMonitor;
              curMonitor = static_cast<monitor>(i-1);
          }
      }
      else if(e->key() == Qt::Key_Right)
      {
        if(curMonitor == LAST-1)
        {
            curMonitor = static_cast<monitor>(FIRST+1);
        }
        else
        {
            int i = curMonitor;
            curMonitor = static_cast<monitor>(i+1);
        }
      }



      selectMonitor();

*/

}






