//#define RTC
#define TEST
#define SERIAL_TRACE

#include <Wire.h>
#include "LowPower.h"
#include "wwFlipdot02.h"     
#include "panelCommands.h"
#include "CommandProcessor.h"

#ifdef RTC
#include "RtcClock.h"
#endif

#define panelNumber 11          // die I2C Nummer des jeweiligen Panels

CommandProcessor command_processor(panelNumber);

#ifdef RTC
RtcClock rtc_processor(panelNumber);
#endif

void setup() {
  Serial.begin(57600);
  Wire.begin(panelNumber);      // join i2c bus with address panelNumber
  command_processor.init();

#ifdef RTC  
  rtc_processor.init();
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
      rtc_processor.read_time();
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
