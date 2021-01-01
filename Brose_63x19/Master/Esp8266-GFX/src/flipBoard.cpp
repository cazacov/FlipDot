#include <Arduino.h>
#include <Wire.h>

#include "flipBoard.h"
#include "panelCommands.h"

char buffer[50];
FlipBoard::FlipBoard(uint8_t panel_width, uint8_t panel_height, Panel panelInfo[], uint8_t prows, uint8_t pcolumns) 
  : panelWidth(panel_width), panelHeight(panel_height), rows(prows), columns(pcolumns),
  Adafruit_GFX(pcolumns * panel_width, prows * panel_height)
{
  panelCount = prows * pcolumns;
  panelAddrs = (uint8_t*) malloc(panelCount);
  resetPins = (uint8_t*) malloc(panelCount);
  
  for (int i = 0; i < panelCount; i++)
  { 
    panelAddrs[i] = panelInfo[i].i2cAddress;
    resetPins[i] = panelInfo[i].resetPin;
    pinMode(resetPins[i], INPUT);
  }
  maxx = (uint16_t)panel_width * columns;
  maxy = (uint16_t)panel_height * rows;
  
  Wire.begin(D2, D1); // join i2c bus (address optional for master)
  Wire.setClock(400000);

  frameBufferWidth = (maxx + 7) / 8;
  frameBufferSize = frameBufferWidth * maxy;
  frameBuffer = (uint8_t*)malloc(frameBufferSize);
  screenBuffer = (uint8_t*)malloc(frameBufferSize);

  sprintf(buffer, "frameBufferWidth: %d", frameBufferWidth);
  Serial.println(buffer);
  sprintf(buffer, "frameBufferSize: %d", frameBufferSize);
  Serial.println(buffer);
}

void FlipBoard::resetPanels() {
  for (uint8_t i = 0; i < panelCount; i++)
  { 
    pinMode(resetPins[i], OUTPUT);
    digitalWrite(resetPins[i], LOW);
  }
  delay(5);
  for (uint8_t i = 0; i < panelCount; i++)
  { 
    digitalWrite(resetPins[i], HIGH);
  }
}

void FlipBoard::begin() {
  delay(5000);
  for(uint8_t i = 0; i < panelCount; i++)
  {
    sendCommand(i, CMD_START, 5, 0);
    sendCommand(i, CMD_DURATION_SET, 3, 0);
    sendCommand(i, CMD_ALL_RESET, 0, 0);
    delay(5);
  }
  memset(frameBuffer, 0, frameBufferSize);
  memset(screenBuffer, 0, frameBufferSize);
}

void FlipBoard::sendCommand(uint8_t panel, uint8_t command, uint8_t param1, uint8_t param2)
{
  Wire.beginTransmission(panelAddrs[panel]); 
  Wire.write(command);              
  Wire.write(param1);
  Wire.write(param2);
  Wire.endTransmission();  
}

void FlipBoard::dot_set(uint16_t x, uint16_t y)
{
  if (x < 0 || x >= maxx || y < 0 || y >= maxy)
  {
    return;
  }
  uint8_t panel = (y / panelHeight) * columns + (x / panelWidth);
  uint8_t panel_x = (x % panelWidth)  + 1;
  uint8_t panel_y = (y % panelHeight) + 1;
  sendCommand(panel, CMD_DOT_SET, panel_x, panel_y );
#ifdef SERIAL_TRACE  
  sprintf(buffer,"SET %d,%d -> %d,%d,%d", x,y,panel,panel_x, panel_y);
  Serial.println(buffer);
#endif
}  

void FlipBoard::dot_reset(uint16_t x, uint16_t y) 
{
  if (x < 0 || x >= maxx || y < 0 || y >= maxy)
  {
    return;
  }
  uint8_t panel = (y / panelHeight) * columns + (x / panelWidth);
  uint8_t panel_x = (x % panelWidth)  + 1;
  uint8_t panel_y = (y % panelHeight) + 1;
  sendCommand(panel, CMD_DOT_RESET, panel_x, panel_y );
#ifdef SERIAL_TRACE    
  sprintf(buffer,"RESET %d,%d -> %d,%d,%d", x,y,panel,panel_x, panel_y);
  Serial.println(buffer);
#endif
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

void FlipBoard::writeDot(int16_t x, int16_t y, bool state) {
  state ? dot_set(x, y) : dot_reset(x,y);
}

// overwrites Adafruit
void FlipBoard::drawPixel(int16_t x, int16_t y, uint16_t color) {
  if(x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
    if(color) {
        frameBuffer[y * frameBufferWidth + x/8] |= 0x80 >> (x % 8);
        screenBuffer[y * frameBufferWidth + x/8] |= 0x80 >> (x % 8);
    } else {
        frameBuffer[y * frameBufferWidth + x/8] &= ~(0x80 >> (x % 8));
        screenBuffer[y * frameBufferWidth + x/8] &= ~(0x80 >> (x % 8));
    }
  }
  writeDot(x, y, color);
  delay(1);
}

// overwrites Adafruit
void FlipBoard::writePixel(int16_t x, int16_t y, uint16_t color) {
  if(x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
    if(color) {
      frameBuffer[y * frameBufferWidth + x/8] |= 0x80 >> (x % 8);
    } else {
      frameBuffer[y * frameBufferWidth + x/8] &= ~(0x80 >> (x % 8));
    }
  }
}

void FlipBoard::endWrite(void) {
  uint16_t dotsFlipped = 0;
  for(uint16_t x = 0; x < WIDTH; x++) {
      for(uint16_t y = 0; y < HEIGHT; y++) {
          uint8_t screenState = (screenBuffer[y * frameBufferWidth + x/8] & (0x80 >> (x % 8)));
          uint8_t frameState = (frameBuffer[y * frameBufferWidth + x/8] & (0x80 >> (x % 8)));
          if(screenState != frameState) {
              writeDot(x, y, frameState);
              dotsFlipped++;
          }
      }
  }
  memcpy(screenBuffer, frameBuffer, frameBufferSize); 
  delay(dotsFlipped);
}

// overwrites Adafruit
void FlipBoard::fillScreen(uint16_t color) {
#ifdef SERIAL_TRACE     
  Serial.println("Full screen call");
#endif  
  for(int i = 0; i < rows * columns; i++)
  {
    sendCommand(i, color ? CMD_ALL_SET : CMD_ALL_RESET, 0, 0);
  }    
  if (color) {
    memset(frameBuffer, 0xFF, frameBufferSize);
    memset(screenBuffer, 0xFF, frameBufferSize);
  }
  else {
    memset(frameBuffer, 0, frameBufferSize);
    memset(screenBuffer, 0, frameBufferSize);
  }
  delay(100);
}