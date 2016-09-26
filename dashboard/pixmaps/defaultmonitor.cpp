#include "defaultmonitor.h"

#include "settings.h"
#include <QPainter>
#include <QRectF>
//#include "textframe.h"





DefaultMonitor::DefaultMonitor() //: QPixmap(PIXMAP_WIDTH, PIXMAP_HEIGHT)
{

    this->fill(Qt::black);

    //labels = new TextFrame[DES_MAX];
    //values = new TextFrame[DES_MAX];

    for(size_t i = 0; i < sizeof(labels)/sizeof(TextFrame); i++)
    {
        values[i].setParameter(QFont(FONT, FONT_SIZE_TEXT), LABEL_LETTERS, textPos::RIGHT);
    }


    for(size_t i = 0; i < sizeof(values)/sizeof(TextFrame); i++)
    {
        values[i].setParameter(QFont(FONT, FONT_SIZE_TEXT), VALUE_LETTERS, textPos::RIGHT);
    }

    values[GEAR].setParameter(QFont(FONT, FONT_SIZE_GEAR), 1, textPos::CENTER);
    values[STATUS_MSG].setParameter(QFont(FONT, FONT_SIZE_STATUS), -1, textPos::CENTER);




    calculateFrames();
    drawLabels();




}



void DefaultMonitor::calculateFrames()
{
    // STATUS-FRAME
    values[STATUS_MSG].setTop(STATUS_TOP);
    values[STATUS_MSG].setBottom(STATUS_BOT);
    values[STATUS_MSG].setLeft(STATUS_LEFT);
    values[STATUS_MSG].setRight(STATUS_RIGHT);

    // GEAR-FRAME
    values[GEAR].setOriginCenter(PIXMAP_HEIGHT/2, PIXMAP_WIDTH/2);

    // TOP-LEFT
    labels[TEMP_OIL].setOriginTopLeft(MIN_Y, MIN_X);
    labels[TEMP_WAT].addUnder(&labels[TEMP_OIL]);
    labels[PLACEHOLDER1].addUnder(&labels[TEMP_WAT]);

    values[TEMP_OIL].addRightFrom(&labels[TEMP_OIL]);
    values[TEMP_WAT].addRightFrom(&labels[TEMP_WAT]);
    values[PLACEHOLDER1].addRightFrom(&labels[PLACEHOLDER1]);

    // BOTTOM-LEFT
    labels[DELTA_BEHIND].setOriginBotLeft(MAX_Y, MIN_X);
    labels[DELTA_AHEAD].addAbove(&labels[DELTA_BEHIND]);
    labels[POSITION].addAbove(&labels[DELTA_AHEAD]);

    values[DELTA_AHEAD].addRightFrom(&labels[DELTA_AHEAD]);
    values[DELTA_BEHIND].addRightFrom(&labels[DELTA_BEHIND]);
    values[POSITION].addRightFrom(&labels[POSITION]);

    // TOP-RIGHT
    values[LAST_LAP].setOriginTopRight(MIN_Y, MAX_X);
    values[BEST_LAP].addUnder(&values[LAST_LAP]);
    values[DELTA_LAP].addUnder(&values[BEST_LAP]);

    labels[LAST_LAP].addLeftFrom(&values[LAST_LAP]);
    labels[BEST_LAP].addLeftFrom(&values[BEST_LAP]);
    labels[DELTA_LAP].addLeftFrom(&values[DELTA_LAP]);

    // TOP-BOTTOM
    values[DELTA_S3].setOriginBotRight(MAX_Y, MAX_X);
    values[DELTA_S2].addAbove(&values[DELTA_S3]);
    values[DELTA_S1].addAbove(&values[DELTA_S2]);

    labels[DELTA_S1].addLeftFrom(&values[DELTA_S1]);
    labels[DELTA_S2].addLeftFrom(&values[DELTA_S2]);
    labels[DELTA_S3].addLeftFrom(&values[DELTA_S3]);

}

void DefaultMonitor::drawLabels()
{
    for(size_t i = 0; i < sizeof(labels)/sizeof(TextFrame); i++)
    {
        labels[i].drawFrame(this);
    }

    labels[LAST_LAP].drawText(this, "tLast");
    labels[BEST_LAP].drawText(this, "tBest");
    labels[DELTA_LAP].drawText(this, "Delta");

    labels[DELTA_S1].drawText(this, "S1");
    labels[DELTA_S2].drawText(this, "S2");
    labels[DELTA_S3].drawText(this, "S3");

    labels[TEMP_OIL].drawText(this, "TOil");
    labels[TEMP_WAT].drawText(this, "TWat");
    labels[PLACEHOLDER1].drawText(this, "-");

    labels[POSITION].drawText(this, "Pos");
    labels[DELTA_BEHIND].drawText(this, "tBehi");
    labels[DELTA_AHEAD].drawText(this, "tAhea");
}

void DefaultMonitor::drawValues(gameDataStruct data)
{
    for(size_t i = 0; i < sizeof(values)/sizeof(TextFrame); i++)
    {
        values[i].clearArea(this);
        values[i].drawFrame(this);

    }

    values[STATUS_MSG].drawText(this, "No Messages available!", Qt::red);
    values[GEAR].drawText(this, QString::number(data.gear));
    values[LAST_LAP].drawTime(this, data.timeLastLap);
    values[BEST_LAP].drawTime(this, data.timeBestLap);
    values[DELTA_LAP].drawDelta(this, (data.timeLastLap-data.timeBestLap));
    values[DELTA_S1].drawDelta(this, (data.timeCurrentSector1-data.timeFastestSector1));
    values[DELTA_S2].drawDelta(this, (data.timeCurrentSector2-data.timeFastestSector2));
    values[DELTA_S3].drawDelta(this, (data.timeCurrentSector3-data.timeFastestSector3));
    values[TEMP_OIL].drawTemperature(this, data.tempOil, 70, 100);
    values[TEMP_WAT].drawTemperature(this, data.tempWater, 70, 100);
    values[POSITION].drawText(this, QString::number(data.racePosition));
    values[DELTA_AHEAD].drawDelta(this, data.timeSplitAhead);
    values[DELTA_BEHIND].drawDelta(this, data.timeSplitBehind *(-1));
}


