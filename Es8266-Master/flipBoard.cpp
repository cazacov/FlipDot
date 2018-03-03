#include <Arduino.h>
#include <Wire.h>

#include "flipBoard.h"
#include "panelCommands.h"

FlipBoard::FlipBoard()
{
}

void FlipBoard::begin(uint8_t panelInfo[][2], uint8_t prows, uint8_t pcolumns)
{
  rows = prows;
  columns = pcolumns;
  
  for (int panelCount = 0; panelCount < rows * columns; panelCount++)
  { 
    panels[panelCount] = panelInfo[panelCount][0];
    pins[panelCount] = panelInfo[panelCount][1];
    pinMode(pins[panelCount], INPUT);
  }
  maxx = PANEL_WIDTH * columns;
  maxy = PANEL_HEIGHT * rows;
  
  Wire.begin(D2, D1); // join i2c bus (address optional for master)
  Wire.setClock(400000);
  delay(1000);

  for(int i = 0; i < rows * columns; i++)
  {
    // reset panel
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], LOW);
    delay(10);
    digitalWrite(pins[i], HIGH);
  }
  delay(2000);

  for(int i = 0; i < rows * columns; i++)
  {
    sendCommand(i, CMD_DURATION_SET, 5, 0);
    sendCommand(i, CMD_ALL_RESET, 0, 0);
  }
  delay(200);
}

void FlipBoard::sendCommand(uint8_t panel, uint8_t command, uint8_t param1, uint8_t param2)
{
  Wire.beginTransmission(panels[panel]); 
  Wire.write(command);              
  Wire.write(param1);
  Wire.write(param2);
  Wire.endTransmission();  
}

void FlipBoard::dot_set(uint8_t x, uint8_t y)
{
  if (x < 0 || x >= maxx || y < 0 || y >= maxy)
  {
    return;
  }
  uint8_t panel = (y / PANEL_HEIGHT) * columns + (x / PANEL_WIDTH);
  sendCommand(panel, CMD_DOT_SET, (x % PANEL_WIDTH)+1, (y % PANEL_HEIGHT)+1);
  delay(2);
}  

void FlipBoard::dot_reset(uint8_t x, uint8_t y) 
{
  if (x < 0 || x >= maxx || y < 0 || y >= maxy)
  {
    return;
  }
  uint8_t panel = (y / PANEL_HEIGHT) * columns + (x / PANEL_WIDTH);
  sendCommand(panel, CMD_DOT_RESET, (x % PANEL_WIDTH)+1, (y % PANEL_HEIGHT)+1);
  delay(2);
}

void FlipBoard::clearScreen() {
  for(int i = 0; i < rows * columns; i++)
  {
    sendCommand(i, CMD_ALL_RESET, 0, 0);
  }    
  delay(100);
}

void FlipBoard::test() 
{
  for (int y = 0; y < maxy; y++)
  {
    for (int x = 0; x < maxx; x++)
    {
      dot_set(x, y);
      delay(50);
    }
  }
  delay(500);
  for (int y = 0; y < maxy; y++)
  {
    for (int x = 0; x < maxx; x++)
    {
      dot_reset(x, y);
      delay(50);
    }
  }
}

void FlipBoard::powerOn()
{
  for(int i = 0; i < rows * columns; i++)
  {
    sendCommand(i, CMD_POWER_ON, 0, 0);
  }
}

void FlipBoard::powerOff() {
  for(int i = 0; i < rows * columns; i++)
  {
    sendCommand(i, CMD_POWER_OFF, 0, 0);
  }
}

void FlipBoard::sleep() {
  for(int i = 0; i < rows * columns; i++)
  {
    sendCommand(i, CMD_SLEEP, 0, 0);
  }
}



