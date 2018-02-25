#include <Arduino.h>
#include <Wire.h>

#include "flipBoard.h"
#include "clock.h"
#include "textwriter.h"

FlipBoard flipBoard;
TextWriter textwriter(flipBoard);

uint8_t panels[][2] = {
  { 10, D5 },
  { 11, D6 },
  { 12, D7 }
};

Clock clock;

void setup() {
  // put your setup code here, to run once:
  flipBoard.begin(panels, 1, 3);
  Serial.begin(57600);
  delay(2000);
  flipBoard.clearScreen();
  flipBoard.dot_set(16,3);
  flipBoard.dot_set(16,4);
  flipBoard.dot_set(17,3);
  flipBoard.dot_set(17,4);
  flipBoard.dot_set(16,8);
  flipBoard.dot_set(16,9);
  flipBoard.dot_set(17,8);
  flipBoard.dot_set(17,9);
}

void loop() {
  char date[20];
  delay(200);
  clock.read();

  textwriter.DrawNumber(clock.hours, 0, 0, 2);
  textwriter.DrawNumber(clock.minutes, 20, 0, 2);
  
  /*
  flipBoard.drawNumber(clock.hours, 13, 2, 2);
  flipBoard.drawNumber(clock.minutes, 27, 2, 2);
  flipBoard.drawNumber(clock.seconds, 41, 2, 2);

  flipBoard.drawNumber(clock.day, 9, 12, 2);
  flipBoard.drawNumber(clock.month, 22, 12, 2);
  flipBoard.drawNumber(clock.year, 36, 12, 2);
  */

  delay(5000);
}
