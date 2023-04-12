#include <Arduino.h>
#include <Wire.h>
#include "XantoI2C.h"

#include "VM_IIC.h"

#define DISPLAY_WIDTH   112
#define DISPLAY_HEIGHT  16
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
  flipdot = new VM_IIC(DISPLAY_WIDTH, DISPLAY_HEIGHT, FLIP_TIME, i2cWriteByteSoftware);
  flipdot->setModuleMapping(1, 2, 3, 4);
  delay(100);    
  flipdot->clearDisplay();
} 

void loop() {
  char buf[2] = "0";

  flipdot->fillScreen(0);
  flipdot->setTextColor(1,0);
  for (int i = 0; i < 18; i++) {
    buf[0] = 'A' + i;
    flipdot->setCursor(1 + i*6, 1 + (i % 8));
    flipdot->print(buf);
  }
  flipdot->update();
  delay(5000);
  flipdot->fillScreen(1);
  flipdot->setTextColor(0,1);
  for (int i = 0; i < 18; i++) {
    buf[0] = 'A' + i;
    flipdot->setCursor(1 + i*6, 1 + (i % 8));
    flipdot->print(buf);
  }
  flipdot->update();
  delay(5000);
}
