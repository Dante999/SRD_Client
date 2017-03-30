#include "defaultmonitor.h"


DefaultMonitor::DefaultMonitor()
{
   this->fill(Qt::black);

   for(size_t i = 0; i < sizeof(m_labels)/sizeof(TextFrame); i++)
   {
     m_labels[i].setParameter(QFont(FONT_FAMILY, FONT_SIZE_TEXT), LABEL_LETTER_COUNT, textPos::RIGHT);
     m_values[i].setParameter(QFont(FONT_FAMILY, FONT_SIZE_TEXT), VALUE_LETTER_COUNT, textPos::RIGHT);
   }

   m_values[GEAR].setParameter(QFont(FONT_FAMILY, FONT_SIZE_GEAR), 1, textPos::CENTER);
   m_values[STATUS_MSG].setParameter(QFont(FONT_FAMILY, FONT_SIZE_STATUS), -1, textPos::CENTER);

   setLayout();
}



void DefaultMonitor::setLayout()
{
   // STATUS-FRAME
   m_values[STATUS_MSG].setTop(STATUS_TOP);
   m_values[STATUS_MSG].setBottom(STATUS_BOT);
   m_values[STATUS_MSG].setLeft(STATUS_LEFT);
   m_values[STATUS_MSG].setRight(STATUS_RIGHT);

   // GEAR-FRAME
   m_values[GEAR].setOriginCenter(PIXMAP_HEIGHT/2, PIXMAP_WIDTH/2);

   // TOP-LEFT
   m_labels[TEMP_OIL].setOriginTopLeft(MIN_Y, MIN_X);
   m_labels[TEMP_WAT].addUnder(&m_labels[TEMP_OIL]);
   m_labels[PLACEHOLDER1].addUnder(&m_labels[TEMP_WAT]);

   m_values[TEMP_OIL].addRightFrom(&m_labels[TEMP_OIL]);
   m_values[TEMP_WAT].addRightFrom(&m_labels[TEMP_WAT]);
   m_values[PLACEHOLDER1].addRightFrom(&m_labels[PLACEHOLDER1]);

   // BOTTOM-LEFT
   m_labels[DELTA_BEHIND].setOriginBotLeft(MAX_Y, MIN_X);
   m_labels[DELTA_AHEAD].addAbove(&m_labels[DELTA_BEHIND]);
   m_labels[POSITION].addAbove(&m_labels[DELTA_AHEAD]);

   m_values[DELTA_AHEAD].addRightFrom(&m_labels[DELTA_AHEAD]);
   m_values[DELTA_BEHIND].addRightFrom(&m_labels[DELTA_BEHIND]);
   m_values[POSITION].addRightFrom(&m_labels[POSITION]);

   // TOP-RIGHT
   m_values[LAST_LAP].setOriginTopRight(MIN_Y, MAX_X);
   m_values[BEST_LAP].addUnder(&m_values[LAST_LAP]);
   m_values[DELTA_LAP].addUnder(&m_values[BEST_LAP]);

   m_labels[LAST_LAP].addLeftFrom(&m_values[LAST_LAP]);
   m_labels[BEST_LAP].addLeftFrom(&m_values[BEST_LAP]);
   m_labels[DELTA_LAP].addLeftFrom(&m_values[DELTA_LAP]);

   // TOP-BOTTOM
   m_values[DELTA_S3].setOriginBotRight(MAX_Y, MAX_X);
   m_values[DELTA_S2].addAbove(&m_values[DELTA_S3]);
   m_values[DELTA_S1].addAbove(&m_values[DELTA_S2]);

   m_labels[DELTA_S1].addLeftFrom(&m_values[DELTA_S1]);
   m_labels[DELTA_S2].addLeftFrom(&m_values[DELTA_S2]);
   m_labels[DELTA_S3].addLeftFrom(&m_values[DELTA_S3]);
}

void DefaultMonitor::repaintLabels()
{
   for(size_t i = 0; i < sizeof(m_labels)/sizeof(TextFrame); i++)
   {
       m_labels[i].drawFrame(this);
   }

   m_labels[LAST_LAP].drawText(this, "tLast");
   m_labels[BEST_LAP].drawText(this, "tBest");
   m_labels[DELTA_LAP].drawText(this, "Delta");

   m_labels[DELTA_S1].drawText(this, "S1");
   m_labels[DELTA_S2].drawText(this, "S2");
   m_labels[DELTA_S3].drawText(this, "S3");

   m_labels[TEMP_OIL].drawText(this, "TOil");
   m_labels[TEMP_WAT].drawText(this, "TWat");
   m_labels[PLACEHOLDER1].drawText(this, "-");

   m_labels[POSITION].drawText(this, "Pos");
   m_labels[DELTA_BEHIND].drawText(this, "tBehi");
   m_labels[DELTA_AHEAD].drawText(this, "tAhea");
}

void DefaultMonitor::repaintValues(gameDataStruct data)
{
   for(size_t i = 0; i < sizeof(m_values)/sizeof(TextFrame); i++)
   {
      m_values[i].clearArea(this);
      m_values[i].drawFrame(this);
   }

   m_values[STATUS_MSG].drawText(this, "Overview");
   m_values[LAST_LAP].drawTime(this, data.timeLastLap);
   m_values[BEST_LAP].drawTime(this, data.timeBestLap);
   m_values[DELTA_LAP].drawDelta(this, (data.timeLastLap-data.timeBestLap));
   m_values[DELTA_S1].drawDelta(this, (data.timeCurrentSector1-data.timeFastestSector1));
   m_values[DELTA_S2].drawDelta(this, (data.timeCurrentSector2-data.timeFastestSector2));
   m_values[DELTA_S3].drawDelta(this, (data.timeCurrentSector3-data.timeFastestSector3));
   m_values[TEMP_OIL].drawTemperature(this, data.tempOil, Qt::white);
   m_values[TEMP_WAT].drawTemperature(this, data.tempWater, Qt::white);
   m_values[POSITION].drawText(this, QString::number(data.racePosition));
   m_values[DELTA_AHEAD].drawDelta(this, data.timeSplitAhead);
   m_values[DELTA_BEHIND].drawDelta(this, data.timeSplitBehind *(-1));


   if(data.gear == -1)
   {
      m_values[GEAR].drawText(this, "R");
   }
   else
   {
      m_values[GEAR].drawText(this, QString::number(data.gear));
   }
}

void DefaultMonitor::repaintCarshape(gameDataStruct data)
{
   // no carshape used
}


