#ifndef SETTINGS_H
#define SETTINGS_H


#define PIXMAP_WIDTH   1024
#define PIXMAP_HEIGHT  600

#define FONT    "Consolas"

// Letters per Text-Label
#define LABEL_LETTERS       5
#define VALUE_LETTERS       9

// Label-Text size in points
#define FONT_SIZE_TEXT      30
#define FONT_SIZE_STATUS    50
#define FONT_SIZE_GEAR      200

// Border-space
#define BORDER_SPACE        10

#define MIN_Y   FONT_SIZE_STATUS+BORDER_SPACE+50
#define MAX_Y   PIXMAP_HEIGHT-20
#define MIN_X   BORDER_SPACE
#define MAX_X   PIXMAP_WIDTH-BORDER_SPACE

#define CEN_X   ((MAX_X-MIN_X)/2)+MIN_X
#define CEN_Y   ((MAX_Y-MIN_Y)/2)+MIN_Y

// Position Status-Box
#define STATUS_TOP      BORDER_SPACE
#define STATUS_BOT      (FONT_SIZE_STATUS*1.5)+BORDER_SPACE
#define STATUS_LEFT     MIN_X
#define STATUS_RIGHT    MAX_X







#endif // SETTINGS_H

