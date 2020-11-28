// **************************************************************************
// wwFlipdot-woody
// 2017-03-28
//
// c by Rainer Radow, 30171 Hannover, Germany
// radow.org
// **************************************************************************
#include "wwFlipdot02.h"

// ==========================================================================
// Feld mit der Darstellung von Woody
byte woodyRightStart = 0;
byte woodyRightEnd = 22;
byte  woodyRight [] = {   //84
  0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00, 0x00, 0x01 , 0x00 , 0x07 , 0xC0 , 0x1F , 0xF0 , 0x70 , 0x1C,
  0x77 , 0x9C , 0x70 , 0x5C , 0x11 , 0x90 , 0x10 , 0x50,
  0x77 , 0x9C , 0x70 , 0x1C , 0x77 , 0x9C , 0x10 , 0x50,
  0x11 , 0x90 , 0x70 , 0x5C , 0x77 , 0x9C , 0x70 , 0x1C,
  0x18 , 0x30 , 0x0F , 0xE0 , 0x03 , 0x80 , 0x1E , 0xF0,
  0x30 , 0x18,  0x00 , 0x00,  0x00 , 0x00
};
// ==========================================================================
void setup() {
  //Hier wählt man das Layout seines Moduls aus - dabei helfe ich gerne
  //dotSetup( 1, 28, 2, 15, 0);  //15x28 Startspalte (x), Anzahl Spalten, Startzeile (y), Anzahl Zeilen, Platinenversion
  //dotSetup( 8, 21, 6, 11, 0);  //11x21
  //dotSetup( 8, 21, 7, 13, 0);  //13x21
  dotSetup( 8, 21, 1, 19, 0);  //19x21
  //dotSetup( 1, 28, 1, 19, 0);  //15x28

  dotPowerOn();    //schaltet den DC/DC Wandler für die Flipspannung ein               
  delay(50);       //kurze Wartezeit, um den Spannungswandler auf Touren kommen zu lassen
}
// ===========================================================================================
void loop() {
  setAll(1);
  //delay(100);
  resetAll(1);
  delay(100);

  pictureRightToLeft(woodyRight, woodyRightStart , woodyRightEnd, 1);
  delay(2000);
}
// ===========================================================================================
void pictureRightToLeft(byte picture[], byte startLine, byte stopLine, uint8_t y0) {
  uint8_t anzeigeByte = 0;
  
  y0 = y0 - 1;   // Korrektur, damit Zeile 1 intern als Zeile 0 verarbeitet wird.
  for (int p0 = startLine * 2; p0 < stopLine * 2; p0 += 2) {
    for (int x = 21; x > 1; x--) {
      // Oberen 8 bit ------------------------------
      anzeigeByte = picture[p0 + x * 2];
      for (int y = 0; y < 8; y ++) {
        if ((anzeigeByte & 128) == 128) {
          setDot(x, y0 +  y);
        }
        else {
          resetDot(x, y0 + y);
        }
        anzeigeByte = anzeigeByte << 1; //select next bit
      }
      // Untere 8 bit -------------------------------
      anzeigeByte = picture[p0 + x * 2 + 1];
      for (int y = 8; y < 16; y ++) {
        if ((anzeigeByte & 128) == 128) {
          setDot(x, y0 + y);
        }
        else {
          resetDot(x, y0 + y);
        }
        anzeigeByte = anzeigeByte << 1; //select next bit
      }
    }
  }
}
// ===========================================================================================
// ===========================================================================================


