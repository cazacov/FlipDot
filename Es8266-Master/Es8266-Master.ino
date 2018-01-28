#include <Arduino.h>
#include <Wire.h>

#include "flipBoard.h"
#include "clock.h"

FlipBoard flipBoard;

uint8_t panels[][2] = {
  { 10, D5 },
  { 11, D6 },
  { 12, D7 }
};

Clock clock;

void setup() {
  // put your setup code here, to run once:
  flipBoard.begin(panels, 1, 3, 12);
  Serial.begin(57600);
  delay(2000);
  flipBoard.clearScreen();
  flipBoard.dot_set(24,4);
  flipBoard.dot_set(24,6);
  flipBoard.dot_set(38,4);
  flipBoard.dot_set(38,6);
}

void loop() {
  char date[20];
  delay(200);
  clock.read();
  sprintf(date, "%04d-%02d-%02d %02d:%02d:%02d", flipBoard.year, flipBoard.month, flipBoard.day, flipBoard.hours, flipBoard.minutes, flipBoard.seconds);

  flipBoard.drawNumber(clock.hours, 13, 2, 2);
  flipBoard.drawNumber(clock.minutes, 27, 2, 2);
  flipBoard.drawNumber(clock.seconds, 41, 2, 2);

  flipBoard.drawNumber(clock.day, 9, 12, 2);
  flipBoard.drawNumber(clock.month, 22, 12, 2);
  flipBoard.drawNumber(clock.year, 36, 12, 2);
  Serial.println(date);
}
