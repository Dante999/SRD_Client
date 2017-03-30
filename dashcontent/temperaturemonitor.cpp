#include "temperaturemonitor.h"
#include <QPainter>


TemperatureMonitor::TemperatureMonitor()
{
   m_config = Config::getInstance();

    for(size_t i = 0; i < sizeof(m_values)/sizeof(TextFrame); i++)
    {
        m_values[i].setParameter(QFont(FONT_FAMILY, FONT_SIZE_TEXT), 5, textPos::RIGHT);
        m_labels[i].setParameter(QFont(FONT_FAMILY, FONT_SIZE_TEXT), LABEL_LETTER_COUNT, textPos::RIGHT);
    }

    m_values[TEMP::STATUS_MSG].setParameter(QFont(FONT_FAMILY, FONT_SIZE_STATUS), -1, textPos::CENTER);

    setLayout();
}


void TemperatureMonitor::repaintLabels()
{
   for(unsigned int i = 0; i < sizeof(m_labels)/sizeof(TextFrame); i++)
   {
       m_labels[i].drawFrame(this);
   }

   m_labels[TEMP::TYRE_FRONT_LEFT].drawText(this,  "TYRE");
   m_labels[TEMP::TYRE_FRONT_RIGHT].drawText(this, "TYRE");
   m_labels[TEMP::TYRE_REAR_LEFT].drawText(this,   "TYRE");
   m_labels[TEMP::TYRE_REAR_RIGHT].drawText(this,  "TYRE");

   m_labels[TEMP::BRAKE_FRONT_LEFT].drawText(this, "BRAKE");
   m_labels[TEMP::BRAKE_FRONT_RIGHT].drawText(this,"BRAKE");
   m_labels[TEMP::BRAKE_REAR_LEFT].drawText(this,  "BRAKE");
   m_labels[TEMP::BRAKE_REAR_RIGHT].drawText(this, "BRAKE");

   m_labels[TEMP::OIL].drawText(this, "OIL");
   m_labels[TEMP::WATER].drawText(this, "WAT");
}

void TemperatureMonitor::repaintValues(gameDataStruct data)
{
   for(unsigned int i = 0; i < sizeof(m_values)/sizeof(TextFrame); i++)
   {
      m_values[i].clearArea(this);
      m_values[i].drawFrame(this);
   }

   m_values[TEMP::STATUS_MSG].drawText(this, "Temperature");
   m_values[TEMP::OIL].drawText(this, QString::number(data.tempOil));
   m_values[TEMP::WATER].drawText(this, QString::number(data.tempWater));
   m_values[TEMP::TYRE_FRONT_LEFT].drawText(this, QString::number(data.tempTyre[eTYRE_FRONT_LEFT]));
   m_values[TEMP::TYRE_FRONT_RIGHT].drawText(this, QString::number(data.tempTyre[eTYRE_FRONT_RIGHT]));
   m_values[TEMP::TYRE_REAR_LEFT].drawText(this, QString::number(data.tempTyre[eTYRE_REAR_LEFT]));
   m_values[TEMP::TYRE_REAR_RIGHT].drawText(this, QString::number(data.tempTyre[eTYRE_REAR_LEFT]));
   m_values[TEMP::BRAKE_FRONT_LEFT].drawText(this, QString::number(data.tempBrake[eTYRE_FRONT_LEFT]));
   m_values[TEMP::BRAKE_FRONT_RIGHT].drawText(this, QString::number(data.tempBrake[eTYRE_FRONT_RIGHT]));
   m_values[TEMP::BRAKE_REAR_LEFT].drawText(this, QString::number(data.tempBrake[eTYRE_REAR_LEFT]));
   m_values[TEMP::BRAKE_REAR_RIGHT].drawText(this, QString::number(data.tempBrake[eTYRE_REAR_RIGHT]));
}

void TemperatureMonitor::repaintCarshape(gameDataStruct data)
{
   QColor color;
   int limitLow;
   int limitHigh;

   m_carshape.drawShapeImage();

   // ENGINE
   limitLow = m_config->getValue(CFG_OIL_TEMP_COLD).toInt();
   limitHigh = m_config->getValue(CFG_OIL_TEMP_HOT).toInt();
   color = getTempIndicator(data.tempOil, limitLow, limitHigh);
   m_carshape.colorPart(carPart::ENGINE, color);

   // TYRE-FRONT-LEFT
   limitLow = m_config->getValue(CFG_TYRE_TEMP_COLD).toInt();
   limitHigh = m_config->getValue(CFG_TYRE_TEMP_HOT).toInt();
   color = getTempIndicator(data.tempTyre[eTYRE_FRONT_LEFT], limitLow, limitHigh);
   m_carshape.colorPart(carPart::TYRE_FRONT_LEFT, color);

   // TYRE-FRONT-RIGHT
   limitLow = m_config->getValue(CFG_TYRE_TEMP_COLD).toInt();
   limitHigh = m_config->getValue(CFG_TYRE_TEMP_HOT).toInt();
   color = getTempIndicator(data.tempTyre[eTYRE_FRONT_RIGHT], limitLow, limitHigh);
   m_carshape.colorPart(carPart::TYRE_FRONT_RIGHT, color);

   // TYRE-REAR-LEFT
   limitLow = m_config->getValue(CFG_TYRE_TEMP_COLD).toInt();
   limitHigh = m_config->getValue(CFG_TYRE_TEMP_HOT).toInt();
   color = getTempIndicator(data.tempTyre[eTYRE_REAR_LEFT], limitLow, limitHigh);
   m_carshape.colorPart(carPart::TYRE_REAR_LEFT, color);

   // TYRE-REAR-RIGHT
   limitLow = m_config->getValue(CFG_TYRE_TEMP_COLD).toInt();
   limitHigh = m_config->getValue(CFG_TYRE_TEMP_HOT).toInt();
   color = getTempIndicator(data.tempTyre[eTYRE_REAR_RIGHT], limitLow, limitHigh);
   m_carshape.colorPart(carPart::TYRE_REAR_RIGHT, color);


   // BRAKE-FRONT-LEFT
   limitLow = m_config->getValue(CFG_BRAKE_TEMP_COLD).toInt();
   limitHigh = m_config->getValue(CFG_BRAKE_TEMP_HOT).toInt();
   color = getTempIndicator(data.tempTyre[eTYRE_FRONT_LEFT], limitLow, limitHigh);
   m_carshape.colorPart(carPart::BRAKE_FRONT_LEFT, color);

   // BRAKE-FRONT-RIGHT
   limitLow = m_config->getValue(CFG_BRAKE_TEMP_COLD).toInt();
   limitHigh = m_config->getValue(CFG_BRAKE_TEMP_HOT).toInt();
   color = getTempIndicator(data.tempTyre[eTYRE_FRONT_RIGHT], limitLow, limitHigh);
   m_carshape.colorPart(carPart::BRAKE_FRONT_RIGHT, color);

   // BRAKE-REAR-LEFT
   limitLow = m_config->getValue(CFG_BRAKE_TEMP_COLD).toInt();
   limitHigh = m_config->getValue(CFG_BRAKE_TEMP_HOT).toInt();
   color = getTempIndicator(data.tempTyre[eTYRE_REAR_LEFT], limitLow, limitHigh);
   m_carshape.colorPart(carPart::BRAKE_REAR_LEFT, color);

   // BRAKE-REAR-RIGHT
   limitLow = m_config->getValue(CFG_BRAKE_TEMP_COLD).toInt();
   limitHigh = m_config->getValue(CFG_BRAKE_TEMP_HOT).toInt();
   color = getTempIndicator(data.tempTyre[eTYRE_REAR_RIGHT], limitLow, limitHigh);
   m_carshape.colorPart(carPart::BRAKE_REAR_RIGHT, color);


   QPainter paint;
   paint.begin(this);
   paint.drawPixmap(0, 0, PIXMAP_WIDTH, PIXMAP_HEIGHT, m_carshape);
   paint.end();
}

void TemperatureMonitor::setLayout()
{
   //STATUS-FRAME
    m_values[TEMP::STATUS_MSG].setTop(STATUS_TOP);
    m_values[TEMP::STATUS_MSG].setBottom(STATUS_BOT);
    m_values[TEMP::STATUS_MSG].setLeft(STATUS_LEFT);
    m_values[TEMP::STATUS_MSG].setRight(STATUS_RIGHT);

    // TOP-LEFT
    m_labels[TEMP::TYRE_FRONT_LEFT].setOriginTopLeft(MIN_Y, MIN_X);
    m_labels[TEMP::BRAKE_FRONT_LEFT].addUnder(&m_labels[TEMP::TYRE_FRONT_LEFT]);

    m_values[TEMP::TYRE_FRONT_LEFT].addRightFrom(&m_labels[TEMP::TYRE_FRONT_LEFT]);
    m_values[TEMP::BRAKE_FRONT_LEFT].addRightFrom(&m_labels[TEMP::BRAKE_FRONT_LEFT]);


    //MID-LEFT
    m_labels[TEMP::OIL].setOriginLeftCenter(350, MIN_X);
    m_values[TEMP::OIL].addRightFrom(&m_labels[TEMP::OIL]);

    // BOTTOM-LEFT
    m_labels[TEMP::BRAKE_REAR_LEFT].setOriginBotLeft(MAX_Y, MIN_X);
    m_labels[TEMP::TYRE_REAR_LEFT].addAbove(&m_labels[TEMP::BRAKE_REAR_LEFT]);

    m_values[TEMP::BRAKE_REAR_LEFT].addRightFrom(&m_labels[TEMP::BRAKE_REAR_LEFT]);
    m_values[TEMP::TYRE_REAR_LEFT].addRightFrom(&m_labels[TEMP::TYRE_REAR_LEFT]);

    // TOP-RIGHT
    m_values[TEMP::TYRE_FRONT_RIGHT].setOriginTopRight(MIN_Y, MAX_X);
    m_values[TEMP::BRAKE_FRONT_RIGHT].addUnder(&m_values[TEMP::TYRE_FRONT_RIGHT]);

    m_labels[TEMP::TYRE_FRONT_RIGHT].addLeftFrom(&m_values[TEMP::TYRE_FRONT_RIGHT]);
    m_labels[TEMP::BRAKE_FRONT_RIGHT].addLeftFrom(&m_values[TEMP::BRAKE_FRONT_RIGHT]);

    //MID-RIGHT
    m_values[TEMP::WATER].setOriginRightCenter(350, MAX_X);
    m_labels[TEMP::WATER].addLeftFrom(&m_values[TEMP::WATER]);

    // BOTTOM-RIGHT
    m_values[TEMP::BRAKE_REAR_RIGHT].setOriginBotRight(MAX_Y, MAX_X);
    m_values[TEMP::TYRE_REAR_RIGHT].addAbove(&m_values[TEMP::BRAKE_REAR_RIGHT]);

    m_labels[TEMP::BRAKE_REAR_RIGHT].addLeftFrom(&m_values[TEMP::BRAKE_REAR_RIGHT]);
    m_labels[TEMP::TYRE_REAR_RIGHT].addLeftFrom(&m_values[TEMP::TYRE_REAR_RIGHT]);
}



QColor TemperatureMonitor::getTempIndicator(int temperature, int limitLow, int limitHigh)
{
   QColor colorCold    = Qt::darkCyan;
   QColor colorNormal  = Qt::green;
   QColor colorHot     = Qt::red;

   if(temperature > limitHigh)
   {
      return colorHot;
   }
   else if(temperature < limitLow)
   {
      return colorCold;
   }
   else
   {
      return colorNormal;
   }
}



