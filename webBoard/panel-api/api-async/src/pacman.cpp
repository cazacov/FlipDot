#include "pacman.h"

Pacman::~Pacman() { }  

void Pacman::begin(Display &display) {
    BaseAnimation::begin(display);

    width = display.width();
    height = display.height();

    radius = height/2;
    pos = -radius;
}

void Pacman::end(Display &display) {
    isActive = false;
}

void Pacman::nextStep(Display &display) {
    if (!isActive) {
        return;
    }
    if (pos >= width + radius) {
        return;
    }

    display.drawCircle(pos, radius, radius, 0);
    pos++;
    display.fillCircle(pos, radius, radius, 1);

    int phase = pos % 10;
    if (phase > 5) {
        phase = 10 - phase;
    }
    phase++;
    double maxAngle = phase * 3.1415 / 18;
    for (double angle = 0; angle < maxAngle + .01; angle += 3.1415 / 36.0) {
        int x = cos(angle) * (radius+1);
        int y = sin(angle) * (radius+1);
        display.drawLine(pos, radius, pos + x, radius - y, 0);
        display.drawLine(pos, radius, pos + x, radius + y, 0);
    }
    display.update();
}