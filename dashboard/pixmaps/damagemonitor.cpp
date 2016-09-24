#include "damagemonitor.h"
#include "settings.h"
#include <QPainter>
#include <QDebug>
#include <QVector>
#include <QThread>






DamageMonitor::DamageMonitor()
{

    refreshCarshape();


    for(size_t i = 0; i < sizeof(values)/sizeof(TextFrame); i++)
    {
        values[i].setParameter(QFont(FONT, FONT_SIZE_TEXT), 5, textPos::RIGHT);
    }

    for(size_t i = 0; i < sizeof(labels)/sizeof(TextFrame); i++)
    {
        labels[i].setParameter(QFont(FONT, FONT_SIZE_TEXT), LABEL_LETTERS, textPos::RIGHT);
    }

    values[DMG::STATUS_MSG].setParameter(QFont(FONT, FONT_SIZE_STATUS), -1, textPos::CENTER);

    /*
    values[DMG::TYRE_FRONT_LEFT].setParameter(QFont(FONT, FONT_SIZE_TEXT*1.5), VALUE_LETTERS, textPos::RIGHT);
    values[DMG::TYRE_FRONT_LEFT].setParameter(QFont(FONT, FONT_SIZE_TEXT*1.5), VALUE_LETTERS, textPos::RIGHT);
    values[DMG::TYRE_FRONT_LEFT].setParameter(QFont(FONT, FONT_SIZE_TEXT*1.5), VALUE_LETTERS, textPos::RIGHT);
    values[DMG::TYRE_FRONT_LEFT].setParameter(QFont(FONT, FONT_SIZE_TEXT*1.5), VALUE_LETTERS, textPos::RIGHT);
    */

    calculateFrames();
    drawLabels();
}




void DamageMonitor::calculateFrames()
{
    values[DMG::STATUS_MSG].setTop(STATUS_TOP);
    values[DMG::STATUS_MSG].setBottom(STATUS_BOT);
    values[DMG::STATUS_MSG].setLeft(STATUS_LEFT);
    values[DMG::STATUS_MSG].setRight(STATUS_RIGHT);

    labels[DMG::AERO].setOriginLeftCenter(350, MIN_X);
    values[DMG::AERO].addRightFrom(&labels[DMG::AERO]);

    values[DMG::ENGINE].setOriginRightCenter(350, MAX_X);
    labels[DMG::ENGINE].addLeftFrom(&values[DMG::ENGINE]);

    // TOP-LEFT
    labels[DMG::TYRE_FRONT_LEFT].setOriginTopLeft(MIN_Y, MIN_X);
    labels[DMG::BRAKE_FRONT_LEFT].addUnder(&labels[DMG::TYRE_FRONT_LEFT]);
    labels[DMG::SUSP_FRONT_LEFT].addUnder(&labels[DMG::BRAKE_FRONT_LEFT]);

    values[DMG::TYRE_FRONT_LEFT].addRightFrom(&labels[DMG::TYRE_FRONT_LEFT]);
    values[DMG::BRAKE_FRONT_LEFT].addRightFrom(&labels[DMG::BRAKE_FRONT_LEFT]);
    values[DMG::SUSP_FRONT_LEFT].addRightFrom(&labels[DMG::SUSP_FRONT_LEFT]);

    // BOTTOM-LEFT
    labels[DMG::SUSP_REAR_LEFT].setOriginBotLeft(MAX_Y, MIN_X);
    labels[DMG::BRAKE_REAR_LEFT].addAbove(&labels[DMG::SUSP_REAR_LEFT]);
    labels[DMG::TYRE_REAR_LEFT].addAbove(&labels[DMG::BRAKE_REAR_LEFT]);

    values[DMG::SUSP_REAR_LEFT].addRightFrom(&labels[DMG::SUSP_REAR_LEFT]);
    values[DMG::BRAKE_REAR_LEFT].addRightFrom(&labels[DMG::BRAKE_REAR_LEFT]);
    values[DMG::TYRE_REAR_LEFT].addRightFrom(&labels[DMG::TYRE_REAR_LEFT]);

    // TOP-RIGHT
    values[DMG::TYRE_FRONT_RIGHT].setOriginTopRight(MIN_Y, MAX_X);
    values[DMG::BRAKE_FRONT_RIGHT].addUnder(&values[DMG::TYRE_FRONT_RIGHT]);
    values[DMG::SUSP_FRONT_RIGHT].addUnder(&values[DMG::BRAKE_FRONT_RIGHT]);

    labels[DMG::TYRE_FRONT_RIGHT].addLeftFrom(&values[DMG::TYRE_FRONT_RIGHT]);
    labels[DMG::BRAKE_FRONT_RIGHT].addLeftFrom(&values[DMG::BRAKE_FRONT_RIGHT]);
    labels[DMG::SUSP_FRONT_RIGHT].addLeftFrom(&values[DMG::SUSP_FRONT_RIGHT]);

    // BOTTOM-RIGHT
    values[DMG::SUSP_REAR_RIGHT].setOriginBotRight(MAX_Y, MAX_X);
    values[DMG::BRAKE_REAR_RIGHT].addAbove(&values[DMG::SUSP_REAR_RIGHT]);
    values[DMG::TYRE_REAR_RIGHT].addAbove(&values[DMG::BRAKE_REAR_RIGHT]);

    labels[DMG::SUSP_REAR_RIGHT].addLeftFrom(&values[DMG::SUSP_REAR_RIGHT]);
    labels[DMG::BRAKE_REAR_RIGHT].addLeftFrom(&values[DMG::BRAKE_REAR_RIGHT]);
    labels[DMG::TYRE_REAR_RIGHT].addLeftFrom(&values[DMG::TYRE_REAR_RIGHT]);
}

void DamageMonitor::drawLabels()
{
    for(unsigned int i = 0; i < sizeof(labels)/sizeof(TextFrame); i++)
    {
        labels[i].drawFrame(this);
    }

    labels[DMG::TYRE_FRONT_LEFT].drawText(this, "TYRE");
    labels[DMG::TYRE_FRONT_RIGHT].drawText(this, "TYRE");
    labels[DMG::TYRE_REAR_LEFT].drawText(this, "TYRE");
    labels[DMG::TYRE_REAR_RIGHT].drawText(this, "TYRE");

    labels[DMG::SUSP_FRONT_LEFT].drawText(this, "SUSP");
    labels[DMG::SUSP_FRONT_RIGHT].drawText(this, "SUSP");
    labels[DMG::SUSP_REAR_LEFT].drawText(this, "SUSP");
    labels[DMG::SUSP_REAR_RIGHT].drawText(this, "SUSP");

    labels[DMG::BRAKE_FRONT_LEFT].drawText(this, "BRAKE");
    labels[DMG::BRAKE_FRONT_RIGHT].drawText(this, "BRAKE");
    labels[DMG::BRAKE_REAR_LEFT].drawText(this, "BRAKE");
    labels[DMG::BRAKE_REAR_RIGHT].drawText(this, "BRAKE");

    labels[DMG::AERO].drawText(this, "AERO");
    labels[DMG::ENGINE].drawText(this, "ENG");


}



void DamageMonitor::drawValues(clientDataStruct data)
{    
    carshape.drawShapeImage();

    carshape.drawDamage(shape::TYRE_FRONT_LEFT, data.damageTyre[eTYRE_FRONT_LEFT]);
    carshape.drawDamage(shape::TYRE_FRONT_RIGHT, data.damageTyre[eTYRE_FRONT_RIGHT]);
    carshape.drawDamage(shape::TYRE_REAR_LEFT, data.damageTyre[eTYRE_REAR_LEFT]);
    carshape.drawDamage(shape::TYRE_REAR_RIGHT, data.damageTyre[eTYRE_REAR_RIGHT]);

    carshape.drawDamage(shape::SUSP_FRONT_LEFT, data.damageSuspension[eTYRE_FRONT_LEFT]);
    carshape.drawDamage(shape::SUSP_FRONT_RIGHT, data.damageSuspension[eTYRE_FRONT_RIGHT]);
    carshape.drawDamage(shape::SUSP_REAR_LEFT, data.damageSuspension[eTYRE_REAR_LEFT]);
    carshape.drawDamage(shape::SUSP_REAR_RIGHT, data.damageSuspension[eTYRE_REAR_RIGHT]);

    carshape.drawDamage(shape::BRAKE_FRONT_LEFT, data.damageBrake[eTYRE_FRONT_LEFT]);
    carshape.drawDamage(shape::BRAKE_FRONT_RIGHT, data.damageBrake[eTYRE_FRONT_RIGHT]);
    carshape.drawDamage(shape::BRAKE_REAR_LEFT, data.damageBrake[eTYRE_REAR_LEFT]);
    carshape.drawDamage(shape::BRAKE_REAR_RIGHT, data.damageBrake[eTYRE_REAR_RIGHT]);

    carshape.drawDamage(shape::ENGINE, data.damageEngine);
    carshape.drawDamage(shape::AERO, data.damageAero);

    refreshCarshape();
    drawLabels();


    // Values as numbers

    for(unsigned int i = 0; i < sizeof(values)/sizeof(TextFrame); i++)
    {
        //values[i].clearArea(this);
        values[i].drawFrame(this);
    }

    values[DMG::STATUS_MSG].drawText(this, "No Messages available!", Qt::red);

    values[DMG::AERO].drawText(this, QString::number(data.damageAero));
    values[DMG::ENGINE].drawText(this, QString::number(data.damageEngine));

    values[DMG::TYRE_FRONT_LEFT].drawText(this, QString::number(data.damageTyre[eTYRE_FRONT_LEFT]));
    values[DMG::TYRE_FRONT_RIGHT].drawText(this, QString::number(data.damageTyre[eTYRE_FRONT_RIGHT]));
    values[DMG::TYRE_REAR_LEFT].drawText(this, QString::number(data.damageTyre[eTYRE_REAR_LEFT]));
    values[DMG::TYRE_REAR_RIGHT].drawText(this, QString::number(data.damageTyre[eTYRE_REAR_LEFT]));

    values[DMG::BRAKE_FRONT_LEFT].drawText(this, QString::number(data.damageBrake[eTYRE_FRONT_LEFT]));
    values[DMG::BRAKE_FRONT_RIGHT].drawText(this, QString::number(data.damageBrake[eTYRE_FRONT_RIGHT]));
    values[DMG::BRAKE_REAR_LEFT].drawText(this, QString::number(data.damageBrake[eTYRE_REAR_LEFT]));
    values[DMG::BRAKE_REAR_RIGHT].drawText(this, QString::number(data.damageBrake[eTYRE_REAR_LEFT]));

    values[DMG::SUSP_FRONT_LEFT].drawText(this, QString::number(data.damageSuspension[eTYRE_FRONT_LEFT]));
    values[DMG::SUSP_FRONT_RIGHT].drawText(this, QString::number(data.damageSuspension[eTYRE_FRONT_RIGHT]));
    values[DMG::SUSP_REAR_LEFT].drawText(this, QString::number(data.damageSuspension[eTYRE_REAR_LEFT]));
    values[DMG::SUSP_REAR_RIGHT].drawText(this, QString::number(data.damageSuspension[eTYRE_REAR_LEFT]));


}

void DamageMonitor::refreshCarshape()
{
    QPainter paint;

    paint.begin(this);
    paint.drawPixmap(0, 0, PIXMAP_WIDTH, PIXMAP_HEIGHT, carshape);
    paint.end();
}

