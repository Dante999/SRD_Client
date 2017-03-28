#include "dashboardcontent.h"



DashboardContent::DashboardContent() : QPixmap(PIXMAP_WIDTH, PIXMAP_HEIGHT)
{

}

void DashboardContent::drawData(gameDataStruct data)
{
   repaintCarshape(data);
   repaintValues(data);
   repaintLabels();
}
