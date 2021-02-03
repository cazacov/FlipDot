#pragma once

#include <Arduino.h>
#include "VM_IIC.h"
#include "XantoI2C.h"

#include <vector>

class Display : public VM_IIC {
private:
    uint8_t display_pin;
    uint8_t backlight_pin;
    XantoI2C i2c;
public:
    Display(uint8_t sda_pin, uint8_t scl_pin, uint8_t power_pin, uint8_t lamp_pin);
    void backlightOn();
    void backlightOff();
    void displayOn();
    void displayOff();
    std::vector<uint8_t> getPixels();
    void setPixels(std::vector<uint8_t> &newFrameBuffer);
};