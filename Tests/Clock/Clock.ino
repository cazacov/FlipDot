#include <Arduino.h>
#include <Wire.h>
#include "clock.h"

Clock clock;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  Wire.begin(D2,D1);
}

void loop() {
  // put your main code here, to run repeatedly:
  clock.read();

  char buf[30];
  sprintf(buf, "%02d.%02d.%04d %02d:%02d:%02d", 
    clock.day,
    clock.month,
    clock.year,
    clock.hours, 
    clock.minutes, 
    clock.seconds);
   Serial.println(buf);
   delay(1000);
}
