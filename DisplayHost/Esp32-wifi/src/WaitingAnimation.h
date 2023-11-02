#pragma once

#include "BaseAnimation.h"

class WaitingAnimation : public BaseAnimation {
public:
    void begin(Display &display);
    void end(Display &display);
    void nextStep(Display &display);  
    WaitingAnimation(String text);  
    ~WaitingAnimation();
private:
    String text;     
    int ticks;
    int phase;
    void drawBar(Display &display, int center_x, int center_y, int phase);
};