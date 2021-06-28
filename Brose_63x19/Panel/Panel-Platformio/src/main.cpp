#include <Wire.h>
#include "LowPower.h"
#include "wwFlipdot02.h"     
#include "panelCommands.h"
#include "CommandProcessor.h"

#define panelNumber 12    // I2C port number that the panel listens to

CommandProcessor command_processor(panelNumber);

volatile bool isReceiving = false;
bool isSleeping = false;
uint8_t readCounter = 0;
uint8_t sleep_count = 0;
volatile uint8_t param1 = 0;
volatile uint8_t param2 = 0;
volatile uint8_t command = 0;     

#define RING_BUFFER_SIZE 400
struct Command {
  uint8_t command;
  uint8_t param1;
  uint8_t param2;
};
Command ring_buffer[RING_BUFFER_SIZE];
volatile uint16_t head = 0;
uint16_t tail = 0;

void receiveEvent(int howMany);
void inline addCommand(uint8_t p_command, uint8_t p_param1, uint8_t p_param2);

void setup() {
  Wire.begin(panelNumber);      // join i2c bus with address panelNumber
#ifdef SERIAL_TRACE  
  Serial.begin(57600);
#endif  
  command_processor.init();
  Wire.onReceive(receiveEvent); // register event
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  head = tail = 0;
#ifdef TEST
  addCommand(CMD_START, 0, 0);
  addCommand(CMD_TEST, 0, 0);
  addCommand(CMD_DELAY, 20, 0);
  addCommand(CMD_SHOWID, 0, 0);
#endif 
}

void loop() {
  
  if (isReceiving) {
    return;
  }
  
  // Sleep next sleep_count * 8 seconds
  if (sleep_count) {
    sleep_count--;
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
    return;
  } else {
    if (isSleeping) {
      digitalWrite(LED_BUILTIN, HIGH);
      command_processor.execute(CMD_POWER_ON, 0, 0);
    }
  }
  
  if (head == tail) {
    return;
  }

  uint8_t cmd = ring_buffer[tail].command;
  uint8_t p1 = ring_buffer[tail].param1;
  uint8_t p2 = ring_buffer[tail].param2;
  tail = (tail + 1) % RING_BUFFER_SIZE;

  switch(cmd) {
    case CMD_SLEEP:
      isSleeping = true;
      digitalWrite(LED_BUILTIN, LOW);
      command_processor.execute(CMD_POWER_OFF, 0, 0);
      sleep_count = 6;
      break;
    default:
      command_processor.execute(cmd, p1, p2);
      break;
  }
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) 
{
  if (!isReceiving) {
    isReceiving = true;
  }
  while(Wire.available()){
    switch(readCounter) {
      case 0:
        command = Wire.read();
        break;
      case 1:
        param1 = Wire.read();         
        break;
      case 2:
        param2 = Wire.read();         
        break;
      default:
        Wire.read();         
    }
    readCounter++;
    if (readCounter > 2) {
      if (CommandProcessor::isValidCommand(command)) {
        addCommand(command, param1, param2);
        readCounter = 0;
      }
      else {
        // I2C got out of sync, clear input buffer
        readCounter = 0;
        isReceiving = false;
        while(Wire.available()) {
          Wire.read();       
        }
      }
    }
  }
  if (readCounter  == 0) {
    isReceiving = false;
  }
}

void inline addCommand(uint8_t p_command, uint8_t p_param1, uint8_t p_param2) {
  ring_buffer[head].command = p_command;
  ring_buffer[head].param1 = p_param1;
  ring_buffer[head].param2 = p_param2;
  head = (head + 1) % RING_BUFFER_SIZE;
} 