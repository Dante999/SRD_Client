#include "carshape.h"

#include <QDebug>
#include <QPainter>



#define CAR_IMAGE_X_CENTER  512

#define TYRE_WIDTH      26
#define TYRE_HEIGHT     61
#define TYRE_RADIUS     4

#define BRAKE_WIDTH     7
#define BRAKE_HEIGHT    53
#define BRAKE_RADIUS    2


CarShape::CarShape() : QPixmap(PIXMAP_WIDTH, PIXMAP_HEIGHT)
{
    if( carImage.load("img//carframe.png") == false)
    {
        qDebug() << "can't load image carshape!";
    }

    drawShapeImage();
    calculateShapes();
}


void CarShape::calculateShapes()
{
    QVector<QPointF> points;

    // TYRES
    dmgParts[shape::TYRE_FRONT_LEFT].addRoundedRect(431, 188, TYRE_WIDTH, TYRE_HEIGHT, TYRE_RADIUS, TYRE_RADIUS);
    dmgParts[shape::TYRE_FRONT_RIGHT].addRoundedRect(568, 188, TYRE_WIDTH, TYRE_HEIGHT, TYRE_RADIUS, TYRE_RADIUS);
    dmgParts[shape::TYRE_REAR_LEFT].addRoundedRect(431, 488, TYRE_WIDTH, TYRE_HEIGHT, TYRE_RADIUS, TYRE_RADIUS);
    dmgParts[shape::TYRE_REAR_RIGHT].addRoundedRect(568, 488, TYRE_WIDTH, TYRE_HEIGHT, TYRE_RADIUS, TYRE_RADIUS);

    // BRAKES
    dmgParts[shape::BRAKE_FRONT_LEFT].addRoundedRect(458, 191, BRAKE_WIDTH, BRAKE_HEIGHT, BRAKE_RADIUS, BRAKE_RADIUS);
    dmgParts[shape::BRAKE_FRONT_RIGHT].addRoundedRect(560, 191, BRAKE_WIDTH, BRAKE_HEIGHT, BRAKE_RADIUS, BRAKE_RADIUS);
    dmgParts[shape::BRAKE_REAR_LEFT].addRoundedRect(458, 492, BRAKE_WIDTH, BRAKE_HEIGHT, BRAKE_RADIUS, BRAKE_RADIUS);
    dmgParts[shape::BRAKE_REAR_RIGHT].addRoundedRect(560, 492, BRAKE_WIDTH, BRAKE_HEIGHT, BRAKE_RADIUS, BRAKE_RADIUS);

    // ENGINE
    dmgParts[shape::ENGINE].addRect(497, 422, 31, 43);
    dmgParts[shape::ENGINE].addRect(493, 424, 4, 39);
    dmgParts[shape::ENGINE].addRect(528, 424, 4, 39);

    // AERO
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

    dmgParts[shape::AERO].addPolygon(QPolygonF(points));
    mirrorPoints(CAR_IMAGE_X_CENTER, &points );
    dmgParts[shape::AERO].addPolygon(QPolygonF(points));

    // SUSPENSION FRONT
    points.clear();
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

    dmgParts[shape::SUSP_FRONT_LEFT].addPolygon(QPolygonF(points));
    mirrorPoints(CAR_IMAGE_X_CENTER, &points);
    dmgParts[shape::SUSP_FRONT_RIGHT].addPolygon(QPolygonF(points));

    // SUSPENSION REAR
    points.clear();
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

    dmgParts[shape::SUSP_REAR_LEFT].addPolygon(QPolygonF(points));
    mirrorPoints(CAR_IMAGE_X_CENTER, &points);
    dmgParts[shape::SUSP_REAR_RIGHT].addPolygon(QPolygonF(points));
}






void CarShape::mirrorPoints(qreal xMirror, QVector<QPointF> *points)
{
    for(int i = 0; i < points->size(); i++)
    {
        qreal x = points->at(i).x();        
        x = (2*xMirror) - x;
        points->operator [](i).setX(x);
    }
}



void CarShape::drawDamage(shape::parts carPart, int percent)
{
    QPainter paint;

    //if(percent < 0) percent = 0;
    //else if(percent > 100) percent = 100;

    paint.begin(this);
    paint.setOpacity((qreal)percent/100);
    paint.fillPath(dmgParts[carPart], QBrush(Qt::red));
    paint.end();
}

void CarShape::drawShapeImage()
{
    QPainter paint;

    if(carImage.isNull() == true) return;

    paint.begin(this);
    paint.drawImage(QRectF(0,0,PIXMAP_WIDTH,PIXMAP_HEIGHT), carImage);
    paint.end();
}
