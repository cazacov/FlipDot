#pragma once

#include "BaseAnimation.h"

class CounterAnimation : public BaseAnimation {
public:
    void begin(Display &display, int xpos, int value);
    void end(Display &display);
    void nextStep(Display &display);    
    ~CounterAnimation();
private:
    int width;
    int height;
    int counter;
    int xpos;
    int ypos;
    int charWidth;
    int ticks;
};