#include <Arduino.h>
#include "flipDotNanoGFX.h"
#include <TimerOne.h>

FlipDotNanoGFX display(28, 24, 1, StackMode::kRow);

const int debugPin1 = 8;
const int debugPin2 = 8;

void setup() {
   Serial.begin(115200);

  display.clearScreen();
  display.endWrite();
  
  pinMode(debugPin1, OUTPUT);
  pinMode(debugPin2, OUTPUT);
  digitalWrite(debugPin1, LOW);
  digitalWrite(debugPin2, HIGH);

//    Timer1.initialize();
//    Timer1.attachInterrupt(timerCallback);
//    Timer1.stop();
  display.fillScreen(0);
  display.endWrite();

}

void loop() {

  digitalWrite(debugPin1, HIGH);

  //delay(5);
  while(!display.updateNext()) {
    //delayMicroseconds(1);
  }

  digitalWrite(debugPin1, LOW);
  delay(1);
  return;

/*

  display.fillScreen(1);
  display.endWrite();
  delay(3000);
  display.fillScreen(0);
  display.endWrite();
  delay(3000);
  */
}