#include "WaitingAnimation.h"
#include "fonts/bus_169_6x7.h"

WaitingAnimation::~WaitingAnimation() { }  

WaitingAnimation::WaitingAnimation(String text) {
    ticks = 0;
    phase = 0;
    this->text = text;
}

void WaitingAnimation::begin(Display &display) {
    BaseAnimation::begin(display);

    int width = display.width();
    int height = display.height();

    display.cls();
    display.setFont(&bus_169_6x7);

    int16_t x,y;
    uint16_t w,h;
    display.getTextBounds(text, 0, 15, &x, &y, &w, &h);

    display.setCursor(70 - w / 2, 7);
    display.print(text);
}

void WaitingAnimation::end(Display &display) {
    isActive = false;
}

void WaitingAnimation::nextStep(Display &display) {
    if (!isActive) {
        return;
    }

    ticks++;
    if (ticks < 20) {
        return;
    }
    ticks = 0;

    int centerx = 70;
    int centery = 14;

    display.fillCircle(centerx, centery, 4, 1);
    display.fillCircle(centerx, centery, 2, 0);

    float angle = phase * 2 * PI / 12.0;
    float nx = cos(angle);
    float ny = sin(angle);

    for (int y = -4; y <= 4; y++) {
        for (int x = -4; x<=4; x++) {
            float dot = nx * x + ny * y;
            if (dot < 0) {
                display.writePixel(centerx + x, centery + y, 0);
            }
        }
    }
    
    phase = (phase + 1) % 12;
    display.update();
}