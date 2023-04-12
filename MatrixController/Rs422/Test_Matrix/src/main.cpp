#include <Arduino.h>
#include <Wire.h>
#include "XantoI2C.h"

#include "VM_IIC.h"

#define DISPLAY_WIDTH   28
#define DISPLAY_HEIGHT  19
#define FLIP_TIME       250

const uint8_t PIN_SCL = 21;
const uint8_t PIN_SDA = 5;

XantoI2C i2c(PIN_SCL, PIN_SDA, 0);

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
  pinMode(23, OUTPUT);
  digitalWrite(23, LOW);
  delay(100);


  flipdot = new VM_IIC(DISPLAY_WIDTH, DISPLAY_HEIGHT, FLIP_TIME, i2cWriteByteSoftware);
  // put your setup code here, to run once:
  flipdot->setModuleMapping(1);

  delay(100);    
  // blank display
  flipdot->clearDisplay();
} 

void loop() {
  for (int x = 0; x < DISPLAY_WIDTH; x++) {
    for (int y = 0; y < DISPLAY_HEIGHT; y++) {
      flipdot->setDot(x, y, 1);
      flipdot->update();
      delay(1);
    }
  }
  delay(1000);
  for (int x = 0; x < DISPLAY_WIDTH; x++) {
    for (int y = 0; y < DISPLAY_HEIGHT; y++) {
      flipdot->setDot(x, y, 0);
      flipdot->update();
      delay(1);
    }
  }
  delay(1000);
}
