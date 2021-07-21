#include "CellAutomaton.h"

CellAutomaton::CellAutomaton() {
    isActive = false;
}

void CellAutomaton::begin(Display &display) {
    display.cls();
    display.setDot(20, 5, true);
    display.setDot(20, 7, true);
    display.setDot(21, 8, true);
    display.setDot(22, 8, true);
    display.setDot(23, 8, true);
    display.setDot(23, 5, true);
    display.setDot(24, 6, true);
    display.setDot(24, 7, true);
    display.setDot(24, 8, true);

    display.setDot(20, 13, true);
    display.setDot(20, 15, true);
    display.setDot(21, 12, true);
    display.setDot(22, 12, true);
    display.setDot(23, 12, true);
    display.setDot(23, 15, true);
    display.setDot(24, 12, true);
    display.setDot(24, 13, true);
    display.setDot(24, 14, true);

    
    display.setDot(18, 9, true);
    display.setDot(18, 10, true);
    display.setDot(18, 11, true);
    display.setDot(17, 9, true);
    display.setDot(17, 10, true);
    display.setDot(17, 11, true);
    display.setDot(16, 9, true);
    display.setDot(16, 11, true);
    display.setDot(15, 10, true);
    display.setDot(14, 10, true);

    display.setDot(11, 8, true);
    display.setDot(11, 12, true);
    display.setDot(10, 8, true);
    display.setDot(10, 9, true);
    display.setDot(10, 11, true);
    display.setDot(10, 12, true);
    display.setDot(9, 9, true);
    display.setDot(9, 11, true);
    display.setDot(7, 10, true);
    display.setDot(6, 10, true);
    display.setDot(5, 10, true);

    width = display.width();
    height = display.height();

    int bufferSize = width * height;
    buffer = (bool*)malloc(bufferSize * sizeof(bool));

    isActive = true;
}

void CellAutomaton::end(Display &display) {
    isActive = false;
    free(buffer);
}

void CellAutomaton::nextStep(Display &display) {
    if (!isActive) {
        return;
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            setBuffer(x,y, display.getDot(x, y));
        }
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int count = 0;
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (!dx && !dy) {
                        continue;
                    }
                    if (getBuffer(x + dx, y + dy)) {
                        count++;                                
                    }
                }
            }
            if (getBuffer(x,y)) {
                display.setDot(x, y, count == 2 || count == 3);
            } else {
                display.setDot(x, y, count == 3);
            }
        }
    }
    display.update();
}

bool CellAutomaton::getBuffer(int x, int y) {
    if (x < 0) {
        x = width - 1;
    } else if (x >= width) {
        x = 0;
    }
    if (y < 0) {
        y = height - 1;
    } else if (y >= height) {
        y = 0;
    }
    return buffer[y * width + x];
}

void CellAutomaton::setBuffer(int x, int y, bool newValue) {
    buffer[y*width + x] = newValue;
}
