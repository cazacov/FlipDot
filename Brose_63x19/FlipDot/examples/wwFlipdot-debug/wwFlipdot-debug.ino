// **************************************************************************
// wwFlipdot-debug-test
// 2017-03-27
//
// c by Rainer Radow, 30171 Hannover, Germany
// radow.org
// **************************************************************************
#include "wwFlipdot02.h"
// ==========================================================================
void setup() {
  //Hier wählt man das Layout seines Moduls aus - dabei helfe ich gerne
  //dotSetup( 1, 28, 2, 15, 0);  //15x28 Startspalte (x), Anzahl Spalten, Startzeile (y), Anzahl Zeilen, Platinenversion
  //dotSetup( 8, 21, 6, 11, 0);  //11x21
  //dotSetup( 8, 21, 7, 13, 0);  //13x21
  dotSetup( 8, 21, 1, 19, 0);  //19x21
  //  dotSetup( 1, 28, 1, 19, 0);  //15x28

  dotPowerOn();    //schaltet den DC/DC Wandler für die Flipspannung ein               
  delay(50);       //kurze Wartezeit, um den Spannungswandler auf Touren kommen zu lassen
}
// ==========================================================================
void loop() {

  for (int i = 15; i>=0; i-=3) {
  setAll(i);       //setze alle Dots mit einer Verzögerungszeit von i Milisekunden zwischen den Dots
  delay(100);      //warte 100 Millisekunden
  resetAll(i);     //lösche alle Dots mit i ms Verzögerung
  delay(100);
  }
  delay(2000);
}
// ===========================================================================
// ===========================================================================
