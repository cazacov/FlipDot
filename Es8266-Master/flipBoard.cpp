#include <Arduino.h>
#include <Wire.h>

#include "flipBoard.h"
#include "panelCommands.h"

FlipBoard::FlipBoard()
{
  rtcPanel = 0;
}

void FlipBoard::begin(uint8_t panelInfo[][2], uint8_t prows, uint8_t pcolumns, uint8_t prtcPanel)
{
  rows = prows;
  columns = pcolumns;
  rtcPanel = prtcPanel;
  
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

bool FlipBoard::readTime()
{
  if (!rtcPanel)
  {
    return false;
  }
  
  char date[20];
  int count = 0;

  sendCommand(rtcPanel, CMD_TIME_GET, 0,0);
  delay(5);

  Wire.requestFrom((int)rtcPanel, 19);
  delay(2);
  while (Wire.available() && count < 20) { // slave may send less than requested
    char ch =  Wire.read();
    date[count++] = ch;
  }
  while (Wire.available())
  {
    Wire.read();
    Serial.print(".");
  }
  
  if (count == 19)
  {
    date[4] = 0;
    year = atoi(date);
    date[7] = 0;
    month = atoi(date + 5);
    date[10] = 0;
    day = atoi(date + 8);
    date[13] = 0;
    hours = atoi(date + 11);
    date[16] = 0;
    minutes = atoi(date + 14);
    date[19] = 0;
    seconds = atoi(date + 17);

    Serial.print(year);
    return true;
  }
  return false;
} 

const uint8_t  ziffer[][4] = {
  { 0x7C , 0x82 , 0x82 , 0x7C }, // 0
  { 0x00 , 0x42 , 0xFE , 0x02 }, // 1
  { 0x46 , 0x8A , 0x92 , 0x62 }, // 2
  { 0x44 , 0x82 , 0x92 , 0x6C }, // 3
  { 0x30 , 0x50 , 0x90 , 0xFE }, // 4
  { 0xE4 , 0xA2 , 0xA2 , 0x9C }, // 5
  { 0x7C , 0xA2 , 0xA2 , 0x1C }, // 6
  { 0x86 , 0x88 , 0x90 , 0xE0 }, // 7
  { 0x6C , 0x92 , 0x92 , 0x6C }, // 8
  { 0x70 , 0x8A , 0x8A , 0x7C }, // 9
};

void FlipBoard::drawDigit(int charNumber, int x0, int y0) {
  uint8_t anzeigeByte = 0;

  for (int xc = 0; xc < 4; xc++) {
    anzeigeByte = ziffer[charNumber][xc];
    for (int yc = 0; yc < 7; yc ++) {
      if ((anzeigeByte & 128) == 128) {
        dot_set(x0 + xc, y0 + yc);
      }
      else {
        dot_reset(x0 + xc, y0 + yc);
      }
      anzeigeByte = anzeigeByte << 1; //select next bit
    }
  }
}

void FlipBoard::drawNumber(int number, int x0, int y0, int minLength) {
  int digitCount = 0;
  int n = number;
  while (n > 0)
  {
    digitCount++;
    n /= 10;
  }
  if (!digitCount)
  {
    digitCount = 1;
  }
  if (digitCount < minLength)
  {
    digitCount = minLength;
  }

  while(digitCount)
  {
    drawDigit(number % 10, x0 + digitCount * 5 - 5, y0);
    number /= 10;
    digitCount--;
  }
}


