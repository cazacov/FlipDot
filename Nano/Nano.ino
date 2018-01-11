// **************************************************************************
// wwFlipdot-slace-receiver
// 2017-04-23 aufgespielt um 21:56
// **************************************************************************
#include "wwFlipdot02.h"     
#include "panelCommands.h"
#include <Wire.h>

#define RTC

#ifdef RTC
#include <RtcDS3231.h>
RtcDS3231<TwoWire> Rtc(Wire);
RtcDateTime now;
#endif

#define panelNumber 12          // die I2C Nummer des jeweiligen Panels
void displayNumber(int id);

void setup() {
  dotSetup( 8, 21, 1, 19, 0);   //21x19
  dotPowerOn();    
  delay(50);       
  resetAll(5);
  setCoilOnDuration(100);
  displayNumber(panelNumber);

  Wire.begin(panelNumber);      // join i2c bus with address panelNumber

#ifdef RTC
  Serial.begin(57600);
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  Rtc.Begin();
  if (!Rtc.IsDateTimeValid())
  {
    Serial.println("RTC lost confidence in the DateTime!");
    Rtc.SetDateTime(compiled);
  }
  if (!Rtc.GetIsRunning())
  {
    Serial.println("RTC was not actively running, starting now");
    Rtc.SetIsRunning(true);
  }
  if (!Rtc.GetIsRunning())
  {
    Serial.println("RTC was not actively running, starting now");
    Rtc.SetIsRunning(true);
  }
  now = Rtc.GetDateTime();
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
  Wire.onRequest(requestEvent);
#endif
  

  Wire.onReceive(receiveEvent); // register event
}

volatile int param1 = 0;
volatile int param2 = 0;
volatile int command = 0;                
volatile bool isReceiving = false;
int readCounter = 0;

void loop() {
  if (isReceiving)
  {
    return;
  }
  if (!command)
  {
    return;
  }
  switch (command) {
    case CMD_ALL_SET:
      setAll(0);
      break;
    case CMD_ALL_RESET:
      resetAll(0);
      break;
    case CMD_POWER_ON:
      dotPowerOn();
      break;
    case CMD_POWER_OFF:
      dotPowerOff();
      break;      
    case CMD_DOT_SET:
      setDot(param1, param2);
      break;
    case CMD_DOT_RESET:
      resetDot(param1, param2);
      break;
    case CMD_DURATION_SET:
      if (param1 >= 1 && param1 <= 5)
      {
        setCoilOnDuration(param1 * 100);
      }
      break;
#ifdef RTC
    case CMD_TIME_GET:
      now = Rtc.GetDateTime();
      break;
#endif      
  }
  command = 0;
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) 
{
  if (!isReceiving)
  {
    isReceiving = true;
    command = Wire.read();
    readCounter = 0;
  }
  while(Wire.available())
  {
    switch(readCounter)
    {
      case 0:
        param1 = Wire.read();         
        break;
      case 1:
        param2 = Wire.read();         
        break;
      default:
        Wire.read();         
    }
    readCounter++;
  }
  if (readCounter > 1)
  {
    isReceiving = false;
  }
}


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

void displayNumber(int id)
{
  drawChar(id / 10, 5, 5);  
  drawChar(id % 10, 10, 5);    
}

#ifdef RTC
void requestEvent() {
  char datestring[20];

  sprintf(datestring,
             "%04u-%02u-%02u %02u:%02u:%02u",
             now.Year(),
             now.Month(),
             now.Day(),
             now.Hour(),
             now.Minute(),
             now.Second() );
  Wire.write(datestring); 
}
#endif
