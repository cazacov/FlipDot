#include "newyearanimation.h"

NewYear::~NewYear() { }  

void NewYear::begin(Display &display) {
    BaseAnimation::begin(display);

    width = display.width();
    height = display.height();

    for (int i = 0; i < SNOWFLAKES_COUNT; i++) {
        snowflakes[i][0] = display.width() / SNOWFLAKES_COUNT * i + 3 + random(7);
        snowflakes[i][1] = -4 - random(28);
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
        /*
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
        */

        display.setDot(x-3, y+3, true);
        display.setDot(x-3, y-3, true);
        display.setDot(x-3, y+2, false);
        display.setDot(x-3, y-4, false);

        display.setDot(x-2, y+2, true);
        display.setDot(x-2, y-2, true);
        display.setDot(x-2, y+1, false);
        display.setDot(x-2, y-3, false);
        
        display.setDot(x-1, y+1, true);
        display.setDot(x-1, y, false);
        display.setDot(x-1, y-1, true);
        display.setDot(x-1, y-2, false);

        display.setDot(x,   y+4, true);
        display.setDot(x,   y-5, false);

        display.setDot(x+1, y+1, true);
        display.setDot(x+1, y, false);
        display.setDot(x+1, y-1, true);
        display.setDot(x+1, y-2, false);
        
        display.setDot(x+2, y+2, true);
        display.setDot(x+2, y-2, true);
        display.setDot(x+2, y+1, false);
        display.setDot(x+2, y-3, false);

        display.setDot(x+3, y+3, true);
        display.setDot(x+3, y-3, true);
        display.setDot(x+3, y+2, false);
        display.setDot(x+3, y-4, false);

        if (y > display.height() + 3) {
            bool isValid = true;
            do {
                isValid = true;
                x = 3 + random(display.width() - 9);
                for (int j = 0; j < SNOWFLAKES_COUNT; j++) {
                    int sx = snowflakes[j][0];
                    int sy = snowflakes[j][1];
                    if (abs(sx-x)<8) {
                        if (abs(sy + 3) < 9)
                        {
                            isValid = false;
                            break;
                        }
                    }
                }
            } while (!isValid);
            snowflakes[i][0] = x;
            snowflakes[i][1] = -6 + random(3);
        }
    }
    display.update();
}