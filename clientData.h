#ifndef CLIENT_DATA_H
#define CLIENT_DATA_H


#include <stdint.h>



// Tyres
enum
{
  eTYRE_FRONT_LEFT = 0,
  eTYRE_FRONT_RIGHT,
  eTYRE_REAR_LEFT,
  eTYRE_REAR_RIGHT,
  //--------------
  eTYRE_MAX
};

// (Type#5) Flag Colours (to be used with 'mHighestFlagColour')
enum
{
  eFLAG_COLOUR_NONE = 0,       // Not used for actual flags, only for some query functions
  eFLAG_COLOUR_GREEN,          // End of danger zone, or race started
  eFLAG_COLOUR_BLUE,           // Faster car wants to overtake the participant
  eFLAG_COLOUR_WHITE,          // Approaching a slow car
  eFLAG_COLOUR_YELLOW,         // Danger on the racing surface itself
  eFLAG_COLOUR_DOUBLE_YELLOW,  // Danger that wholly or partly blocks the racing surface
  eFLAG_COLOUR_BLACK,          // Participant disqualified
  eFLAG_COLOUR_CHEQUERED,      // Chequered flag
  //-------------
  eFLAG_COLOUR_MAX
};

// (Type#9) Car Flags (to be used with 'mCarFlags')
enum
{
  eCAR_HEADLIGHT         = (1<<0),
  eCAR_ENGINE_ACTIVE     = (1<<1),
  eCAR_ENGINE_WARNING    = (1<<2),
  eCAR_SPEED_LIMITER     = (1<<3),
  eCAR_ABS               = (1<<4),
  eCAR_HANDBRAKE         = (1<<5),
};

typedef struct
{
    int8_t gear;                            // [ UNITS = NONE ]     [ RANGE = -128 -> +127 ]
    int8_t maxGear;                         // [ UNITS = NONE ]     [ RANGE = -128 -> +127 ]
    uint16_t rpm;                           // [ UNITS = rpm  ]     [ RANGE = 0 -> 65535 ]
    uint16_t maxRpm;                        // [ UNITS = rpm  ]     [ RANGE = 0 -> 65535 ]
    uint16_t speed;                         // [ UNITS = km/h ]     [ RANGE = 0 -> 65535 ]
    uint8_t fuelLevel;                      // [ UNITS = liters ]   [ RANGE = 0 -> 255 ]
    uint8_t fuelCapacity;                   // [ UNITS = liters ]   [ RANGE = 0 -> 255 ]    

    uint16_t tempTyre[eTYRE_MAX];           // [ UNITS = celsius ]  [ RANGE = 0 -> 65535 ]
    uint16_t tempBrake[eTYRE_MAX];          // [ UNITS = celsius ]  [ RANGE = 0 -> 65535 ]
    uint16_t tempOil;                       // [ UNITS = celsius ]  [ RANGE = 0 -> 65535 ]
    uint16_t tempWater;                     // [ UNITS = celsius ]  [ RANGE = 0 -> 65535 ]

    uint8_t damageAero;                     // [ UNITS = percent ]     [ RANGE = 0 -> 100 ]
    uint8_t damageEngine;                   // [ UNITS = percent ]     [ RANGE = 0 -> 100 ]
    uint8_t damageBrake[eTYRE_MAX];         // [ UNITS = percent ]     [ RANGE = 0 -> 100 ]
    uint8_t damageSuspension[eTYRE_MAX];    // [ UNITS = percent ]     [ RANGE = 0 -> 100 ]
    uint8_t damageTyre[eTYRE_MAX];          // [ UNITS = percent ]     [ RANGE = 0 -> 100 ]

    uint8_t raceFlagColour;                 // See (Type#5) Flag Colours
    uint8_t carFlags;                       // See (Type#9) Car Flags

    uint8_t racePosition;


    float timeBestLap;
    float timeLastLap;
    float timeCurrentSector1;
    float timeCurrentSector2;
    float timeCurrentSector3;
    float timeFastestSector1;
    float timeFastestSector2;
    float timeFastestSector3;
    float timeSplitAhead;
    float timeSplitBehind;

} clientDataStruct;














#endif // CLIENT_DATA_H
