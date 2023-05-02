#pragma once

#include <Arduino.h>
#include <SPI.h> // Adafruit_GFX needs this
#include <Adafruit_I2CDevice.h>
#include <Adafruit_GFX.h>
#include <GFXcanvas7bit.h>

enum class StackMode {
    kRow,
    kStacked
};

class FlipDotNanoGFX : public GFXcanvas7bit {
public:    
    FlipDotNanoGFX(int matrix_width, int matrix_height, int matrix_columns, StackMode stack_mode);
    void setDot(int x, int y, bool state);
    void clearScreen();
    uint8_t readConfig();
    void setBitmap(const uint8_t *bytes, size_t count);
    bool updateNext();
    void endPulse();
// Override AdafruitGFX
    void endWrite(void);
// GFX Helper    
    void printCentered(const char *buf, uint16_t x, uint16_t y);
// Expose useful variables
    uint16_t frameBufferSize;
    uint16_t frameBufferWidth;
protected:
    int matrix_width_;
    int matrix_height_;
    int display_width_;
    int display_height_;
    int matrix_columns_;
    bool is_stacked_;
    uint8_t* volatile frameBuffer;
    uint8_t next_x;
    uint8_t next_y;
    uint8_t next_mask;
    uint8_t next_bit_nr;
    uint8_t *next_screen_ptr;
    uint8_t *next_target_ptr;

    void startPulse(int x, int y, bool state);
    void sendZeros();
    void sendData(uint8_t x, uint8_t y, uint8_t matrix, bool state);
    void sendDataRaw(uint32_t data); 
};
