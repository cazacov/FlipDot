#include "RtcClock.h"

void RtcClock::init() {
#ifdef SERIAL_TRACE
  Serial.begin(57600);
#endif;  
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  Rtc.Begin();
  if (!Rtc.IsDateTimeValid())
  {
#ifdef SERIAL_TRACE    
    Serial.println("RTC lost confidence in the DateTime!");
#endif    
    Rtc.SetDateTime(compiled);
  }
  if (!Rtc.GetIsRunning())
  {
#ifdef SERIAL_TRACE    
    Serial.println("RTC was not actively running, starting now");
#endif    
    Rtc.SetIsRunning(true);
  }
  if (!Rtc.GetIsRunning())
  {
#ifdef SERIAL_TRACE    
    Serial.println("RTC was not actively running, starting now");
#endif    
    Rtc.SetIsRunning(true);
  }
  now = Rtc.GetDateTime();
  if (now < compiled)
  {
#ifdef SERIAL_TRACE    
    Serial.println("RTC is older than compile time!  (Updating DateTime)");
#endif    
    Rtc.SetDateTime(compiled);
  }
  else if (now > compiled)
  {
#ifdef SERIAL_TRACE    
    Serial.println("RTC is newer than compile time. (this is expected)");
#endif    
  }
  else if (now == compiled)
  {
#ifdef SERIAL_TRACE    
    Serial.println("RTC is the same as compile time! (not expected but all is fine)");
#endif    
  }

  // never assume the Rtc was last configured by you, so
  // just clear them to your needed state
  Rtc.Enable32kHzPin(false);
  Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeNone);
  Wire.onRequest(requestEvent);
}

void RtcClock::read_time() {
  now = Rtc.GetDateTime();
}

void requestEvent() {
  char datestring[20];

  sprintf(datestring,
             "%04u-%02u-%02u %02u:%02u:%02u",
             now.Year(),
             now.Month(),
             now.Day(),
             now.Hour(),
             now.Minute(),
             now.Second() );
  Wire.write(datestring); 
}