#include <Arduino.h>
#include <Wire.h>
#include "display.h"

XantoI2C* xi2c;

void i2cWriteByteSoftware(uint8_t addr, uint8_t data) {
    xi2c->start();
    xi2c->writeByte(addr);
    xi2c->readAck(); // discard ack
    xi2c->writeByte(data);
    xi2c->readNack(); // discard nack
    xi2c->stop();
}

Display::Display(uint8_t sda_pin, uint8_t scl_pin, uint8_t power_pin, uint8_t lamp_pin) : 
    VM_IIC(112, 16, 500, i2cWriteByteSoftware),
    display_pin(power_pin), 
    backlight_pin(lamp_pin), 
    i2c(scl_pin, sda_pin, 0) {
  pinMode(power_pin, OUTPUT);
  digitalWrite(power_pin, HIGH);
  pinMode(lamp_pin, OUTPUT);
  digitalWrite(lamp_pin, HIGH);
  xi2c = &i2c;
  setModuleMapping(1,2,3,4);
}

void Display::backlightOn() {
  digitalWrite(backlight_pin, LOW);
}

void Display::backlightOff() {
  digitalWrite(backlight_pin, HIGH);
}

void Display::displayOn() {
  digitalWrite(display_pin, LOW);
}

void Display::displayOff() {
  digitalWrite(display_pin, HIGH);
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