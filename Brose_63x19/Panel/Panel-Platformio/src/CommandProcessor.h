#ifndef _COMMANDPROCESSOR_h
#define _COMMANDPROCESSOR_h

#include "wwFlipdot02.h"
#include "panelCommands.h"

class CommandProcessor
{
private:
    uint8_t panel_number;
    void drawChar(uint8_t digit, uint8_t x0, uint8_t y0);
    void start();
    void test();
    void calibrate();
    void showId();
public:
    CommandProcessor(uint8_t panelNumber) : panel_number(panelNumber) {};
    void init();
    void execute(uint8_t command, uint8_t param1, uint8_t param2);
};
#endif
