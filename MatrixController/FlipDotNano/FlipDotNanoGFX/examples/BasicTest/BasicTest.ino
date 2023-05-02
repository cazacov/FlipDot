#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_GFX.h>
#include <flipDotNanoGFX.h>

FlipDotNanoGFX display(28, 24, 2, StackMode::kRow);

void setup() {
  Serial.begin(115200);
  display.startWrite();
  display.fillScreen(1); 
  display.endWrite();
  display.startWrite();
  display.fillScreen(0); 
  display.endWrite();
  delay(1000);
}

int color = 1;

void loop() {
  for (int y = 0; y < display.height(); y++) {
    for (int x = 0; x < display.width(); x++) {
      display.startWrite();
      display.drawPixel(x, y, color);
      display.endWrite();
    }
  }

  delay(3000);
  color = 1 - color;
}
