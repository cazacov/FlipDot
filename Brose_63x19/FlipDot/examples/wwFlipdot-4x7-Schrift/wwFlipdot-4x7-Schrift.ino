// **************************************************************************
// wwFlipdot-4x7-Schrift
// 2017-03-28
//
// c by Rainer Radow, 30171 Hannover, Germany
// radow.org
// **************************************************************************
#include "wwFlipdot02.h"

// ===========================================================================================
// 4x7 Zeichensatz
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
  { 0x00 , 0x7C , 0x82 , 0x7C }, // schmale 0 --- Alternative Ziffern
  { 0x30 , 0x50 , 0x90 , 0xFE }, // hohe 4
  { 0x18 , 0x28 , 0x48 , 0xFE }, // niedrige 4
  { 0x86 , 0x88 , 0x90 , 0xE0 }, // breite 7
  { 0x80 , 0x8E , 0x90 , 0xE0 }, // schmale 7
  { 0x62 , 0x92 , 0x92 , 0x8C }, // 10 = S    --- Buchstaben müsste mal jemand mehr erzeugen ;-)
  { 0x04 , 0x2A , 0x2A , 0x1E }, // 11 = a
};
// ===========================================================================================
void setup() {
  //Hier wählt man das Layout seines Moduls aus - dabei helfe ich gerne
  //dotSetup( 1, 28, 2, 15, 0);  //15x28 Startspalte (x), Anzahl Spalten, Startzeile (y), Anzahl Zeilen, Platinenversion
  //dotSetup( 8, 21, 6, 11, 0);  //11x21
  //dotSetup( 8, 21, 7, 13, 0);  //13x21
  dotSetup( 8, 21, 1, 19, 0);  //19x21
  //dotSetup( 1, 28, 1, 19, 0);  //15x28

  dotPowerOn();    //schaltet den DC/DC Wandler für die Flipspannung ein
  delay(50);       //kurze Wartezeit, um den Spannungswandler auf Touren kommen zu lassen
  resetAll(5);     //lösche alle Dots mit 5 ms Verzögerung
}
// ===========================================================================================
void loop() {
  for (int i = 0; i < 17; i++) {

    setCoilOnDuration(400);
    drawChar(i, 5, 5);

    setCoilOnDuration(50);
    drawChar(i, 11, 5);
    delay(150);
    setCoilOnDuration(50);
    drawChar(i, 11, 5);   
    delay(150);
    setCoilOnDuration(50);
    drawChar(i, 11, 5);
     delay(150);   
    setCoilOnDuration(300);
    drawChar(i, 11, 5);
    delay(500);
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
      //delay(10);  //Wenn man es gemütlich flippen lassen möchte, baut man hier ein Delay ein
    }
  }
}
// ===========================================================================================
// ===========================================================================================
