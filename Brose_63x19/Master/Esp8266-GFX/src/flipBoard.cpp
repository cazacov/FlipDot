#include <Arduino.h>
#include <Wire.h>

#include "flipBoard.h"
#include "panelCommands.h"

char buffer[50];
FlipBoard::FlipBoard(Panel panelInfo[], uint8_t prows, uint8_t pcolumns) 
  : Adafruit_GFX(pcolumns * PANEL_WIDTH, prows * PANEL_HEIGHT)
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
}

void FlipBoard::resetPanels() {
  for (int i = 0; i < panelCount; i++)
  { 
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], LOW);
  }
  delay(5);
  for (int i = 0; i < panelCount; i++)
  { 
    digitalWrite(pins[i], HIGH);
  }
}

void FlipBoard::begin() {
  Serial.println(panelCount);
  Serial.println("FlipBoard begin");
  delay(2000);
  sprintf(buffer, "GFX width:%d, height:%d", WIDTH, HEIGHT);
  Serial.println(buffer);
  delay(3000);
  for(int i = 0; i < panelCount; i++)
  {
    sendCommand(i, CMD_START, 5, 0);
    sendCommand(i, CMD_DURATION_SET, 5, 0);
    delay(5);
    sprintf(buffer, "%d START", i);
    Serial.println(buffer);
  }
  delay(1000);
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
  uint8_t panel_x = (x % PANEL_WIDTH)  + 1;
  uint8_t panel_y = (y % PANEL_HEIGHT) + 1;
  sendCommand(panel, CMD_DOT_SET, panel_x, panel_y );

  sprintf(buffer,"SET %d,%d -> %d,%d,%d", x,y,panel,panel_x, panel_y);
  Serial.println(buffer);

}  

void FlipBoard::dot_reset(uint8_t x, uint8_t y) 
{
  if (x < 0 || x >= maxx || y < 0 || y >= maxy)
  {
    return;
  }
  uint8_t panel = (y / PANEL_HEIGHT) * columns + (x / PANEL_WIDTH);
  uint8_t panel_x = (x % PANEL_WIDTH)  + 1;
  uint8_t panel_y = (y % PANEL_HEIGHT) + 1;
  sendCommand(panel, CMD_DOT_RESET, panel_x, panel_y );
  sprintf(buffer,"RESET %d,%d -> %d,%d,%d", x,y,panel,panel_x, panel_y);
  Serial.println(buffer);

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

void FlipBoard::drawPixel(int16_t x, int16_t y, uint16_t color) {
  color ? dot_set(x, y) : dot_reset(x,y);
  delay(5);
}

void FlipBoard::fillScreen(uint16_t color) {
  Serial.println("Full screen call");
  for(int i = 0; i < rows * columns; i++)
  {
    sendCommand(i, color ? CMD_ALL_SET : CMD_ALL_RESET, 0, 0);
  }    
  delay(100);
}