#pragma once

#include "BaseAnimation.h"

#define SNOWFLAKES_COUNT 7

class NewYear : public BaseAnimation {
public:
    void begin(Display &display);
    void end(Display &display);
    void nextStep(Display &display);
    ~NewYear();
private:
    int width;
    int height;
    int snowflakes[SNOWFLAKES_COUNT][2];
};

