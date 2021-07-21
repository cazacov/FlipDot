#pragma once

#include "display.h"

class CellAutomaton {
public:
    bool isActive;
    CellAutomaton();
    void begin(Display &display);
    void end(Display &display);
    void nextStep(Display &display);
private:
    bool* buffer;    
    int width;
    int height;
    bool getBuffer(int x, int y);
    void setBuffer(int x, int y, bool newValue);
};