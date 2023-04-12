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
  //Der Wochentag wird hier nicht ausgelesen da dieses mit 
  //dem Modul RTC DS3231 nicht über die Wire.h zuverlässig funktioniert.
  /* wochentag  =*/ bcdToDec(Wire.read());
  day        = bcdToDec(Wire.read());
  month      = bcdToDec(Wire.read());
  year       = bcdToDec(Wire.read())+2000; 
}

