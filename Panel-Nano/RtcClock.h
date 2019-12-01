#ifndef _RTCCLOCK_h
#define _RTCCLOCK_h

#include <Wire.h>
#include <RtcDS3231.h>

RtcDS3231<TwoWire> Rtc(Wire);
RtcDateTime now;
void requestEvent();

class RtcClock {
public:  
  void init();
  void read_time();
};
#endif