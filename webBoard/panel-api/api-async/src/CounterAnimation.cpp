#include "CounterAnimation.h"
#include "fonts/bus_163_8x15.h"

CounterAnimation::~CounterAnimation() { }  

void CounterAnimation::begin(Display &display, int xpos, int value) {
    BaseAnimation::begin(display);

    width = display.width();
    height = display.height();

    counter = value;
    this->xpos = xpos;
    this->ypos = 0;

    int16_t x,y;
    uint16_t w,h;
    display.getTextBounds("6", 0, 15, &x, &y, &w, &h);
    charWidth = w + 1;
    ticks = 0;
}

void CounterAnimation::end(Display &display) {
    isActive = false;
}

void CounterAnimation::nextStep(Display &display) {
    if (!isActive) {
        return;
    }

    ticks++;
    if (ticks < 10) {
        return;
    }
    ticks = 0;


    display.setFont(&bus_163_8x15);
    
    
    auto cnt = counter;
    auto xp = xpos;

    bool redraw = true;
    while (cnt > 0) {
        auto digit = cnt % 10;

        if (!redraw) {
            display.setCursor(xp - charWidth - 2,16);
            display.print(digit);
        }
        else {
            display.fillRect(xp - charWidth - 2, 0, charWidth + 2, height, 0);
            display.setCursor(xp - charWidth - 2, 16 - ypos);
            display.print(digit);
            display.setCursor(xp - charWidth - 2, 16 + 15 + 2 - ypos);
            display.print((digit + 1) % 10);
        }

        if (redraw) {
            if (digit == 9 || (digit == 0 && ypos == 0))
            { 
                redraw = true;
            }
            else {
                redraw = false;
            }
        }
        
        cnt /= 10;
        xp -= charWidth + 2;
    }

    ypos++;
    if (ypos == 17) {
        ypos = 0;
        counter++;
    }

    display.update();
}