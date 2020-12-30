#include <Wire.h>
#include "LowPower.h"
#include "wwFlipdot02.h"     
#include "panelCommands.h"
#include "CommandProcessor.h"

#define panelNumber 14    // I2C port number that the panel listens to

#define TEST

CommandProcessor command_processor(panelNumber);

volatile bool isReceiving = false;
bool isSleeping = false;
uint8_t readCounter = 0;
uint8_t sleep_count = 0;
volatile uint8_t param1 = 0;
volatile uint8_t param2 = 0;
volatile uint8_t command = 0;     

#define RING_BUFFER_SIZE 32
struct Command {
  uint8_t command;
  uint8_t param1;
  uint8_t param2;
};

Command ring_buffer[RING_BUFFER_SIZE];
volatile uint8_t head = 0;
uint8_t tail = 0;

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
  addCommand(CMD_SHOWID, 0, 0);
#endif // DEBUG  
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

  Command cmd = ring_buffer[tail];
  tail = (tail + 1) % RING_BUFFER_SIZE;
  
  switch(cmd.command) {
    case CMD_SLEEP:
      isSleeping = true;
      digitalWrite(LED_BUILTIN, LOW);
      command_processor.execute(CMD_POWER_OFF, 0, 0);
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
    addCommand(command, param1, param2);
  }
}

void inline addCommand(uint8_t p_command, uint8_t p_param1, uint8_t p_param2) {
  ring_buffer[head] = Command {
      p_command,
      p_param1,
      p_param2
    };
  head = (head + 1) % RING_BUFFER_SIZE;
}

