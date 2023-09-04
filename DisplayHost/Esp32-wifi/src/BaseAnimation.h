#pragma once

#include "display.h"

class BaseAnimation {
public:
    bool isActive;
    BaseAnimation() : isActive(false) {}
    virtual ~BaseAnimation();
    virtual void begin(Display &display);
    virtual void end(Display &display);
    virtual void nextStep(Display &display);
};