#include <Arduino.h>

#include "flipBoard.h"

Panel panels[] = {
    {10, D5},
    {12, D6},
    {14, D7}};

FlipBoard flipBoard(panels, 1, 3);

void setup()
{
  Serial.begin(115200);
  Serial.println("Serial started");
  delay(1000);
  flipBoard.begin();  
}

void loop() {
  Serial.println("loop");
  delay(3000);
  flipBoard.fillScreen(0);
  Serial.println("Screen cleared");
  delay(3000);
  flipBoard.setCursor(0,00);
  Serial.println("Cursor set");
  flipBoard.println("Hallo Welt");
  Serial.println("text printed");

  delay(100000);
  Serial.print("Should never be here");
}