//#define RTC
#define TEST
#define SERIAL_TRACE

#include <Wire.h>
#include "LowPower.h"
#include "wwFlipdot02.h"     
#include "panelCommands.h"
#include "CommandProcessor.h"

#define panelNumber 11          // die I2C Nummer des jeweiligen Panels



#ifdef RTC
#include <RtcDS3231.h>
RtcDS3231<TwoWire> Rtc(Wire);
RtcDateTime now;
#endif

CommandProcessor command_processor(panelNumber);

void setup() {
  Serial.begin(57600);
  Wire.begin(panelNumber);      // join i2c bus with address panelNumber

  command_processor.init();

#ifdef RTC
#ifdef SERIAL_TRACE
  Serial.begin(57600);
#endif;  
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  Rtc.Begin();
  if (!Rtc.IsDateTimeValid())
  {
#ifdef SERIAL_TRACE    
    Serial.println("RTC lost confidence in the DateTime!");
#endif    
    Rtc.SetDateTime(compiled);
  }
  if (!Rtc.GetIsRunning())
  {
#ifdef SERIAL_TRACE    
    Serial.println("RTC was not actively running, starting now");
#endif    
    Rtc.SetIsRunning(true);
  }
  if (!Rtc.GetIsRunning())
  {
#ifdef SERIAL_TRACE    
    Serial.println("RTC was not actively running, starting now");
#endif    
    Rtc.SetIsRunning(true);
  }
  now = Rtc.GetDateTime();
  if (now < compiled)
  {
#ifdef SERIAL_TRACE    
    Serial.println("RTC is older than compile time!  (Updating DateTime)");
#endif    
    Rtc.SetDateTime(compiled);
  }
  else if (now > compiled)
  {
#ifdef SERIAL_TRACE    
    Serial.println("RTC is newer than compile time. (this is expected)");
#endif    
  }
  else if (now == compiled)
  {
#ifdef SERIAL_TRACE    
    Serial.println("RTC is the same as compile time! (not expected but all is fine)");
#endif    
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
int sleep_count = 0;

void loop() {
  if (isReceiving)
  {
    return;
  }
  
  if (sleep_count)
  {
    sleep_count--;
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
    return;
  }
  
  if (!command)
  {
    return;
  }

  switch(command) {
#ifdef RTC    
    case CMD_TIME_GET:
      now = Rtc.GetDateTime();
      break;
#endif      
    case CMD_SLEEP:
      sleep_count = 6;
      break;
    default:
      command_processor.execute(command, param1, param2);
      break;
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
