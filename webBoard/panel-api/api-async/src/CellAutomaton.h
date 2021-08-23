#pragma once

#include "BaseAnimation.h"

class CellAutomaton : public BaseAnimation {
public:
    bool isClosed;
    void begin(Display &display...);
    void end(Display &display);
    void nextStep(Display &display);
    ~CellAutomaton();
private:
    bool* buffer;    
    int width;
    int height;
    bool getBuffer(int x, int y);
    void setBuffer(int x, int y, bool newValue);
    void put_spaceship(Display &display);
    void put_gun(Display &display, int x, int y);
};