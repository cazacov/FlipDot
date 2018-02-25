#include "textwriter.h"
#include "glcdfonts.h"

#include "flipBoard.h"

TextWriter::TextWriter(FlipBoard& flipboard_) : flipboard(flipboard_)
{
}

void TextWriter::DrawDigit(uint8_t digit, uint8_t pos_x, uint8_t pos_y) {

    for (uint8_t x = 0; x < 8; x++) {
        for (uint8_t y = 0; y < 16; y++)
        {
            int idx = digit * 17 + 1 + (x * 2) + (y / 8);
            if (Digits8x16[idx] & (1 << (y & 0x07))) {
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
    DrawDigit(number % 10, x0 + digitCount * 10 - 10, y0);
    number /= 10;
    digitCount--;
  }
}