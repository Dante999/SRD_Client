#include "dashboard.h"
#include <QPainter>
#include <QKeyEvent>
#include <QMessageBox>
#include <QDebug>

#include "pixmaps/defaultmonitor.h"
#include "pixmaps/damagemonitor.h"



void Dashboard::selectMonitor()
{

    if(content != Q_NULLPTR) delete content;


    switch (curMonitor) {
    case DEFAULT:
        content = new DefaultMonitor();
        break;

    case DAMAGE:
        content = new DamageMonitor();
        break;

    default:
        content = new DamageMonitor();
        break;
    }


}

Dashboard::Dashboard(clientDataStruct *gameData)
{
    content = Q_NULLPTR;


    this->gameData = gameData;
    curMonitor = DEFAULT;

    selectMonitor();
}


void Dashboard::paintEvent(QPaintEvent *)
{
    content->drawValues(*gameData);

    QPainter painter(this);

    QPixmap scaledPixmap = content->scaled(this->width(),
                                           this->height(),
                                           Qt::KeepAspectRatio,
                                           Qt::SmoothTransformation);

    painter.drawPixmap(0, 0, this->width(), this->height(), scaledPixmap);

}

void Dashboard::keyPressEvent(QKeyEvent *e)
{

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



}






