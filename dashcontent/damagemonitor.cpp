#include "damagemonitor.h"
#include <QPainter>
#include <QDebug>
#include <QVector>
#include <QThread>






DamageMonitor::DamageMonitor()
{
   m_config = Config::getInstance();

    for(size_t i = 0; i < sizeof(m_values)/sizeof(TextFrame); i++)
    {
        m_values[i].setParameter(QFont(FONT_FAMILY, FONT_SIZE_TEXT), 5, textPos::RIGHT);
        m_labels[i].setParameter(QFont(FONT_FAMILY, FONT_SIZE_TEXT), LABEL_LETTER_COUNT, textPos::RIGHT);
    }    

    m_values[DMG::STATUS_MSG].setParameter(QFont(FONT_FAMILY, FONT_SIZE_STATUS), -1, textPos::CENTER);

    setLayout();

}




void DamageMonitor::repaintLabels()
{
   for(unsigned int i = 0; i < sizeof(m_labels)/sizeof(TextFrame); i++)
   {
       m_labels[i].drawFrame(this);
   }

   m_labels[DMG::TYRE_FRONT_LEFT].drawText(this,  "TYRE");
   m_labels[DMG::TYRE_FRONT_RIGHT].drawText(this, "TYRE");
   m_labels[DMG::TYRE_REAR_LEFT].drawText(this,   "TYRE");
   m_labels[DMG::TYRE_REAR_RIGHT].drawText(this,  "TYRE");

   m_labels[DMG::SUSP_FRONT_LEFT].drawText(this,  "SUSP");
   m_labels[DMG::SUSP_FRONT_RIGHT].drawText(this, "SUSP");
   m_labels[DMG::SUSP_REAR_LEFT].drawText(this,   "SUSP");
   m_labels[DMG::SUSP_REAR_RIGHT].drawText(this,  "SUSP");

   m_labels[DMG::BRAKE_FRONT_LEFT].drawText(this, "BRAKE");
   m_labels[DMG::BRAKE_FRONT_RIGHT].drawText(this,"BRAKE");
   m_labels[DMG::BRAKE_REAR_LEFT].drawText(this,  "BRAKE");
   m_labels[DMG::BRAKE_REAR_RIGHT].drawText(this, "BRAKE");

   m_labels[DMG::AERO].drawText(this, "AERO");
   m_labels[DMG::ENGINE].drawText(this, "ENG");
}

void DamageMonitor::repaintValues(gameDataStruct data)
{
   for(unsigned int i = 0; i < sizeof(m_values)/sizeof(TextFrame); i++)
   {
       m_values[i].drawFrame(this);
   }

   m_values[DMG::STATUS_MSG].drawText(this, "Damage");
   m_values[DMG::AERO].drawText(this, QString::number(data.damageAero));
   m_values[DMG::ENGINE].drawText(this, QString::number(data.damageEngine));
   m_values[DMG::TYRE_FRONT_LEFT].drawText(this, QString::number(data.damageTyre[eTYRE_FRONT_LEFT]));
   m_values[DMG::TYRE_FRONT_RIGHT].drawText(this, QString::number(data.damageTyre[eTYRE_FRONT_RIGHT]));
   m_values[DMG::TYRE_REAR_LEFT].drawText(this, QString::number(data.damageTyre[eTYRE_REAR_LEFT]));
   m_values[DMG::TYRE_REAR_RIGHT].drawText(this, QString::number(data.damageTyre[eTYRE_REAR_LEFT]));
   m_values[DMG::SUSP_FRONT_LEFT].drawText(this, QString::number(data.damageSuspension[eTYRE_FRONT_LEFT]));
   m_values[DMG::SUSP_FRONT_RIGHT].drawText(this, QString::number(data.damageSuspension[eTYRE_FRONT_RIGHT]));
   m_values[DMG::SUSP_REAR_LEFT].drawText(this, QString::number(data.damageSuspension[eTYRE_REAR_LEFT]));
   m_values[DMG::BRAKE_FRONT_LEFT].drawText(this, QString::number(data.damageSuspension[eTYRE_FRONT_LEFT]));
   m_values[DMG::BRAKE_FRONT_RIGHT].drawText(this, QString::number(data.damageSuspension[eTYRE_FRONT_RIGHT]));
   m_values[DMG::BRAKE_REAR_LEFT].drawText(this, QString::number(data.damageSuspension[eTYRE_REAR_LEFT]));
   m_values[DMG::BRAKE_REAR_RIGHT].drawText(this, QString::number(data.damageSuspension[eTYRE_REAR_RIGHT]));
   m_values[DMG::SUSP_REAR_RIGHT].drawText(this, QString::number(data.damageSuspension[eTYRE_REAR_LEFT]));
}

void DamageMonitor::repaintCarshape(gameDataStruct data)
{
   QColor color;

   m_carshape.drawShapeImage();

   // AERO
   color = getDamageIndicator(data.damageAero);
   m_carshape.colorPart(carPart::AERO, color);

   // ENGINE
   color = getDamageIndicator(data.damageEngine);
   m_carshape.colorPart(carPart::ENGINE, color);

   // TYRE-FRONT-LEFT
   color = getDamageIndicator(data.damageTyre[eTYRE_FRONT_LEFT]);
   m_carshape.colorPart(carPart::TYRE_FRONT_LEFT, color);

   // TYRE-FRONT-RIGHT
   color = getDamageIndicator(data.damageTyre[eTYRE_FRONT_RIGHT]);
   m_carshape.colorPart(carPart::TYRE_FRONT_RIGHT, color);

   // TYRE-REAR-LEFT
   color = getDamageIndicator(data.damageTyre[eTYRE_REAR_LEFT]);
   m_carshape.colorPart(carPart::TYRE_REAR_LEFT, color);

   // TYRE-REAR-RIGHT
   color = getDamageIndicator(data.damageTyre[eTYRE_REAR_RIGHT]);
   m_carshape.colorPart(carPart::TYRE_REAR_RIGHT, color);

   // SUSPENSION-FRONT-LEFT
   color = getDamageIndicator(data.damageSuspension[eTYRE_FRONT_LEFT]);
   m_carshape.colorPart(carPart::SUSP_FRONT_LEFT, color);

   // SUSPENSION-FRONT-RIGHT
   color = getDamageIndicator(data.damageSuspension[eTYRE_FRONT_RIGHT]);
   m_carshape.colorPart(carPart::SUSP_FRONT_RIGHT, color);

   // SUSPENSION-REAR-LEFT
   color = getDamageIndicator(data.damageSuspension[eTYRE_REAR_LEFT]);
   m_carshape.colorPart(carPart::SUSP_REAR_LEFT, color);

   // SUSPENSION-REAR-RIGHT
   color = getDamageIndicator(data.damageSuspension[eTYRE_REAR_RIGHT]);
   m_carshape.colorPart(carPart::SUSP_REAR_RIGHT, color);

   // BRAKE-FRONT-LEFT
   color = getDamageIndicator(data.damageSuspension[eTYRE_FRONT_LEFT]);
   m_carshape.colorPart(carPart::BRAKE_FRONT_LEFT, color);

   // BRAKE-FRONT-RIGHT
   color = getDamageIndicator(data.damageSuspension[eTYRE_FRONT_RIGHT]);
   m_carshape.colorPart(carPart::BRAKE_FRONT_RIGHT, color);

   // BRAKE-REAR-LEFT
   color = getDamageIndicator(data.damageSuspension[eTYRE_REAR_LEFT]);
   m_carshape.colorPart(carPart::BRAKE_REAR_LEFT, color);

   // BRAKE-REAR-RIGHT
   color = getDamageIndicator(data.damageSuspension[eTYRE_REAR_RIGHT]);
   m_carshape.colorPart(carPart::BRAKE_REAR_RIGHT, color);

   QPainter paint;
   paint.begin(this);
   paint.drawPixmap(0, 0, PIXMAP_WIDTH, PIXMAP_HEIGHT, m_carshape);
   paint.end();
}

void DamageMonitor::setLayout()
{
   //STATUS-FRAME
    m_values[DMG::STATUS_MSG].setTop(STATUS_TOP);
    m_values[DMG::STATUS_MSG].setBottom(STATUS_BOT);
    m_values[DMG::STATUS_MSG].setLeft(STATUS_LEFT);
    m_values[DMG::STATUS_MSG].setRight(STATUS_RIGHT);

    // TOP-LEFT
    m_labels[DMG::TYRE_FRONT_LEFT].setOriginTopLeft(MIN_Y, MIN_X);
    m_labels[DMG::BRAKE_FRONT_LEFT].addUnder(&m_labels[DMG::TYRE_FRONT_LEFT]);
    m_labels[DMG::SUSP_FRONT_LEFT].addUnder(&m_labels[DMG::BRAKE_FRONT_LEFT]);

    m_values[DMG::TYRE_FRONT_LEFT].addRightFrom(&m_labels[DMG::TYRE_FRONT_LEFT]);
    m_values[DMG::BRAKE_FRONT_LEFT].addRightFrom(&m_labels[DMG::BRAKE_FRONT_LEFT]);
    m_values[DMG::SUSP_FRONT_LEFT].addRightFrom(&m_labels[DMG::SUSP_FRONT_LEFT]);

    //MID-LEFT
    m_labels[DMG::AERO].setOriginLeftCenter(350, MIN_X);
    m_values[DMG::AERO].addRightFrom(&m_labels[DMG::AERO]);

    // BOTTOM-LEFT
    m_labels[DMG::SUSP_REAR_LEFT].setOriginBotLeft(MAX_Y, MIN_X);
    m_labels[DMG::BRAKE_REAR_LEFT].addAbove(&m_labels[DMG::SUSP_REAR_LEFT]);
    m_labels[DMG::TYRE_REAR_LEFT].addAbove(&m_labels[DMG::BRAKE_REAR_LEFT]);

    m_values[DMG::SUSP_REAR_LEFT].addRightFrom(&m_labels[DMG::SUSP_REAR_LEFT]);
    m_values[DMG::BRAKE_REAR_LEFT].addRightFrom(&m_labels[DMG::BRAKE_REAR_LEFT]);
    m_values[DMG::TYRE_REAR_LEFT].addRightFrom(&m_labels[DMG::TYRE_REAR_LEFT]);

    // TOP-RIGHT
    m_values[DMG::TYRE_FRONT_RIGHT].setOriginTopRight(MIN_Y, MAX_X);
    m_values[DMG::BRAKE_FRONT_RIGHT].addUnder(&m_values[DMG::TYRE_FRONT_RIGHT]);
    m_values[DMG::SUSP_FRONT_RIGHT].addUnder(&m_values[DMG::BRAKE_FRONT_RIGHT]);

    m_labels[DMG::TYRE_FRONT_RIGHT].addLeftFrom(&m_values[DMG::TYRE_FRONT_RIGHT]);
    m_labels[DMG::BRAKE_FRONT_RIGHT].addLeftFrom(&m_values[DMG::BRAKE_FRONT_RIGHT]);
    m_labels[DMG::SUSP_FRONT_RIGHT].addLeftFrom(&m_values[DMG::SUSP_FRONT_RIGHT]);

    //MID-RIGHT
    m_values[DMG::ENGINE].setOriginRightCenter(350, MAX_X);
    m_labels[DMG::ENGINE].addLeftFrom(&m_values[DMG::ENGINE]);

    // BOTTOM-RIGHT
    m_values[DMG::SUSP_REAR_RIGHT].setOriginBotRight(MAX_Y, MAX_X);
    m_values[DMG::BRAKE_REAR_RIGHT].addAbove(&m_values[DMG::SUSP_REAR_RIGHT]);
    m_values[DMG::TYRE_REAR_RIGHT].addAbove(&m_values[DMG::BRAKE_REAR_RIGHT]);

    m_labels[DMG::SUSP_REAR_RIGHT].addLeftFrom(&m_values[DMG::SUSP_REAR_RIGHT]);
    m_labels[DMG::BRAKE_REAR_RIGHT].addLeftFrom(&m_values[DMG::BRAKE_REAR_RIGHT]);
    m_labels[DMG::TYRE_REAR_RIGHT].addLeftFrom(&m_values[DMG::TYRE_REAR_RIGHT]);
}



QColor DamageMonitor::getDamageIndicator(int damage)
{
   QColor colorNoDamage    = Qt::green;
   QColor colorDamageLow   = Qt::yellow;
   QColor colorDamageMid   = QColor(255,130,0);
   QColor colorDamageHigh  = Qt::red;

   int damageLow  = m_config->getValue(CFG_DAMAGE_LOW).toInt();
   int damageMid  = m_config->getValue(CFG_DAMAGE_MID).toInt();
   int damageHigh = m_config->getValue(CFG_DAMAGE_HIGH).toInt();

   if(damage > damageHigh)
   {
      return colorDamageHigh;
   }
   else if(damage > damageMid)
   {
      return colorDamageMid;
   }
   else if(damage > damageLow)
   {
      return colorDamageLow;
   }
   else
   {
      return colorNoDamage;
   }
}


