#include <Arduino.h>
#include <Wire.h>

#include "flipBoard.h"
#include "clock.h"
#include "textwriter.h"
#include "glcdfonts.h"
#include "weatherClient.h"

FlipBoard flipBoard;
TextWriter textwriter(flipBoard);
WeatherClient weather_client;

Panel panels[] = {
    {10, D5},
    {11, D6},
    {12, D7}};

Clock clock;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  flipBoard.begin(panels, 1, 3);
  delay(2000);
  flipBoard.test();
  delay(2000);
  flipBoard.clearScreen();
  flipBoard.dot_set(18, 3);
  flipBoard.dot_set(18, 4);
  flipBoard.dot_set(19, 3);
  flipBoard.dot_set(19, 4);
  flipBoard.dot_set(18, 8);
  flipBoard.dot_set(18, 9);
  flipBoard.dot_set(19, 8);
  flipBoard.dot_set(19, 9);
#ifdef SHOW_WEATHER  
  weather_client.Begin();
#endif  
}

int last_minute = -1;
float last_temperature = -100;
WeatherIcon last_icon = kUnknown;
int last_read_minute = -100;
bool isPowered = true;
bool isSleeping = false;

void ShowTime();
void ShowWeather();

void loop()
{
  clock.read();
  delay(500);

  if (clock.minutes != last_minute)
  {
    last_minute = clock.minutes;
    ShowTime();
  }

  int minute = clock.hours * 60 + clock.minutes;

#ifdef SHOW_WEATHER  
  if (minute < last_read_minute || minute - last_read_minute > 10)
  {
    last_read_minute = minute;
    weather_client.GetWeatherData();
  }

  if (last_temperature != weather_client.temperature_current || last_icon != weather_client.weather_icon)
  {
    last_temperature = weather_client.temperature_current;
    last_icon = weather_client.weather_icon;
    ShowWeather();
  }
#endif  

#ifdef LOWPOWER
  if (isPowered && clock.seconds > 0 && clock.seconds < 55)
  {
    isPowered = false;
    flipBoard.powerOff();
  }
  else if (!isPowered && clock.seconds < 1 || clock.seconds > 55)
  {
    isPowered = true;
    flipBoard.powerOn();
  }
  if (!isSleeping && clock.seconds == 2)
  {
    isSleeping = true;
    flipBoard.sleep();
  }
  if (isSleeping && clock.seconds > 51)
  {
    // Nanos wake up after 48 seconds
    isSleeping = false; 
  }
#endif  
}

void ShowTime()
{
  textwriter.DrawNumber(clock.hours, 2, -1, 2);
  textwriter.DrawNumber(clock.minutes, 22, -1, 2);
  flipBoard.dot_set(8, 18);
  textwriter.DrawDigit(clock.dayOfWeek - 1 + 32, 0, 14, 10, 5, DaysOfWeeksRu10x5);
  textwriter.SmallNumber(clock.day, 12, 14, 2);
  flipBoard.dot_set(20, 18);
  textwriter.DrawDigit(clock.month - 1 + 32, 23, 14, 15, 5, MonthsRu15x5);

}

void ShowWeather()
{
  char buf[20];
  sprintf(buf, "%d'", (int)weather_client.temperature_current);
  textwriter.DrawText(buf, 46, 14);
  textwriter.DrawDigit((int)(weather_client.weather_icon) + 32, 39, 0, 24, 12, Weather24x12);
}
