#include <Wire.h>

#include "display.h"

void Display::i2cWriteByteSoftware(uint8_t addr, uint8_t data) {
    i2c.start();
    i2c.writeByte(addr);
    i2c.readAck(); // discard ack
    i2c.writeByte(data);
    i2c.readNack(); // discard nack
    i2c.stop();
}

Display::Display(uint8_t sda_pin, uint8_t scl_pin, uint8_t power_pin, uint8_t lamp_pin) : 
    display_pin(power_pin), 
    backlight_pin(lamp_pin), 
    i2c(scl_pin, sda_pin, 0) {
  pinMode(power_pin, OUTPUT);
  digitalWrite(power_pin, LOW);
  pinMode(lamp_pin, OUTPUT);
  digitalWrite(lamp_pin, LOW);
}

void Display::backlightOn() {
  digitalWrite(backlight_pin, HIGH);
}

void Display::backlightOff() {
  digitalWrite(backlight_pin, LOW);
}

void Display::displayOn() {
  digitalWrite(display_pin, HIGH);
}

void Display::displayOff() {
  digitalWrite(display_pin, LOW);
}