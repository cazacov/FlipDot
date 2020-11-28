#include <Arduino.h>
#include <Wire.h>

#include "flipBoard.h"

FlipBoard flipBoard;

uint8_t panels[][2] = {
  { 10, 4 },
  { 11, 3 },
  { 12, 2 }
};


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
  flipBoard.readTime();
  sprintf(date, "%04d-%02d-%02d %02d:%02d:%02d", flipBoard.year, flipBoard.month, flipBoard.day, flipBoard.hours, flipBoard.minutes, flipBoard.seconds);

  flipBoard.drawNumber(flipBoard.hours, 13, 2, 2);
  flipBoard.drawNumber(flipBoard.minutes, 27, 2, 2);
  flipBoard.drawNumber(flipBoard.seconds, 41, 2, 2);

  flipBoard.drawNumber(flipBoard.day, 9, 12, 2);
  flipBoard.drawNumber(flipBoard.month, 22, 12, 2);
  flipBoard.drawNumber(flipBoard.year, 36, 12, 2);
  Serial.println(date);
}
