#ifndef CARSHAPE_H
#define CARSHAPE_H

#include <QImage>
#include <QPixmap>

namespace carPart
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
   QImage m_carImage;
   QPainterPath m_carParts[carPart::PARTS_MAX];

   void mirrorPoints(qreal xMirror, QVector<QPointF> *points);

   void createTyres();
   void createBrakes();
   void createEngine();
   void createFrontwing();
   void createSuspensionFront();
   void createSuspensionRear();

public:
   CarShape();
   void colorPart(carPart::parts carPart, QColor color, qreal opacity = 1);
   void drawShapeImage();

};
#endif // CARSHAPE_H
