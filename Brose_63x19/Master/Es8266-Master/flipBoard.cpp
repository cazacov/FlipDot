#include <Arduino.h>
#include <Wire.h>

#include "flipBoard.h"
#include "panelCommands.h"

FlipBoard::FlipBoard()
{
}

void FlipBoard::begin(Panel panelInfo[], uint8_t prows, uint8_t pcolumns)
{
  rows = prows;
  columns = pcolumns;
  panelCount = prows * pcolumns;
  
  for (int i = 0; i < panelCount; i++)
  { 
    panels[i] = panelInfo[i].i2cAddress;
    pins[i] = panelInfo[i].resetPin;
    pinMode(pins[i], INPUT);
  }
  maxx = PANEL_WIDTH * columns;
  maxy = PANEL_HEIGHT * rows;
  
  Wire.begin(D2, D1); // join i2c bus (address optional for master)
  Wire.setClock(400000);
  delay(1000);

  for(int i = 0; i < panelCount; i++)
  {
    // reset panel
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], LOW);
    delay(10);
    digitalWrite(pins[i], HIGH);
  }
  delay(2500);

  for(int i = 0; i < panelCount; i++)
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
      delay(5);
    }
  }
  delay(500);
  for (int y = 0; y < maxy; y++)
  {
    for (int x = 0; x < maxx; x++)
    {
      dot_reset(x, y);
      delay(5);
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
