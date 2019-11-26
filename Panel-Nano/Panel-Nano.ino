//#define RTC
#include <Wire.h>
#include "LowPower.h"
#include "wwFlipdot02.h"     
#include "panelCommands.h"
#include "CommandProcessor.h"

#ifdef RTC
#include "RtcClock.h"
#endif

#define panelNumber 10          // die I2C Nummer des jeweiligen Panels

CommandProcessor command_processor(panelNumber);

#ifdef RTC
RtcClock rtc_processor(panelNumber);
#endif

void setup() {
  Wire.begin(panelNumber);      // join i2c bus with address panelNumber
  Serial.begin(57600);
  command_processor.init();
#ifdef RTC  
  rtc_processor.init();
#endif
  Wire.onReceive(receiveEvent); // register event
}

volatile bool isReceiving = false;
int readCounter = 0;
int sleep_count = 0;

struct Command {
  int command;
  int param1;
  int param2;
};

#define RING_BUFFER_SIZE 32

Command ring_buffer[RING_BUFFER_SIZE];
int head = 0;
int tail = 0;
volatile int param1 = 0;
volatile int param2 = 0;
volatile int command = 0;                

void loop() {
  if (isReceiving) {
    return;
  }
  
  // Sleep next sleep_count * 8 seconds
  if (sleep_count) {
    sleep_count--;
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
    return;
  }
  
  if (head == tail) {
    return;
  }

  Command cmd = ring_buffer[tail];
  tail = (tail + 1) % RING_BUFFER_SIZE;
  
  switch(cmd.command) {
#ifdef RTC    
    case CMD_TIME_GET:
      rtc_processor.read_time();
      break;
#endif      
    case CMD_SLEEP:
      sleep_count = 6;
      break;
    default:
      command_processor.execute(cmd.command, cmd.param1, cmd.param2);
      break;
  }
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) 
{
  if (!isReceiving) {
    isReceiving = true;
    command = Wire.read();
    readCounter = 0;
  }
  while(Wire.available()){
    switch(readCounter) {
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
  if (readCounter > 1) {
    isReceiving = false;
    ring_buffer[head] = Command {
      command,
      param1,
      param2
    };
    head = (head + 1)% RING_BUFFER_SIZE;
  }
}
