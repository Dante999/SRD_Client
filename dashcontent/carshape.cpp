#include "carshape.h"
#include "dashboardcontent.h"

#include <QPainter>
#include <QDebug>


#define TYRE_WIDTH      26
#define TYRE_HEIGHT     61
#define TYRE_RADIUS     4

#define BRAKE_WIDTH     7
#define BRAKE_HEIGHT    53
#define BRAKE_RADIUS    2



CarShape::CarShape() : QPixmap(PIXMAP_WIDTH, PIXMAP_HEIGHT)
{
   if( m_carImage.load("img//carframe.png") == false)
   {
       qDebug() << "can't load image carshape!";
   }

   createTyres();
   createBrakes();
   createEngine();
   createFrontwing();
   createSuspensionFront();
   createSuspensionRear();
}


/*******************************************************************************
 * @brief   none
 *
 * @param   opacity  0.0=transparent, 1.0=full
 *
 * @return  none
 *
*******************************************************************************/
void CarShape::colorPart(carPart::parts carPart, QColor color, qreal opacity)
{
   QPainter paint;

   paint.begin(this);
   paint.setOpacity(opacity);
   paint.fillPath(m_carParts[carPart], QBrush(color));
   paint.end();
}


/*******************************************************************************
 * @brief   creates shapes for all four tyres
 *
 * @param   none
 *
 * @return  none
 *
*******************************************************************************/
void CarShape::createTyres()
{
   m_carParts[carPart::TYRE_FRONT_LEFT].addRoundedRect( 431, 188, TYRE_WIDTH, TYRE_HEIGHT, TYRE_RADIUS, TYRE_RADIUS);
   m_carParts[carPart::TYRE_FRONT_RIGHT].addRoundedRect(568, 188, TYRE_WIDTH, TYRE_HEIGHT, TYRE_RADIUS, TYRE_RADIUS);
   m_carParts[carPart::TYRE_REAR_LEFT].addRoundedRect(  431, 488, TYRE_WIDTH, TYRE_HEIGHT, TYRE_RADIUS, TYRE_RADIUS);
   m_carParts[carPart::TYRE_REAR_RIGHT].addRoundedRect( 568, 488, TYRE_WIDTH, TYRE_HEIGHT, TYRE_RADIUS, TYRE_RADIUS);
}


/*******************************************************************************
 * @brief   creates shapes for all four brakes
 *
 * @param   none
 *
 * @return  none
 *
*******************************************************************************/
void CarShape::createBrakes()
{
   m_carParts[carPart::BRAKE_FRONT_LEFT].addRoundedRect(458, 191, BRAKE_WIDTH, BRAKE_HEIGHT, BRAKE_RADIUS, BRAKE_RADIUS);
   m_carParts[carPart::BRAKE_FRONT_RIGHT].addRoundedRect(560, 191, BRAKE_WIDTH, BRAKE_HEIGHT, BRAKE_RADIUS, BRAKE_RADIUS);
   m_carParts[carPart::BRAKE_REAR_LEFT].addRoundedRect(458, 492, BRAKE_WIDTH, BRAKE_HEIGHT, BRAKE_RADIUS, BRAKE_RADIUS);
   m_carParts[carPart::BRAKE_REAR_RIGHT].addRoundedRect(560, 492, BRAKE_WIDTH, BRAKE_HEIGHT, BRAKE_RADIUS, BRAKE_RADIUS);
}


/*******************************************************************************
 * @brief   creates a shape for the engine
 *
 * @param   none
 *
 * @return  none
 *
*******************************************************************************/
void CarShape::createEngine()
{
   m_carParts[carPart::ENGINE].addRect(497, 422, 31, 43);
   m_carParts[carPart::ENGINE].addRect(493, 424, 4, 39);
   m_carParts[carPart::ENGINE].addRect(528, 424, 4, 39);
}


/*******************************************************************************
 * @brief   creates a shape for the frontwing
 *
 * @param   none
 *
 * @return  none
 *
*******************************************************************************/
void CarShape::createFrontwing()
{
   QVector<QPointF> points;

   points.append(QPointF(431, 133));
   points.append(QPointF(431, 133));
   points.append(QPointF(431, 184));
   points.append(QPointF(435, 184));
   points.append(QPointF(451, 176));
   points.append(QPointF(469, 176));
   points.append(QPointF(477, 173));
   points.append(QPointF(493, 157));
   points.append(QPointF(501, 157));
   points.append(QPointF(504, 133));

   m_carParts[carPart::AERO].addPolygon(QPolygonF(points));
   mirrorPoints(CEN_X, &points );
   m_carParts[carPart::AERO].addPolygon(QPolygonF(points));
}


/*******************************************************************************
 * @brief   creates a shapt for the front suspension
 *
 * @param   none
 *
 * @return  none
 *
*******************************************************************************/
void CarShape::createSuspensionFront()
{
   QVector<QPointF> points;

   points.append(QPointF(499, 198));
   points.append(QPointF(465, 206));
   points.append(QPointF(465, 230));
   points.append(QPointF(496, 256));
   points.append(QPointF(498, 242));
   points.append(QPointF(471, 220));
   points.append(QPointF(499, 218));
   points.append(QPointF(499, 210));
   points.append(QPointF(485, 210));
   points.append(QPointF(499, 206));

   m_carParts[carPart::SUSP_FRONT_LEFT].addPolygon(QPolygonF(points));
   mirrorPoints(CEN_X, &points);
   m_carParts[carPart::SUSP_FRONT_RIGHT].addPolygon(QPolygonF(points));
}


/*******************************************************************************
 * @brief   creates a shape for the rear suspension
 *
 * @param   none
 *
 * @return  none
 *
*******************************************************************************/
void CarShape::createSuspensionRear()
{
   QVector<QPointF> points;

   points.append(QPointF(500, 477));
   points.append(QPointF(494, 483));
   points.append(QPointF(494, 484));
   points.append(QPointF(483, 495));
   points.append(QPointF(483, 496));
   points.append(QPointF(472, 507));
   points.append(QPointF(472, 508));
   points.append(QPointF(467, 513));
   points.append(QPointF(465, 513));
   points.append(QPointF(465, 532));
   points.append(QPointF(467, 532));
   points.append(QPointF(467, 529));
   points.append(QPointF(474, 529));
   points.append(QPointF(474, 525));
   points.append(QPointF(470, 525));
   points.append(QPointF(470, 522));
   points.append(QPointF(475, 522));
   points.append(QPointF(475, 519));
   points.append(QPointF(502, 519));
   points.append(QPointF(502, 512));
   points.append(QPointF(470, 518));
   points.append(QPointF(470, 517));
   points.append(QPointF(485, 502));
   points.append(QPointF(485, 501));
   points.append(QPointF(500, 486));

   m_carParts[carPart::SUSP_REAR_LEFT].addPolygon(QPolygonF(points));
   mirrorPoints(CEN_X, &points);
   m_carParts[carPart::SUSP_REAR_RIGHT].addPolygon(QPolygonF(points));
}


/*******************************************************************************
 * @brief   mirrors points on a x-axis
 *
 * @param   xMirror     x-value of the mirror axis
 * @param   *points     adress of the path to mirror
 *
 * @return  none
 *
*******************************************************************************/
void CarShape::mirrorPoints(qreal xMirror, QVector<QPointF> *points)
{
    for(int i = 0; i < points->size(); i++)
    {
        qreal x = points->at(i).x();
        x = (2*xMirror) - x;
        points->operator [](i).setX(x);
    }
}


/*******************************************************************************
 * @brief   draws the shape of the complete car
 *
 * @param   none
 *
 * @return  none
 *
*******************************************************************************/
void CarShape::drawShapeImage()
{
    QPainter paint;

    if(!m_carImage.isNull())
    {
       paint.begin(this);
       paint.drawImage(QRectF(0,0,PIXMAP_WIDTH,PIXMAP_HEIGHT), m_carImage);
       paint.end();
    }
}
