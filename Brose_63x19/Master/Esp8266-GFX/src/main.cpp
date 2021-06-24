#include <Arduino.h>

#include "flipBoard.h"
#include <fonts/FreeMonoBold9pt7b.h>

#define nyan_cat_height 17
#define nyan_cat_width 30

static const unsigned char PROGMEM nyan_cat[] = {
 B00000000, B01111111, B11111110, B00000000,
 B00000000, B10000000, B00000001, B00000000,
 B00000001, B00000000, B00000000, B10000000,
 B00000001, B00000000, B11000000, B10110000,
 B01111001, B00000001, B00100000, B11001000,
 B10001111, B00000001, B00010000, B10001000,
 B11000001, B00000001, B00001111, B00001000,
 B00111101, B00000001, B00000000, B00001000,
 B00000111, B00000010, B00010000, B00100100,
 B00000001, B00000010, B00110001, B01100100,
 B00000001, B00000010, B00000000, B00000100,
 B00000011, B00000010, B00010010, B01000100,
 B00001111, B00000001, B00011111, B11001000,
 B00010001, B10000000, B10000000, B00010000,
 B00010010, B11111111, B11111111, B11100000,
 B00011100, B01001000, B10010100, B10000000,
 B00000000, B00111000, B01110011, B10000000,
};

Panel panels[] = {
    {10, D5},
    {12, D6},
    {14, D7}};

FlipBoard flipBoard(21, 19, panels, 1, 3);

void setup()
{
  Serial.begin(115200);
  Serial.println("Serial started");
  flipBoard.begin();  
  flipBoard.fillScreen(0);
}

int n = 0;
void loop() {

  /*
  int8_t coord[][2] = {
    {-1,-1}, {0, -1}, {1, -1}, {1,0}, 
    {1, 1}, {0, 1}, {-1,1},{-1,0}
  };

  for (int x = 0; x < 33; x++) {
    for (int i = 0; i < 8; i++) {
      int dx = coord[i][0];
      int dy = coord[i][1];
      int x0 = x + dx;
      int y0 = 1 + dy;
      flipBoard.writeLine(x0-1, y0-1, x0+30, y0-1, 0);
      flipBoard.writeLine(x0-1, y0+17, x0+30, y0+17, 0);
      flipBoard.writeLine(x0-1, y0-1, x0-1, y0+17, 0);
      flipBoard.writeLine(x0+30, y0-1, x0+30, y0+17, 0);
      flipBoard.drawBitmap(x + dx, 1 + dy, nyan_cat, nyan_cat_width, nyan_cat_height, 1, 0);
      flipBoard.endWrite();
      delay(100);
    }
  }
  flipBoard.fillScreen(0);
  */
  flipBoard.setFont(&FreeMonoBold9pt7b);
  flipBoard.setCursor(0,12);
  flipBoard.print("2021");
  flipBoard.endWrite();
  delay(100*1000);
}