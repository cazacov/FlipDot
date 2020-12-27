#include <Arduino.h>
#include <Wire.h>
#include "XantoI2C.h"

#include "VM_IIC.h"

#define DISPLAY_WIDTH   56
#define DISPLAY_HEIGHT  16
#define FLIP_TIME       250

const uint8_t PIN_SCL = 11;
const uint8_t PIN_SDA = 12;

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
  // put your setup code here, to run once:
  flipdot->setModuleMapping(1, 2, 0, 0);

  delay(100);    
  // blank display
  flipdot->clearDisplay();
} 

void loop() {
/*
  flipdot->setDot(10,10, 0);
  flipdot->update();
  delay(1000);
  flipdot->setDot(10,10, 1);
  flipdot->update();
  delay(1000);
*/
/*
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
*/

  flipdot->fillScreen(0);
  flipdot->setTextColor(1,0);
  flipdot->drawCenteredText(0, 1, "Kati");
  flipdot->drawCenteredText(0, 9, "Anna");
  flipdot->update();
  delay(5000);
  flipdot->fillScreen(1);
  flipdot->setTextColor(0,1);
  flipdot->drawCenteredText(0, 1, "Kati");
  flipdot->drawCenteredText(0, 9, "Anna");
  flipdot->update();
  delay(5000);

}
