// **************************************************************************
// wwFlipdot-basic-test
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
  //dotSetup( 1, 28, 1, 19, 0);  //15x28

  dotPowerOn();    //schaltet den DC/DC Wandler für die Flipspannung ein               
  delay(50);       //kurze Wartezeit, um den Spannungswandler auf Touren kommen zu lassen

  setAll(20);       //setze alle Dots mit einer Verzögerungszeit von 5 Milisekunden zwischen den Dots
  delay(100);      //warte 100 Millisekunden
  resetAll(20);     //lösche alle Dots so schnell es geht, also ohne Verzögerung
  delay(100);
}
// ==========================================================================
void loop() {
  setDot(1, 1);     //setze das Dot X=1, Y=1
  resetDot(10, 1);  //lösche das Dot X=10, Y=1 
  delay(200);
  resetDot(1, 1);
  setDot(10, 1);
  delay(200);
}
// ===========================================================================
// ===========================================================================
