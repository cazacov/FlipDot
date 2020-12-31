#ifndef _FLIPBOARD_h
#define _FLIPBOARD_h

#include <stdint.h>
#include <SPI.h> // Adafruit_GFX needs this
#include <Adafruit_I2CDevice.h>
#include <Adafruit_GFX.h>

#define PANEL_WIDTH 21
#define PANEL_HEIGHT 19

struct Panel {
  uint8_t i2cAddress;
  uint8_t resetPin;
};

class FlipBoard : public Adafruit_GFX {
private:
  uint8_t pins[10];
  uint8_t panels[10];
  uint8_t rows;
  uint8_t columns;
  uint8_t panelCount;
  int maxx;
  int maxy;
  void sendCommand(uint8_t panel, uint8_t command, uint8_t param1, uint8_t param2);
  void dot_set(uint8_t x, uint8_t y);
  void dot_reset(uint8_t x, uint8_t y);
public:
  FlipBoard(Panel panelInfo[], uint8_t prows, uint8_t pcolumns);
  void begin();
  void resetPanels();
  void test();
  void powerOn();
  void powerOff();
  void sleep();
  // Override AdafruitGFX
  void drawPixel(int16_t x, int16_t y, uint16_t color);
  void fillScreen(uint16_t color);
};

#endif