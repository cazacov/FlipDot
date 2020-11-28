#ifndef TEXTWRITER_H_
#define TEXTWRITER_H_

#include "flipBoard.h"

class TextWriter
{
public:
    TextWriter(FlipBoard &flipboard );
    void DrawDigit(uint8_t digit, uint8_t pos_x, uint8_t pos_y, uint8_t size_x, uint8_t size_y, const unsigned short font[]);
    void DrawNumber(int number, int x0, int y0, int minLength);
    void SmallNumber(int number, int x0, int y0, int minLength, int previous_number);
    void DrawText(char* text, int x0, int y0);
private:
    FlipBoard &flipboard;
};
#endif
