#include <Arduino.h>
#include <Wire.h>
#include "display.h"

XantoI2C* xi2c;

#define DISPLAY_WIDTH 140
#define DISPLAY_HEIGHT 19
#define FLIP_TIME 500

void i2cWriteByteSoftware(uint8_t addr, uint8_t data) {
    xi2c->start();
    xi2c->writeByte(addr);
    xi2c->readAck(); // discard ack
    xi2c->writeByte(data);
    xi2c->readNack(); // discard nack
    xi2c->stop();
}

Display::Display(uint8_t sda_pin, uint8_t scl_pin, uint8_t power_pin, uint8_t lamp_pin) : 
    VM_IIC(DISPLAY_WIDTH, DISPLAY_HEIGHT, FLIP_TIME, i2cWriteByteSoftware),
    display_pin(power_pin), 
    backlight_pin(lamp_pin), 
    i2c(scl_pin, sda_pin, 0),
    is_display_on(false),
    is_backlight_on(false) {
  pinMode(power_pin, OUTPUT);
  pinMode(lamp_pin, OUTPUT);  
  setDisplayPower(false);
  setBacklightPower(false);
  xi2c = &i2c;
  setModuleMapping(1,2,3,4,5);
}

void Display::setDisplayPower(bool new_value) {
  is_display_on = new_value;
  digitalWrite(display_pin, is_display_on ? LOW : HIGH);
}

void Display::setBacklightPower(bool new_value) {
  is_backlight_on = new_value;
  digitalWrite(backlight_pin, is_display_on ? LOW : HIGH);
}

bool Display::getBacklightPower() {
  return is_backlight_on;
}

bool Display::getDisplayPower() {
  return is_display_on;
}

std::vector<uint8_t> Display::getPixels() {
  return std::vector<uint8_t> (frameBuffer, frameBuffer + frameBufferSize);
}

void Display::setPixels(std::vector<uint8_t> &newFrameBuffer) {
  if (newFrameBuffer.size() == frameBufferSize) {
    memcpy(frameBuffer, newFrameBuffer.data(), frameBufferSize);
    update();
  }
}

void Display::cls() {
  memset(frameBuffer, 0, frameBufferSize);
}

void Display::test() {
  memset(frameBuffer, 0xFF, frameBufferSize);
  update();
}
