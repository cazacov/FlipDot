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

uint8_t panels[][2] = {
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
  flipBoard.clearScreen();
  flipBoard.dot_set(16, 3);
  flipBoard.dot_set(16, 4);
  flipBoard.dot_set(17, 3);
  flipBoard.dot_set(17, 4);
  flipBoard.dot_set(16, 8);
  flipBoard.dot_set(16, 9);
  flipBoard.dot_set(17, 8);
  flipBoard.dot_set(17, 9);

  weather_client.Begin();
}

int last_minute = -1;
float last_temperature = -100;
WeatherIcon last_icon = kUnknown;
int last_read_minute = -100;

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
}

void ShowTime()
{
  textwriter.DrawNumber(clock.hours, 0, 0, 2);
  textwriter.DrawNumber(clock.minutes, 20, 0, 2);
  textwriter.SmallNumber(clock.day, 0, 14, 2);
  flipBoard.dot_set(8, 18);
  textwriter.DrawDigit(clock.dayOfWeek - 1 + 32, 11, 14, 24, 5, DaysOfWeek24x5);
}

void ShowWeather()
{
  char buf[20];
  sprintf(buf, "%d'", (int)weather_client.temperature_current);
  textwriter.DrawText(buf, 42, 14);
  Serial.println((int)(weather_client.weather_icon));
  textwriter.DrawDigit(weather_client.weather_icon + 32, 38, 0, 24, 12, Weather24x12);
}
