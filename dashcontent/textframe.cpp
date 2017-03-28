#include "textframe.h"

#include <QDebug>
#include <QPainter>

#define FONT_H  1.5
#define FONT_W  0.75

TextFrame::TextFrame()
{
    m_font.setFamily("Consolas");
    m_font.setPointSize(30);
    m_letterCount = 5;
    m_align = textPos::LEFT;

    m_letterWidth = FONT_W * m_font.pointSize();
    m_letterHeight = FONT_H * m_font.pointSize();
}

void TextFrame::setParameter(QFont font, int letterCount, textPos::alignement align)
{
    m_font = font;
    m_letterCount = letterCount;
    m_align = align;

    m_letterWidth = FONT_W * font.pointSize();
    m_letterHeight = FONT_H * font.pointSize();
}

void TextFrame::setOriginCenter(qreal y, qreal x)
{
    this->setLeft(x-(m_letterWidth*m_letterCount)/2);
    this->setRight(x+(m_letterWidth*m_letterCount)/2);
    this->setTop    (y-(m_letterHeight/2));
    this->setBottom (y+(m_letterHeight/2));
}

void TextFrame::setOriginLeftCenter(qreal y, qreal x)
{

    this->setLeft(x);
    this->setTop(y-(m_letterHeight/2));
    this->setRight(x+(m_letterWidth*m_letterCount));
    this->setBottom(y+(m_letterHeight/2));
}

void TextFrame::setOriginRightCenter(qreal y, qreal x)
{
    this->setRight(x);
    this->setTop(y-(m_letterHeight/2));
    this->setLeft(x-(m_letterWidth*m_letterCount));
    this->setBottom(y+(m_letterHeight/2));
}

void TextFrame::setOriginTopLeft(qreal y, qreal x)
{
    this->setLeft(x);
    this->setTop(y);
    this->setRight(x+(m_letterWidth*m_letterCount));
    this->setBottom(y+m_letterHeight);
}

void TextFrame::setOriginTopRight(qreal y, qreal x)
{
    this->setRight(x);
    this->setTop(y);
    this->setLeft(x-(m_letterWidth*m_letterCount));
    this->setBottom(y+m_letterHeight);
}

void TextFrame::setOriginBotRight(qreal y, qreal x)
{
    this->setRight(x);
    this->setBottom(y);
    this->setLeft(x-(m_letterWidth*m_letterCount));
    this->setTop(y-m_letterHeight);
}

void TextFrame::setOriginBotLeft(qreal y, qreal x)
{
    this->setLeft(x);
    this->setBottom(y);
    this->setRight(x+(m_letterWidth*m_letterCount));
    this->setTop(y-m_letterHeight);
}


void TextFrame::addRightFrom(TextFrame *frame)
{
    this->setBottom(frame->bottom());
    this->setTop(this->bottom() - m_letterHeight);
    this->setLeft(frame->right() + BORDER_SPACE);
    this->setRight(this->left() + (m_letterWidth*m_letterCount));
}

void TextFrame::addLeftFrom(TextFrame *frame)
{
    this->setBottom(frame->bottom());
    this->setTop(this->bottom() - m_letterHeight);
    this->setRight(frame->left() - BORDER_SPACE);
    this->setLeft(this->right() - (m_letterWidth*m_letterCount));
}

void TextFrame::addUnder(TextFrame *frame)
{
    this->setLeft(frame->left());
    this->setRight(this->left() + (m_letterWidth*m_letterCount));
    this->setTop(frame->bottom() + BORDER_SPACE);
    this->setBottom(this->top() + m_letterHeight);
}

void TextFrame::addAbove(TextFrame *frame)
{
    this->setLeft(frame->left());
    this->setRight(this->left() + (m_letterWidth*m_letterCount));
    this->setBottom(frame->top() - BORDER_SPACE);
    this->setTop(this->bottom() - m_letterHeight);
}

void TextFrame::drawText(QPixmap *target, QString text, QColor color)
{
    QPainter p(target);

    p.setPen(color);
    p.setFont(m_font);


    switch(m_align)
    {

    case textPos::LEFT:
        p.drawText(this->toRect(), Qt::AlignLeft|Qt::AlignVCenter, text);
        break;

    case textPos::CENTER:
        p.drawText(this->toRect(), Qt::AlignCenter, text);
        break;

    case textPos::RIGHT:
        p.drawText(this->toRect(), Qt::AlignRight|Qt::AlignVCenter, text);
        break;
    }

}

void TextFrame::drawFrame(QPixmap *target, QColor borderColor)
{
    QPainter p(target);
    p.setPen(borderColor);
    p.drawRect(this->toRect());

}

void TextFrame::drawTime(QPixmap *target, float msTime, QColor color)
{
    QPainter p(target);
    p.setPen(color);
    p.setFont(m_font);

    QString time;

    int min = msTime/60;
    int sec = msTime - min*60;
    int ttt = msTime*1000;
    ttt = ttt%1000;

    time += QString("%1:%2.%3") .arg(min, 2, 10, QChar('0'))
                                .arg(sec, 2, 10, QChar('0'))
                                .arg(ttt, 3, 10, QChar('0'));

    p.drawText(this->toRect(), Qt::AlignRight|Qt::AlignVCenter, time);
}

void TextFrame::drawDelta(QPixmap *target, float msTime)
{
    QPainter p(target);
    p.setPen(Qt::white);
    p.setFont(m_font);

    QString deltaTime = "";

    if(msTime < 0)
    {
        msTime = msTime * (-1);
        deltaTime = "-";
        p.setPen(Qt::green);
    }
    else if(msTime > 0)
    {
        deltaTime = "+";
        p.setPen(Qt::red);
    }
    else
    {
       deltaTime = " ";
       p.setPen(Qt::white);
    }

    int sec = msTime;

    int ttt = (msTime+0.0005)*1000;
    ttt = ttt%1000;

    deltaTime += QString("%1.%2").arg(sec, 2, 10, QChar('0'))
                                 .arg(ttt, 3, 10, QChar('0'));

    p.drawText(this->toRect(), Qt::AlignRight|Qt::AlignVCenter, deltaTime);
}


void TextFrame::drawTemperature(QPixmap *target, int temp, QColor color)
{
    QPainter p(target);
    QString temperature;

    p.setPen(color);
    p.setFont(m_font);        

    temperature = QString::number(temp);
    temperature += " °C";

    p.drawText(this->toRect(), Qt::AlignRight|Qt::AlignVCenter, temperature);
}

void TextFrame::clearArea(QPixmap *target, QColor fillColor)
{
    QPainter p(target);

    p.fillRect(this->toRect(), fillColor);
}


