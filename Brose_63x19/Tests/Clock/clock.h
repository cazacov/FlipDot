#ifndef _CLOCK_h
#define _CLOCK_h

#include <stdint.h>

class Clock
{
private:
  uint8_t bcdToDec(uint8_t val);
public:
  uint16_t year;
  uint8_t month;
  uint8_t day;
  uint8_t hours;
  uint8_t minutes;
  uint8_t seconds;

  Clock();
  void read(void);
};
#endif

