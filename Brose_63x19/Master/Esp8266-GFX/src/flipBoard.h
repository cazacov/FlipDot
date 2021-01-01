#ifndef _FLIPBOARD_h
#define _FLIPBOARD_h

#include <stdint.h>
#include <SPI.h> // Adafruit_GFX needs this
#include <Adafruit_I2CDevice.h>
#include <Adafruit_GFX.h>

struct Panel {
  uint8_t i2cAddress;
  uint8_t resetPin;
};

class FlipBoard : public Adafruit_GFX {
private:
  uint8_t *resetPins;
  uint8_t *panelAddrs;
  uint8_t rows;
  uint8_t columns;
  uint8_t panelCount;
  uint8_t panelWidth;
  uint8_t panelHeight;
  uint16_t maxx;
  uint16_t maxy;

  uint8_t* frameBuffer;
  uint8_t* screenBuffer;
  uint16_t frameBufferSize;
  uint16_t frameBufferWidth;

  void sendCommand(uint8_t panel, uint8_t command, uint8_t param1, uint8_t param2);
  void dot_set(uint16_t x, uint16_t y);
  void dot_reset(uint16_t x, uint16_t y);
  void writeDot(int16_t x, int16_t y, bool state);
public:
  FlipBoard(uint8_t panel_width, uint8_t panel_height, Panel panelInfo[], uint8_t prows, uint8_t pcolumns);
  void begin();
  void resetPanels();
  void test();
  void powerOn();
  void powerOff();
  void sleep();
  // Override AdafruitGFX
  void drawPixel(int16_t x, int16_t y, uint16_t color);
  void writePixel(int16_t x, int16_t y, uint16_t color);
  void fillScreen(uint16_t color);
  void endWrite(void);  
};

#endif