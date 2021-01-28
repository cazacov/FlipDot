#pragma once

#include <Arduino.h>
#include "VM_IIC.h"
#include <XantoI2C.h>

class Display {
private:
    uint8_t display_pin;
    uint8_t backlight_pin;
    XantoI2C i2c;
    void i2cWriteByteSoftware(uint8_t addr, uint8_t data);    
public:
    Display(uint8_t sda_pin, uint8_t scl_pin, uint8_t power_pin, uint8_t lamp_pin);
    void backlightOn();
    void backlightOff();
    void displayOn();
    void displayOff();
};