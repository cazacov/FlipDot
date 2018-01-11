// **************************************************************************
// wwFlipdot-clock
// 2017-03-21
//
// c by Rainer Radow, 30171 Hannover, Germany
// radow.org
// **************************************************************************
#include "wwFlipdot02.h"

#include <Wire.h>
#include <RtcDS3231.h>
RtcDS3231<TwoWire> Rtc(Wire);
// ===========================================================================================
const uint8_t  ziffer[][4] = {
  { 0x7C , 0x82 , 0x82 , 0x7C },
  { 0x00 , 0x42 , 0xFE , 0x02 },
  { 0x46 , 0x8A , 0x92 , 0x62 },
  { 0x44 , 0x82 , 0x92 , 0x6C },
  { 0x30 , 0x50 , 0x90 , 0xFE },
  { 0xE4 , 0xA2 , 0xA2 , 0x9C },
  { 0x7C , 0xA2 , 0xA2 , 0x1C },
  { 0x86 , 0x88 , 0x90 , 0xE0 },
  { 0x6C , 0x92 , 0x92 , 0x6C },
  { 0x70 , 0x8A , 0x8A , 0x7C },
};
// ===========================================================================================
int altStunde = 25;
int altMinute = 61;
int altSecond = 61;

boolean blinky = 1;               //zeigt an, ob die Dots zwischen HH und MM an sind oder aus

#define zeile1 1                  //obere Position der Stunden-Ziffern
#define zeile2 9                  //obere Position der Sekunden-Ziffern

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

  setAll(5);
  delay(100);
  resetAll(5);
  delay(100);
  // ----------------- Dieser Code wurde aus der RTC Library kopiert --------------
  Serial.begin(57600);            

  Serial.print("compiled: ");
  Serial.print(__DATE__);
  Serial.println(__TIME__);

  Rtc.Begin();

  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  printDateTime(compiled);
  Serial.println();

  if (!Rtc.IsDateTimeValid())
  {
    // Common Cuases:
    //    1) first time you ran and the device wasn't running yet
    //    2) the battery on the device is low or even missing

    Serial.println("RTC lost confidence in the DateTime!");

    // following line sets the RTC to the date & time this sketch was compiled
    // it will also reset the valid flag internally unless the Rtc device is
    // having an issue

    Rtc.SetDateTime(compiled);
  }

  if (!Rtc.GetIsRunning())
  {
    Serial.println("RTC was not actively running, starting now");
    Rtc.SetIsRunning(true);
  }

  RtcDateTime now = Rtc.GetDateTime();
  if (now < compiled)
  {
    Serial.println("RTC is older than compile time!  (Updating DateTime)");
    Rtc.SetDateTime(compiled);
  }
  else if (now > compiled)
  {
    Serial.println("RTC is newer than compile time. (this is expected)");
  }
  else if (now == compiled)
  {
    Serial.println("RTC is the same as compile time! (not expected but all is fine)");
  }

  // never assume the Rtc was last configured by you, so
  // just clear them to your needed state
  Rtc.Enable32kHzPin(false);
  Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeNone);


  // ---- Dots zwischen Stunden und Minuten einstellen
  setDot(11, zeile1 + 2);
  setDot(11, zeile1 + 4);
}
// ===========================================================================================
#define showSeconds 0      // Sekunden in der 2. Schriftzeile ausgeben 1 = ja / 0 = nein
#define showBlinkyDots 1   // Doppelpunkt zwischen Stunde und Minute blinken 1 = ja / 0 = nein

void loop() {
  int wert = 0;
  if (!Rtc.IsDateTimeValid())
  {
    // Common Cuases:
    //    1) the battery on the device is low or even missing and the power line was disconnected
    Serial.println("RTC lost confidence in the DateTime!");
  }

  RtcDateTime now = Rtc.GetDateTime();
  printDateTime(now);
  Serial.println();

  RtcTemperature temp = Rtc.GetTemperature();
  Serial.print(temp.AsFloat());
  Serial.println("C");
  //----
  if (now.Hour() != altStunde) {
    altStunde = now.Hour();
    wert = now.Hour() % 10;
    drawChar(wert, 6, zeile1);     // obere linke Ecke der Ziffer bei x=6
    wert = now.Hour() / 10;
    drawChar(wert, 1, zeile1);     // obere linke Ecke der Ziffer bei x=1
  }
  //----
  if (now.Minute() != altMinute) {
    altMinute = now.Minute();
    wert = now.Minute() % 10;
    drawChar(wert, 18, zeile1);    // obere linke Ecke der Ziffer bei x=18
    wert = now.Minute() / 10;
    drawChar(wert, 13, zeile1);    // obere linke Ecke der Ziffer bei x=13
  }
  //----
  if (now.Second() != altSecond) {
    altSecond = now.Second();
    //----
    if (showBlinkyDots) {
      // Flipping dots between the
      if (blinky) {
        resetDot(11, zeile1 + 2);
        resetDot(11, zeile1 + 4);
      } else {
        setDot(11, zeile1 + 2);
        setDot(11, zeile1 + 4);
      }
      blinky = !blinky;
    }
    //----
    if (showSeconds) {
      wert = now.Second() % 10;
      drawChar(wert, 18, zeile2);  // obere linke Ecke der Ziffer bei x=18
      wert = now.Second() / 10;
      drawChar(wert, 13, zeile2);  // obere linke Ecke der Ziffer bei x=13
    }
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
      delay(2); // je nach gewünschter Flippgeschwindigkeit hier einen Wert von 0 bis 50? eingeben
    }
  }
}
// ===========================================================================================
#define countof(a) (sizeof(a) / sizeof(a[0]))
void printDateTime(const RtcDateTime& dt)
{
  char datestring[20];

  snprintf_P(datestring,
             countof(datestring),
             PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
             dt.Month(),
             dt.Day(),
             dt.Year(),
             dt.Hour(),
             dt.Minute(),
             dt.Second() );
  Serial.print(datestring);
}
// ===========================================================================================
// ===========================================================================================
