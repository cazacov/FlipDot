// **************************************************************************
// wwFlipdot-live für Einzelmodul
// es fehlt noch die Erkennung des Spielendes bei sich endlos wiederholenden Figuren
// 2017-08-01
//
// c by Rainer Radow, 30171 Hannover, Germany
// radow.org
// **************************************************************************
#include "wwFlipdot02.h"

// ===========================================================================================
#define worldX 21
#define worldY 19

#define neu 1
#define alt 0

byte world[worldX + 1][worldY + 1][2];
long density = 50;

int dotsGesamt1 = 0;
int token = 0;
int newFlip = 0;

// ===========================================================================================
void setup() {
  //Hier wählt man das Layout seines Moduls aus - dabei helfe ich gerne
  //dotSetup( 1, 28, 2, 15, 0);  //15x28 Startspalte (x), Anzahl Spalten, Startzeile (y), Anzahl Zeilen, Platinenversion
  //dotSetup( 8, 21, 6, 11, 0);  //11x21
  //dotSetup( 8, 21, 7, 13, 0);  //13x21
  dotSetup( 8, 21, 1, 19, 0);  //19x21
  //dotSetup( 1, 28, 1, 19, 0);  //15x28

  dotPowerOn();    //schaltet den DC/DC Wandler für die Flipspannung ein
  resetAll(0);     //lösche alle Dots mit 5 ms Verzögerung
}
// ===========================================================================================
void loop() {
  //--- Erstbevölkerung ---------------------------------------
  randomSeed(analogRead(2));
  for (int x = 1; x <= worldX; x++) {
    for (int y = 1; y <= worldY; y++) {
      if (random(100) < density)
        world[x][y][alt] = 1;
      else
        world[x][y][alt] = 0;
    }
  }
  delay(1000);
  resetAll(2);
  delay(1000);
  do {
    // --- Birth and death cycle -------------------------
    for (int x = 1; x <= worldX; x++) {
      for (int y = 1; y <= worldY; y++) {
        int count = neighbours(x, y);
        switch (count) {
          case 2:  // Altes Leben bleibt erhalten
            world[x][y][neu] = world[x][y][alt];
            break;
          case 3:  // Neues Leben oder altes behalten
            world[x][y][neu] = 1;
            break;
          default: // Rest kein neues Leben bzw. stirbt -------
            world[x][y][neu] = 0;
            break;
        }
      }
    }
    ausgabeNeueZustaende();
    // ---------------------------------------- Copy next generation into place
    for (int x = 1; x <= worldX; x++) {
      for (int y = 1; y <= worldY; y++) {
        world[x][y][alt] = world[x][y][neu];
      }
    }
    delay(100);
  } while (newFlip > 0);
}
//===========================================================
int neighbours(int x, int y) {
  int xrechts, xlinks, yoben, yunten;

  if (x == 1)       xlinks = worldX;  else xlinks  = x - 1;
  if (x == worldX)  xrechts = 1;      else xrechts = x + 1;
  if (y == 1)       yoben = worldY;   else yoben   = y - 1;
  if (y == worldY)  yunten = 1;       else yunten  = y + 1;

  return   world[xrechts][y]     [alt] + //rechts daneben
           world[x]      [yunten][alt] + //einen darunter
           world[xlinks] [y]     [alt] + //links
           world[x]      [yoben] [alt] + //einen darüber
           world[xrechts][yunten][alt] + //rechts darunter
           world[xlinks] [yunten][alt] + //links darunter
           world[xlinks] [yoben] [alt] + //links darüber
           world[xrechts][yoben] [alt];  //rechts darüber
}
//===========================================================
void ausgabeNeueZustaende() {
newFlip = 0;
  // ----------------------------------------------------------------------------------
  for (int x = 1; x <= worldX; x++) {
    for (int y = 1; y <= worldY; y++) {
      if (world[x][y][neu] != world[x][y][alt]) {
        token = 1;
        if ( world[x][y][neu] == 1)
          setDot(x, y);
        else
          resetDot(x, y);
        newFlip++;
      }
    }
  }
}
//===========================================================
//===========================================================
