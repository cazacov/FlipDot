#ifndef _COMMANDPROCESSOR_h
#define _COMMANDPROCESSOR_h

#include "wwFlipdot02.h"
#include "panelCommands.h"

class CommandProcessor
{
private:
    int panel_number;
    void drawChar(int charNumber, int x0, int y0);
    void displayNumber(int id);
    void test();
public:
    CommandProcessor(int panelNumber){panel_number = panelNumber;};
    void init();
    void execute(int command, int param1, int param2);
};
#endif