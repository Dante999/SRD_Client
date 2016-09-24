#ifndef CARSHAPE_H
#define CARSHAPE_H


#include <QPixmap>
#include "settings.h"


namespace shape
{
    enum parts
    {
        AERO,
        ENGINE,
        TYRE_FRONT_LEFT,
        TYRE_FRONT_RIGHT,
        TYRE_REAR_LEFT,
        TYRE_REAR_RIGHT,
        BRAKE_FRONT_LEFT,
        BRAKE_FRONT_RIGHT,
        BRAKE_REAR_LEFT,
        BRAKE_REAR_RIGHT,
        SUSP_FRONT_LEFT,
        SUSP_FRONT_RIGHT,
        SUSP_REAR_LEFT,
        SUSP_REAR_RIGHT,
        //-----
        PARTS_MAX
    };
}



class CarShape : public QPixmap
{

private:

    QImage carImage;
    QPainterPath dmgParts[shape::PARTS_MAX];

    void calculateShapes();
    void mirrorPoints(qreal xMirror, QVector<QPointF> *points);

public:

    CarShape();

    void drawDamage(shape::parts carPart, int percent);
    void drawShapeImage();
};

#endif // CARSHAPE_H
