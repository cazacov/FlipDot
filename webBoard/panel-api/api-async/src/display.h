#pragma once

#include <Arduino.h>
#include "VM_IIC.h"
#include "XantoI2C.h"

#include <string>
#include <vector>

class Display : public VM_IIC {
private:
    uint8_t display_pin;
    uint8_t backlight_pin;
    XantoI2C i2c;
    bool is_display_on;
    bool is_backlight_on;
public:
    Display(uint8_t sda_pin, uint8_t scl_pin, uint8_t power_pin, uint8_t lamp_pin);
    bool getBacklightPower();
    void setBacklightPower(bool new_value);
    bool getDisplayPower();
    void setDisplayPower(bool new_value);
    std::vector<uint8_t> getPixels();
    void setPixels(std::vector<uint8_t> &newFrameBuffer);
    void cls(); // clear screen
};