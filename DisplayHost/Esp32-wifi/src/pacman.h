#pragma once

#include "BaseAnimation.h"

class Pacman : public BaseAnimation {
public:
    void begin(Display &display);
    void end(Display &display);
    void nextStep(Display &display);
    ~Pacman();
private:
    int width;
    int height;
    int pos;
    int radius;
};