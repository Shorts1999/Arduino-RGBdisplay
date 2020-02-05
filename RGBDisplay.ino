/* 8x8 WS2812B LED display software

   Date: January 27th 2020
  Author: Sjors Smit

*/

//libraries for controlling the matrix:
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

//File containing the bitmap image data
#include "Bitmaps.h"

#define PIN 6       //LED-string connected to digital pin D6 of the Arduino

#define TILEWIDTH 8      //the amount of horizontal pixels in a single panel
#define TILEHEIGTH 8     //the amount of vertical pixels in a single panel
#define PANELTYPE  (NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG) //Top-left is the first pixel, then scan in a zig-zag pattern vertically.

#define XTILES 1          //the amount of "tiles" (matrices) in the horizontal direction
#define YTILES 1          //the amount of tiles in the vertical direction
#define TILEORIENTATION (NEO_TILE_TOP   + NEO_TILE_LEFT   + NEO_TILE_COLUMNS   + NEO_TILE_PROGRESSIVE)

//Defining the actual display object, with all the above mentioned properties.
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(TILEWIDTH, TILEHEIGTH, XTILES, YTILES, PIN, PANELTYPE + TILEORIENTATION, NEO_GRB + NEO_KHZ800);

// Colour definitions (full RGB range colors available through "matrix.Color(R, G, B)" command)
//Set 24-bit (8-bits per colour, value 0-255) as input, returns the proper 16-bit conversion for the GFX library.
#define BLACK    0x0000
#define WHITE    0xFFFF
#define BLUE     0x001F
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define MAGENTA  0xF81F
#define YELLOW   0xFFE0
#define ORANGE   matrix.Color(0xff, 0xA5, 0x00)
#define PINK     matrix.Color(0xff, 0x14,0x93)
#define BROWN    matrix.Color(0x6F,0x37, 0x0F) //example of using the matrix.Color() command, values are written in hexadecimal.

void rainbow(int, int); //function prototype
const uint16_t rainbowCycle[] = {RED, ORANGE, YELLOW, GREEN, CYAN, BLUE, MAGENTA}; //array that can be used to scroll through a cycle of rainbow colours.

//Commands in "void setup()" will run once at startup and then never again.
void setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  //command "matrix.clear()" empties the display BUFFER. to make changes visible "matrix.show()" command must still be called.
  matrix.clear();
  //To display any changes made to the display buffer, "matrix.show()" command must be called. this allows to layer multiple images in the buffer before displaying these on the panel.
  matrix.show();

  //Brightness can be set on a scale from 0-255. DO NOT SET HIGHER THAN 50, BATTERY CAN NOT HANDLE MORE CURRENT/POWER!
  matrix.setBrightness(32);

  //Set the colour of text to be displayed, can be changed at any time
  matrix.setTextColor(BLUE);

  //to scroll text use a for loop, start value of 9 to start at teh far right side. end value should be (-6) times the amount of characters in the string (INCLUDING SPACES!) plus one, since every character is 6 pixels wide
  //and we want it to keep scrolling until the last character is offscreen.

  //for loop works like this: "for(startvalue; endvalue; what to do at the end of each loop)". this gives us a loop here that starts with a value of 9, then decreases by 1 (Xpos--) at the end of each cycle, and keeps going until it reaches a value of -6*(the amount of charactes in the string)
  for (int Xpos = 9; Xpos > (-6 * 7); Xpos--) {
    matrix.setCursor(Xpos, 0);
    matrix.print("Hello!");
    matrix.show();
    delay(80);
    matrix.clear();
  }
}

//commands in "void loop()" will keep repeating until the display is turned off again.
void loop() {
    //"matrix.fillscreen()" fills the entire display with a colour. (doesn't appear on screen until "matrix.show();" is called)
    matrix.fillScreen(BLUE);
    //Pikachu image is drawn on top of the blue filled screen, overwriting the buffer and thus creating the pikachu image with a blue background!
    drawPikachu(0, 0);
    //update changes in framebuffer to the actual display
    matrix.show();
    //pause for 10 seconds (delay function takes input in milliseconds)
    delay(10000);
    matrix.clear();

    //displays a rainbow pattern over the entire display, increase the number to extend the duration
    rainbow(30, 3);

    for (int j = 0; j < 3;  j++) {
      for (unsigned int i = 0; i < (sizeof(rainbowCycle) / sizeof(*rainbowCycle)); i++) {
        matrix.fillScreen(rainbowCycle[i]);
        matrix.show();
        delay(350);
        matrix.clear();
      }
    }

    matrix.clear();
    //using a for loop to repeat the pattern.
    for (int i = 0; i < 3; i++) {
      //Start at X position -10 so that it starts offscreen, then keep scrolling until position 49, meaning that the last ghost will have left the screen on the other side.
      for (int Xpos = -10; Xpos < 49; Xpos++) {
        //"Xpos % 2" divides the Xpos value by 2 and then gives the value of the remainder, meaning that when Xpos is even, and thus divisible, it will return a 0, but when Xpos is odd, the operation will leave a remainder, giving a 1 into the
        //drawpacman command, and thus drawing it open or closed depending on the position on the screen, giving the animation of it eating.
        drawPacman(Xpos, 0, Xpos % 2);
        //each image is 8 pixels wide, then we also want a little bit of space between the images, so every ghost is drawn 10 pixels behind the previous one. (Xpos-10, Xpos-20 etc..)
        drawGhost(Xpos - 10, 0, RED);
        drawGhost(Xpos - 20, 0, CYAN);
        drawGhost(Xpos - 30, 0, ORANGE);
        drawGhost(Xpos - 40, 0, PINK);
        matrix.show();
        delay(120);
        matrix.clear();
      }
    }
    //Alternate between the smaller and larger version of the heart to animate it beating
    for (int i = 0; i < 9; i++) {
      drawSmallHeart(0, 0);
      matrix.show();
      delay(500);
      matrix.clear();
      drawLargeHeart(0, 0);
      matrix.show();
      delay(500);
      matrix.clear();
    }
  for (int i = 0; i < 5; i++) {
    drawCheckerboard(RED, BLUE);
    matrix.show();
    delay(500);
    drawCheckerboard(BLUE, RED);
    matrix.show();
    delay(500);
  }
  for (int repeat = 0; repeat < 4; repeat++) {
    for (unsigned int i = 0; i < (sizeof(rainbowCycle) / sizeof(*rainbowCycle)); i++) {
      for (int Xpos = 0; Xpos < 5; Xpos++) {
        matrix.drawLine(3 - Xpos, 0, 3 - Xpos, 7, rainbowCycle[i]);
        matrix.drawLine(Xpos + 4, 0, Xpos + 4, 7, rainbowCycle[i]);
        matrix.show();
        delay(50);
      }
      delay(100);
    }
  }
}

//functions to draw the complete bitmaps on the screen
//since only one colour at a time can be drawn with the drawBitmap command, we have to seperately layer each colour of the bitmap.
//data for each colour of the image is stored in a seperate bitmap array in the "bitmaps.cpp" file, these can then all be written one by one to the framebuffer before then being displayed
//by the "matrix.show()" command.
void drawPacman(int x, int y, bool Open) {
  if (Open) {
    matrix.drawBitmap(x, y, pacmanOpen, 8, 8, YELLOW);
  }
  else {
    matrix.drawBitmap(x, y, pacmanClosed, 8, 8, YELLOW);
  }
  matrix.drawBitmap(x, y, pacmanEye, 8, 8, BLUE);
}

void drawGhost(int x, int y, uint16_t Colour) {
  matrix.drawBitmap(x, y, ghostBody, 8, 8, Colour);
  matrix.drawBitmap(x, y, ghostEye, 8, 8, BLUE);
}
void drawLargeHeart(int x, int y) {
  matrix.drawBitmap(x, y, largeHeartOutline, 8, 8, WHITE);
  matrix.drawBitmap(x, y, largeHeartInside, 8, 8, RED);
}
void drawSmallHeart(int x, int y) {
  matrix.drawBitmap(x, y, smallHeartOutline, 8, 8, WHITE);
  matrix.drawBitmap(x, y, smallHeartInside, 8, 8, RED);
}
void drawPikachu(int x, int y) {
  matrix.drawBitmap(x, y, pikachuYellow, 8, 8, YELLOW);
  matrix.drawBitmap(x, y, pikachuBrown, 8, 8, BROWN);
  matrix.drawBitmap(x, y, pikachuBlack, 8, 8, BLACK);
  matrix.drawBitmap(x, y, pikachuRed, 8, 8, RED);
  matrix.drawBitmap(x, y, pikachuOrange, 8, 8, ORANGE);
}
void drawCheckerboard(uint16_t Colour1, uint16_t Colour2) {
  matrix.fillScreen(Colour1);
  matrix.drawBitmap(0, 0, checkerboard, 8, 8, Colour2);
}


//Rainbow cycle command stolen from strandtest from the neopixel example library ;)
// Rainbow cycle along whole matrix. Pass delay time (in ms) between frames.
void rainbow(int wait, int numcycles = 5) {
  // Hue of first pixel runs 3 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this outer loop:
  for (long firstPixelHue = 0; firstPixelHue < numcycles * 65536; firstPixelHue += 256) {
    for (unsigned int i = 0; i < matrix.numPixels(); i++) { // For each pixel in matrix...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the matrix
      // (matrix.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / matrix.numPixels());
      // matrix.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through matrix.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      matrix.setPixelColor(i, matrix.gamma32(matrix.ColorHSV(pixelHue)));
    }
    matrix.show(); // Update matrix with new contents
    delay(wait);  // Pause for a moment
  }
}
