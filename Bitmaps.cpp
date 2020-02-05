#include "Bitmaps.h"

//enabling "PROGMEM" command for ARM boards.
#if defined(__arm__) && !defined(PROGMEM)
#define PROGMEM
#define PSTR(STR) STR
#elif ESP32
#define PROGMEM
#else
#include <avr/pgmspace.h>
#endif
/*
   Bitmap image data stored in arrays:
   Every array consists of 8 bytes of data. overy bit in the byte corresponds to the pixel on the horizontal row, and every next byte is the next (vertical) row on the display
   so the byte 0xE2, which would be (1110 0010) in bits means that on that row the first 3 and the 7th pixel would turn on with the colour specified in the drawBitmap command.
   Since only one colour can be drawn at a time, but multiple bitmaps can be layered on top of each other before calling "matrix.show()".
   for this reason there are multiple bitmaps stored here to create one single image.
*/

//Pac-Man:
const unsigned char pacmanOpen[8] PROGMEM = {
  0x3e, 0x7f, 0xee, 0xfc, 0xf8, 0xfc, 0x7f, 0x3e
};
const unsigned char pacmanClosed[8] PROGMEM = {
  0x3c, 0x7e, 0xef, 0xff, 0xff, 0xff, 0x7e, 0x3c
};
const unsigned char pacmanEye[8] PROGMEM = {
  0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00
};

//Ghost:
const unsigned char ghostBody[8] PROGMEM = {
  0x3c, 0x7e, 0x6d, 0x6d, 0xff, 0xff, 0xff, 0xdb
};
const unsigned char ghostEye[8] PROGMEM = {
  0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x00
};

//Heart:
//small:
const unsigned char smallHeartOutline[8] PROGMEM = {
  ~0xff, ~0xdb, ~0xa5, ~0xbd, ~0xbd, ~0xdb, ~0xe7, ~0xff
};
const unsigned char smallHeartInside[8]  PROGMEM = {
  ~0xff, ~0xff, ~0xdb, ~0xc3, ~0xc3, ~0xe7, ~0xff, ~0xff
};
//large:
const unsigned char largeHeartOutline[8] PROGMEM = {
  ~0x99, ~0x66, ~0x7e, ~0x7e, ~0x7e, ~0xbd, ~0xdb, ~0xe7
};
const unsigned char largeHeartInside[8] PROGMEM = {
  ~0xff, ~0x99, ~0x81, ~0x81, ~0x81, ~0xc3, ~0xe7, ~0xff
};

//Pikachu...this one is getting a bit ambitious. 5 layers...
const unsigned char pikachuBlack[8] PROGMEM = {
  0x21, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00
};
const unsigned char pikachuOrange[8] PROGMEM = {
  0x00, 0x11, 0x00, 0x00, 0x00, 0x0E, 0x14, 0x12
};
const unsigned char pikachuBrown[8] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0xC
};
const unsigned char pikachuRed[8] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00
};
const unsigned char pikachuYellow[8] PROGMEM = {
  0x00, 0x20, 0x1F, 0xD6, 0xCF, 0x10, 0x2A, 0x20
};

//checkerboard
const unsigned char checkerboard[8] PROGMEM = {
  0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa
};


