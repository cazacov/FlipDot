#include <Arduino.h>
#include <Wire.h>
#include "XantoI2C.h"

#include "VM_IIC.h"

#define DISPLAY_WIDTH   28
#define DISPLAY_HEIGHT  16
#define FLIP_TIME       550

const uint8_t PIN_SCL = 5;
const uint8_t PIN_SDA = 6;

XantoI2C i2c(PIN_SCL, PIN_SDA, 5);

void i2cWriteByteSoftware(uint8_t addr, uint8_t data) {
    i2c.start();
    i2c.writeByte(addr);
    i2c.readAck(); // discard ack
    i2c.writeByte(data);
    i2c.readNack(); // discard nack
    i2c.stop();
}

VM_IIC* flipdot;

void setup() {
  Serial.begin(115200);
  flipdot = new VM_IIC(DISPLAY_WIDTH, DISPLAY_HEIGHT, FLIP_TIME, i2cWriteByteSoftware);
  // put your setup code here, to run once:
  flipdot->setModuleMapping(1, 0, 0, 0);

  // blank display
  delay(500);
  flipdot->clearDisplay();
} 

bool state = true;

void loop() {
  for (int x = 0; x < 28; x++) {
    for (int y = 0; y < 16; y++) {
      flipdot->setDot(x, y, 1);
      flipdot->update();
      delay(50);
    }
  }
  delay(1000);
  for (int x = 0; x < 28; x++) {
    for (int y = 0; y < 16; y++) {
      flipdot->setDot(x, y, 0);
      flipdot->update();
      delay(50);
    }
  }
  delay(1000);
}
