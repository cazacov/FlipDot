#include "newyearanimation.h"

NewYear::~NewYear() { }  

void NewYear::begin(Display &display) {
    BaseAnimation::begin(display);

    width = display.width();
    height = display.height();

    for (int i = 0; i < SNOWFLAKES_COUNT; i++) {
        snowflakes[i][0] = i*14 + random(9);
        snowflakes[i][1] = 20 - random(19);
    }
    display.cls();
    display.update();
}

void NewYear::end(Display &display) {
    isActive = false;
}

void NewYear::nextStep(Display &display) {
    if (!isActive) {
        return;
    }

    for (int i = 0; i < SNOWFLAKES_COUNT; i++) {
        snowflakes[i][1] += 1;
        int x = snowflakes[i][0];
        int y = snowflakes[i][1];
        display.setDot(x-2, y+2, true);
        display.setDot(x-2, y-2, true);
        display.setDot(x-2, y+1, false);
        display.setDot(x-2, y-3, false);
        display.setDot(x-1, y+1, true);
        display.setDot(x-1, y-2, false);
        display.setDot(x,   y+3, true);
        display.setDot(x,   y-4, false);
        display.setDot(x+1, y+1, true);
        display.setDot(x+1, y-2, false);
        display.setDot(x+2, y+2, true);
        display.setDot(x+2, y-2, true);
        display.setDot(x+2, y+1, false);
        display.setDot(x+2, y-3, false);

        if (y > display.height() + 2) {
            bool isValid = true;
            do {
                isValid = true;
                x = random(display.width());
                for (int j = 0; j < SNOWFLAKES_COUNT; j++) {
                    int sx = snowflakes[j][0];
                    int sy = snowflakes[j][1];
                    if (abs(sx-x)<5) {
                        if (abs(sy + 3) < 7)
                        {
                            isValid = false;
                            break;
                        }
                    }
                }
            } while (!isValid);
            snowflakes[i][0] = x;
            snowflakes[i][1] = -3;
        }
    }
    display.update();
}