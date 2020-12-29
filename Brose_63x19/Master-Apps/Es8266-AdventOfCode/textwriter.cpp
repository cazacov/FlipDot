#include "textwriter.h"
#include "glcdfonts.h"
#include <Arduino.h>

#include "flipBoard.h"

TextWriter::TextWriter(FlipBoard& flipboard_) : flipboard(flipboard_)
{
}

void TextWriter::DrawDigit(uint8_t character, uint8_t pos_x, uint8_t pos_y, uint8_t size_x, uint8_t size_y, const unsigned short font[]) {

    uint8_t bytes_per_column = size_y > 8 ? 2 : 1;

    for (uint8_t x = 0; x < size_x; x++) {
        for (uint8_t y = 0; y < size_y; y++)
        {

            int idx = (character - 32) * (1 + bytes_per_column * size_x) + 1 + (x * bytes_per_column) + (y / 8);
            if (font[idx] & (1 << (y & 0x07))) {
                this->flipboard.dot_set(pos_x + x, pos_y + y);
            }
            else {
                this->flipboard.dot_reset(pos_x + x, pos_y + y);
            }
        }
    }
}

void TextWriter::DrawNumber(int number, int x0, int y0, int minLength) {
  int digitCount = 0;
  int n = number;
  while (n > 0)
  {
    digitCount++;
    n /= 10;
  }
  if (!digitCount)
  {
    digitCount = 1;
  }
  if (digitCount < minLength)
  {
    digitCount = minLength;
  }

  while(digitCount)
  {
    DrawDigit((number % 10) + 48, x0 + digitCount * 8 - 8,  y0, 8, 12, Digits8x12);
    number /= 10;
    digitCount--;
  }
}

void TextWriter::SmallNumber(int number, int x0, int y0, int minLength, int prev) {
  int digitCount = 0;
  int n = number;
  while (n > 0)
  {
    digitCount++;
    n /= 10;
  }
  if (!digitCount)
  {
    digitCount = 1;
  }
  if (digitCount < minLength)
  {
    digitCount = minLength;
  }

  int pre = prev;
  while(digitCount)
  {
    int newd = number % 10;
    int pred = pre % 10;
    if (newd != pred) {
      DrawDigit((newd) + 48, x0 + digitCount * 4 - 4,  y0, 4, 5, Small4x5);
    }
    number /= 10;
    pre /= 10;
    digitCount--;
  }
}

void TextWriter::DrawText(char* ptr, int x0, int y0)
{
  while (*ptr)
  {
    DrawDigit(*ptr, x0,  y0, 4, 5, Small4x5);      
    x0 += 4;
    ptr++;
  }
}
