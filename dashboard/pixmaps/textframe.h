#ifndef TEXTFRAME_H
#define TEXTFRAME_H

#include <QRectF>
#include <QPixmap>
#include <QFont>
#include "settings.h"

namespace textPos
{
    enum alignement{
        CENTER,
        LEFT,
        RIGHT
    };
}


class TextFrame : public QRectF
{

private:
    int letterWidth;
    int letterHeight;

    QFont font;
    int letterCount;
    textPos::alignement align;

public:
    TextFrame();


    void setParameter(QFont font, int letterCount, textPos::alignement align);

    void setOriginCenter(qreal y, qreal x);
    void setOriginTopLeft(qreal y, qreal x);
    void setOriginTopRight(qreal y, qreal x);
    void setOriginBotRight(qreal y, qreal x);
    void setOriginBotLeft(qreal y, qreal x);

    void addRightFrom(TextFrame *frame);
    void addLeftFrom(TextFrame *frame);
    void addUnder(TextFrame *frame);
    void addAbove(TextFrame *frame);

    void drawText(QPixmap *target, QString text, QColor color = Qt::white);
    void drawFrame(QPixmap *target);
    void drawTime(QPixmap *target, float msTime, bool isDeltaTime = false);
    void drawDelta(QPixmap *target, float msTime);
    void drawTemperature(QPixmap *target, int temp, int limitLow, int limitHigh);
    void clearArea(QPixmap *target);
    void setOriginLeftCenter(qreal y, qreal x);
    void setOriginRightCenter(qreal y, qreal x);
};

#endif // TEXTFRAME_H

