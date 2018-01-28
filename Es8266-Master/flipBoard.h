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
  uint8_t rtcPanel;
  int maxx;
  int maxy;
  void sendCommand(uint8_t panel, uint8_t command, uint8_t param1, uint8_t param2);
public:
  FlipBoard();
  void begin(uint8_t panels[][2], uint8_t rows, uint8_t columns,uint8_t rtcPanel);
  void dot_set(uint8_t x, uint8_t y);
  void dot_reset(uint8_t x, uint8_t y);
  void test();
  bool readTime();
  void drawDigit(int charNumber, int x0, int y0);
  void drawNumber(int number, int x0, int y0, int minLength);
  void clearScreen();

  int year;
  uint8_t month;
  uint8_t day;
  uint8_t hours;
  uint8_t minutes;
  uint8_t seconds;
};

#endif

