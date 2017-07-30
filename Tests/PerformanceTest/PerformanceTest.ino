// Performance test

// **************************************************************************
#include "wwFlipdotPar.h"

// ===========================================================================================
const uint8_t  ziffer[][4] = {
  { 0x7C , 0x82 , 0x82 , 0x7C }, // 0
  { 0x00 , 0x42 , 0xFE , 0x02 }, // 1
  { 0x46 , 0x8A , 0x92 , 0x62 }, // 2
  { 0x44 , 0x82 , 0x92 , 0x6C }, // 3
  { 0x30 , 0x50 , 0x90 , 0xFE }, // 4
  { 0xE4 , 0xA2 , 0xA2 , 0x9C }, // 5
  { 0x7C , 0xA2 , 0xA2 , 0x1C }, // 6
  { 0x86 , 0x88 , 0x90 , 0xE0 }, // 7
  { 0x6C , 0x92 , 0x92 , 0x6C }, // 8
  { 0x70 , 0x8A , 0x8A , 0x7C }, // 9
};
// ===========================================================================================

void setup() {
  dotSetup( 8, 21, 1, 19, 0);  //19x21

  dotPowerOn();    
  delay(50);       
  resetAll(5);     
  delay(10000);
}
// ===========================================================================================

void loop() {
  setCoilOnDuration(50);
  for (int i = 0; i < 1000; i++) {
    int d = i;
    for (int j = 0; j < 4; j++)
    {
      drawChar(d % 10, 17-j*5, 5);
      d /= 10;
    }
    delay(10);
  }
}
// ===========================================================================================

void drawChar(int charNumber, int x0, int y0) {
  uint8_t anzeigeByte = 0;

  for (int xc = 0; xc < 4; xc++) {
    anzeigeByte = ziffer[charNumber][xc];
    for (int yc = 0; yc < 7; yc ++) {
      if ((anzeigeByte & 128) == 128) {
        setDot(x0 + xc, y0 + yc);
      }
      else {
        resetDot(x0 + xc, y0 + yc);
      }
      anzeigeByte = anzeigeByte << 1; //select next bit
    }
  }
}
// ===========================================================================================
