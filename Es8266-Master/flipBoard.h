#ifndef _FLIPBOARD_h
#define _FLIPBOARD_h

#include <stdint.h>

#define PANEL_WIDTH 21
#define PANEL_HEIGHT 19

class FlipBoard
{
private:
  uint8_t pins[10];
  uint8_t panels[10];
  uint8_t rows;
  uint8_t columns;
  int maxx;
  int maxy;
  void sendCommand(uint8_t panel, uint8_t command, uint8_t param1, uint8_t param2);
public:
  FlipBoard();
  void begin(uint8_t panels[][2], uint8_t rows, uint8_t columns);
  void dot_set(uint8_t x, uint8_t y);
  void dot_reset(uint8_t x, uint8_t y);
  void test();
  void clearScreen();
  void powerOn();
  void powerOff();
  void sleep();
};

#endif

