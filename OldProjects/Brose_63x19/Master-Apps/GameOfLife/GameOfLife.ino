#include <Arduino.h>
#include <Wire.h>

#include "flipBoard.h"
#include "textwriter.h"
#include "glcdfonts.h"
#include "Command.h"

FlipBoard flipBoard;
TextWriter textwriter(flipBoard);

Panel panels[] = {
    {10, D5},
    {11, D6},
    {12, D7}};

void setup()
{
  // put your setup code here, to run once:
  flipBoard.begin(panels, 1, 3);  // Panels in 1 row and 3 columns
  flipBoard.clearScreen();
  delay(10000);
  flipBoard.clearScreen();
}

void loop() {
  // put your main code here, to run repeatedly:

}
