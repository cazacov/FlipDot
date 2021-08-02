#pragma once

#include "display.h"

class CellAutomaton {
public:
    bool isActive;
    bool isClosed;
    CellAutomaton();
    void begin(Display &display, bool isClosed = true);
    void end(Display &display);
    void nextStep(Display &display);
private:
    bool* buffer;    
    int width;
    int height;
    bool getBuffer(int x, int y);
    void setBuffer(int x, int y, bool newValue);
    void put_spaceship(Display &display);
    void put_gun(Display &display, int x, int y);
};