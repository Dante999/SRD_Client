#ifndef TEXTFRAME_H
#define TEXTFRAME_H

#include <QRectF>
#include <QPixmap>
#include <QFont>
#include "dashboardcontent.h"

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
    int m_letterWidth;
    int m_letterHeight;

    QFont m_font;
    int m_letterCount;
    textPos::alignement m_align;

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
    void drawFrame(QPixmap *target, QColor borderColor = Qt::white);
    void drawTime(QPixmap *target, float msTime, QColor color = Qt::white);
    void drawDelta(QPixmap *target, float msTime);
    void drawTemperature(QPixmap *target, int temp, QColor color = Qt::white);
    void clearArea(QPixmap *target, QColor fillColor = Qt::black);
    void setOriginLeftCenter(qreal y, qreal x);
    void setOriginRightCenter(qreal y, qreal x);
};

#endif // TEXTFRAME_H
