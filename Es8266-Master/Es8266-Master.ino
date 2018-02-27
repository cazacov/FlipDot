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
  { 10, D5 },
  { 11, D6 },
  { 12, D7 }
};

Clock clock;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  flipBoard.begin(panels, 1, 3);
  delay(2000);
  flipBoard.clearScreen();
  flipBoard.dot_set(16,3);
  flipBoard.dot_set(16,4);
  flipBoard.dot_set(17,3);
  flipBoard.dot_set(17,4);
  flipBoard.dot_set(16,8);
  flipBoard.dot_set(16,9);
  flipBoard.dot_set(17,8);
  flipBoard.dot_set(17,9);

  weather_client.Begin();
}

int last_minute = -1;

void ShowTime();

void loop() {
  clock.read();
  delay(5000);

  if (clock.minutes != last_minute)
  {
      last_minute = clock.minutes;
      //ShowTime();
  }
  weather_client.GetWeatherData();
  delay(10000);
}

void ShowTime() {
   textwriter.DrawNumber(clock.hours, 0, 0, 2);
  textwriter.DrawNumber(clock.minutes, 20, 0, 2);
  textwriter.SmallNumber(clock.day, 0, 14, 2);
  textwriter.DrawDigit(clock.dayOfWeek - 1, 10, 14, 24, 5, DaysOfWeek24x5);
}
