#include "textframe.h"

#include <QDebug>
#include <QPainter>

//#define FONT_H  1.25
#define FONT_H  1.5
#define FONT_W  0.75



TextFrame::TextFrame()
{
    font.setFamily("Consolas");
    font.setPointSize(30);
    letterCount = 5;
    align = textPos::LEFT;

    letterWidth = FONT_W * font.pointSize();
    letterHeight = FONT_H * font.pointSize();
}

void TextFrame::setParameter(QFont font, int letterCount, textPos::alignement align)
{
    this->font = font;
    this->letterCount = letterCount;
    this->align = align;

    letterWidth = FONT_W * font.pointSize();
    letterHeight = FONT_H * font.pointSize();
}

void TextFrame::setOriginCenter(qreal y, qreal x)
{
    this->setLeft(x-(letterWidth*letterCount)/2);
    this->setRight(x+(letterWidth*letterCount)/2);
    this->setTop    (y-(letterHeight/2));
    this->setBottom (y+(letterHeight/2));
}

void TextFrame::setOriginLeftCenter(qreal y, qreal x)
{
    this->setLeft(x);
    this->setTop(y-(letterHeight/2));
    this->setRight(x+(letterWidth*letterCount));
    this->setBottom(y+(letterHeight/2));
}

void TextFrame::setOriginRightCenter(qreal y, qreal x)
{
    this->setRight(x);
    this->setTop(y-(letterHeight/2));
    this->setLeft(x-(letterWidth*letterCount));
    this->setBottom(y+(letterHeight/2));
}

void TextFrame::setOriginTopLeft(qreal y, qreal x)
{
    this->setLeft(x);
    this->setTop(y);
    this->setRight(x+(letterWidth*letterCount));
    this->setBottom(y+letterHeight);
}

void TextFrame::setOriginTopRight(qreal y, qreal x)
{
    this->setRight(x);
    this->setTop(y);
    this->setLeft(x-(letterWidth*letterCount));
    this->setBottom(y+letterHeight);
}

void TextFrame::setOriginBotRight(qreal y, qreal x)
{
    this->setRight(x);
    this->setBottom(y);
    this->setLeft(x-(letterWidth*letterCount));
    this->setTop(y-letterHeight);
}

void TextFrame::setOriginBotLeft(qreal y, qreal x)
{
    this->setLeft(x);
    this->setBottom(y);
    this->setRight(x+(letterWidth*letterCount));
    this->setTop(y-letterHeight);
}


void TextFrame::addRightFrom(TextFrame *frame)
{
    this->setBottom(frame->bottom());
    this->setTop(this->bottom() - letterHeight);
    this->setLeft(frame->right() + BORDER_SPACE);
    this->setRight(this->left() + (letterWidth*letterCount));
}

void TextFrame::addLeftFrom(TextFrame *frame)
{
    this->setBottom(frame->bottom());
    this->setTop(this->bottom() - letterHeight);
    this->setRight(frame->left() - BORDER_SPACE);
    this->setLeft(this->right() - (letterWidth*letterCount));
}

void TextFrame::addUnder(TextFrame *frame)
{
    this->setLeft(frame->left());
    this->setRight(this->left() + (letterWidth*letterCount));
    this->setTop(frame->bottom() + BORDER_SPACE);
    this->setBottom(this->top() + letterHeight);
}

void TextFrame::addAbove(TextFrame *frame)
{
    this->setLeft(frame->left());
    this->setRight(this->left() + (letterWidth*letterCount));
    this->setBottom(frame->top() - BORDER_SPACE);
    this->setTop(this->bottom() - letterHeight);
}

void TextFrame::drawText(QPixmap *target, QString text, QColor color)
{
    QPainter p(target);

    p.setPen(color);
    p.setFont(font);


    switch(align)
    {
        case textPos::LEFT:     p.drawText(this->toRect(), Qt::AlignLeft|Qt::AlignVCenter, text);
                                break;
        case textPos::CENTER:     p.drawText(this->toRect(), Qt::AlignCenter, text);
                                break;
        case textPos::RIGHT:     p.drawText(this->toRect(), Qt::AlignRight|Qt::AlignVCenter, text);
                                break;
    }

}

void TextFrame::drawFrame(QPixmap *target)
{
    QPainter p(target);
    p.setPen(Qt::white);
    p.drawRect(this->toRect());

}

void TextFrame::drawTime(QPixmap *target, float msTime, bool isDeltaTime)
{


    QPainter p(target);
    p.setPen(Qt::white);
    p.setFont(font);


    QString time;

    if(msTime < 0)
    {
        msTime = msTime * (-1);

        if(isDeltaTime)
        {
            time = "-";
            p.setPen(Qt::green);
        }
    }
    else
    {

        if(isDeltaTime)
        {
            time = "+";
            p.setPen(Qt::red);
        }
    }

    int min = msTime/60;
    int sec = msTime - min*60;
    //int ttt = (msTime+0.0005)*1000;
    int ttt = msTime*1000;

    ttt = ttt%1000;




    time += QString("%1:%2.%3") .arg(min, 2, 10, QChar('0'))
                                .arg(sec, 2, 10, QChar('0'))
                                .arg(ttt, 3, 10, QChar('0'));

    p.drawText(this->toRect(), Qt::AlignRight|Qt::AlignVCenter, time);





}

void TextFrame::drawDelta(QPixmap *target, float msTime)
{
    QString deltaTime = "";
    QPainter p(target);

    p.setPen(Qt::white);
    p.setFont(font);

    if(msTime < 0)
    {
        msTime = msTime * (-1);
        deltaTime = "-";
        p.setPen(Qt::green);
    }
    else
    {
        deltaTime = "+";
        p.setPen(Qt::red);
    }

    int sec = msTime;

    int ttt = (msTime+0.0005)*1000;
    ttt = ttt%1000;

    deltaTime += QString("%1.%2")    .arg(sec, 2, 10, QChar('0'))
                                .arg(ttt, 3, 10, QChar('0'));

    p.drawText(this->toRect(), Qt::AlignRight|Qt::AlignVCenter, deltaTime);



}

void TextFrame::drawTemperature(QPixmap *target, int temp, int limitLow, int limitHigh)
{
    QPainter p(target);
    p.setPen(Qt::green);
    p.setFont(font);

    if      ( temp < limitLow)  p.setPen(Qt::blue);
    else if ( temp > limitHigh) p.setPen(Qt::red);

    QString temperature;

    temperature = QString::number(temp);
    temperature += " °C";

    p.drawText(this->toRect(), Qt::AlignRight|Qt::AlignVCenter, temperature);
}

void TextFrame::clearArea(QPixmap *target)
{
    QPainter p(target);

    p.fillRect(this->toRect(), Qt::black);
}


