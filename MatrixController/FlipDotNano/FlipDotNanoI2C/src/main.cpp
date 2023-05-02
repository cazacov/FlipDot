#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_GFX.h>
#include "flipDotNanoGFX.h"
#include "TimerOne.h"
#include "CommandProcessor.h"

FlipDotNanoGFX display(28, 24, 1, StackMode::kRow);

CommandProcessor processor(&display);

const uint8_t STATE_IDLE = 0;
const uint8_t STATE_PULSE = 1;
const uint8_t STATE_DELAY = 2;
const uint8_t STATE_TEST = 2;


const int debugPin = 8;
uint8_t volatile state = STATE_IDLE;
uint8_t address;
char buf[40];

// forward
void receiveEvent(int howMany);
void timerCallback(); 

void setup() {
  Serial.begin(115200);

  address = 0x20 + display.readConfig();
  display.clearScreen();
  sprintf(buf, "0x%02X", address);
  display.printCentered(buf, display.width()/2, display.height()/2);
  display.endWrite();
  
  pinMode(debugPin, OUTPUT);
  digitalWrite(debugPin, LOW);

  Wire.begin(address);
  Wire.onReceive(receiveEvent);
  Serial.print("Listening on address: "); 
  Serial.println(address * 2, HEX);
  delay(2000);
  
  Timer1.initialize();
  Timer1.attachInterrupt(timerCallback);
  Timer1.stop();

  // Test 
  processor.simulateCommand(GfxCommand::kClear, 0);
  processor.simulateCommand(GfxCommand::kSetDelays, 1, 100);
  processor.simulateCommand(GfxCommand::kFillRect, 4, 3, 2, 22, 15);
}

void loop() {
  if (state != STATE_IDLE) { 
    return;
  }

  while (!display.updateNext()) {
    ; // do nothing
  }
  digitalWrite(debugPin, HIGH);
  state = STATE_PULSE;
  Timer1.setPeriod(processor.pulse_microseconds);
}

void receiveEvent(int howMany)
{
  while( Wire.available()) // loop through all but the last
  {
    uint8_t next_byte = Wire.read(); // receive byte as a character
//    Serial.print(next_byte, HEX);         // print the character
//    Serial.print(" ");
    processor.processByte(next_byte);
  }
//  Serial.println();         // print the integer
}

void timerCallback() {
  Timer1.stop();

  if (state == STATE_PULSE) {
    state = STATE_DELAY;
    display.endPulse();
    digitalWrite(debugPin, LOW);
    Timer1.setPeriod(processor.delay_microseconds);
  } else if (state == STATE_DELAY) {
      state = STATE_IDLE;
  }
}