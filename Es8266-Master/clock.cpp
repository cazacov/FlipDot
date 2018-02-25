#include "clock.h"
#include <Wire.h>

#define RTC_I2C_ADDRESS 0x68

Clock::Clock()
{
  seconds = minutes = hours = day = month = year = 0;
}

uint8_t Clock::bcdToDec(uint8_t val){
  return ( (val/16*10) + (val%16) );
}

void Clock::read(void) {
  Wire.beginTransmission(RTC_I2C_ADDRESS);
  Wire.write(0);
  Wire.endTransmission();
  Wire.requestFrom(RTC_I2C_ADDRESS, 7);

  seconds    = bcdToDec(Wire.read() & 0x7f);
  minutes     = bcdToDec(Wire.read()); 
  hours     = bcdToDec(Wire.read() & 0x3f); 
  // Reading day of week is not stable
  bcdToDec(Wire.read());
  day        = bcdToDec(Wire.read());
  month      = bcdToDec(Wire.read());
  year       = bcdToDec(Wire.read())+2000; 


  // https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week#Sakamoto's_methods

  int y = year;
  int m = month;
  int d = day;

  static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
  y -= m < 3;
  dayOfWeek = (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
  
  if (dayOfWeek == 0)
  {
    // Sunday
    dayOfWeek = 7; 
  }
}

