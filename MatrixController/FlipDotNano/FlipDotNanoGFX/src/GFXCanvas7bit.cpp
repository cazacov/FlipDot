#include "GFXCanvas7bit.h"

#ifdef __AVR__
// Bitmask tables of 0x80>>X and ~(0x80>>X), because X>>Y is slow on AVR
const uint8_t PROGMEM GFXcanvas7bit::GFXsetBit[] = {0x01, 0x02, 0x04, 0x08,
                                                 0x10, 0x20, 0x40, 0x80};
const uint8_t PROGMEM GFXcanvas7bit::GFXclrBit[] = {0xFE, 0xFD, 0xFB, 0xF7,
                                                    0xEF, 0xDF, 0xBF, 0x7F};
#endif

/**************************************************************************/
/*!
   @brief    Instatiate a GFX 1-bit canvas context for graphics
   @param    w   Display width, in pixels
   @param    h   Display height, in pixels
*/
/**************************************************************************/
GFXcanvas7bit::GFXcanvas7bit(uint16_t w, uint16_t h) : Adafruit_GFX(w, h) {
  bytesInRow = (w + BITS_IN_BYTE - 1) / BITS_IN_BYTE;
  uint16_t bytes = bytesInRow * h;
  if ((buffer = (uint8_t *)malloc(bytes))) {
    memset(buffer, 0, bytes);
  }
}

/**************************************************************************/
/*!
   @brief    Delete the canvas, free memory
*/
/**************************************************************************/
GFXcanvas7bit::~GFXcanvas7bit(void) {
  if (buffer)
    free(buffer);
}

/**************************************************************************/
/*!
    @brief  Draw a pixel to the canvas framebuffer
    @param  x     x coordinate
    @param  y     y coordinate
    @param  color Binary (on or off) color to fill with
*/
/**************************************************************************/
void GFXcanvas7bit::drawPixel(int16_t x, int16_t y, uint16_t color) {
  if (buffer) {
    if ((x < 0) || (y < 0) || (x >= _width) || (y >= _height))
      return;

    int16_t t;
    switch (rotation) {
    case 1:
      t = x;
      x = WIDTH - 1 - y;
      y = t;
      break;
    case 2:
      x = WIDTH - 1 - x;
      y = HEIGHT - 1 - y;
      break;
    case 3:
      t = x;
      x = y;
      y = HEIGHT - 1 - t;
      break;
    }

    uint8_t byte_nr = x / BITS_IN_BYTE;
    uint8_t bit_nr = x % BITS_IN_BYTE;
    uint8_t *ptr = &buffer[byte_nr + y * bytesInRow];
#ifdef __AVR__
    if (color)
      *ptr |= pgm_read_byte(&GFXsetBit[bit_nr]);
    else
      *ptr &= pgm_read_byte(&GFXclrBit[bit_nr]);
#else
    if (color)
      *ptr |= 0x01 << bit_nr;
    else
      *ptr &= ~(0x01 << bit_nr);
#endif
  }
}

/**********************************************************************/
/*!
        @brief    Get the pixel color value at a given coordinate
        @param    x   x coordinate
        @param    y   y coordinate
        @returns  The desired pixel's binary color value, either 0x1 (on) or 0x0
   (off)
*/
/**********************************************************************/
bool GFXcanvas7bit::getPixel(int16_t x, int16_t y) const {
  int16_t t;
  switch (rotation) {
  case 1:
    t = x;
    x = WIDTH - 1 - y;
    y = t;
    break;
  case 2:
    x = WIDTH - 1 - x;
    y = HEIGHT - 1 - y;
    break;
  case 3:
    t = x;
    x = y;
    y = HEIGHT - 1 - t;
    break;
  }
  return getRawPixel(x, y);
}

/**********************************************************************/
/*!
        @brief    Get the pixel color value at a given, unrotated coordinate.
              This method is intended for hardware drivers to get pixel value
              in physical coordinates.
        @param    x   x coordinate
        @param    y   y coordinate
        @returns  The desired pixel's binary color value, either 0x1 (on) or 0x0
   (off)
*/
/**********************************************************************/
bool GFXcanvas7bit::getRawPixel(int16_t x, int16_t y) const {
  if ((x < 0) || (y < 0) || (x >= WIDTH) || (y >= HEIGHT))
    return 0;
  if (this->getBuffer()) {
    uint8_t *buffer = this->getBuffer();
    uint8_t byte_nr = x / BITS_IN_BYTE;
    uint8_t bit_nr = x % BITS_IN_BYTE;

    uint8_t *ptr = &buffer[byte_nr + y * bytesInRow];

#ifdef __AVR__
    return ((*ptr) & pgm_read_byte(&GFXsetBit[bit_nr])) != 0;
#else
    return ((*ptr) & (0x01 << bit_nr)) != 0;
#endif
  }
  return 0;
}

/**************************************************************************/
/*!
    @brief  Fill the framebuffer completely with one color
    @param  color Binary (on or off) color to fill with
*/
/**************************************************************************/
void GFXcanvas7bit::fillScreen(uint16_t color) {
  if (buffer) {
    uint16_t bytes = bytesInRow * HEIGHT;
    memset(buffer, color ? 0xFF : 0x00, bytes);
  }
}

/**************************************************************************/
/*!
   @brief  Speed optimized vertical line drawing
   @param  x      Line horizontal start point
   @param  y      Line vertical start point
   @param  h      Length of vertical line to be drawn, including first point
   @param  color  Color to fill with
*/
/**************************************************************************/
void GFXcanvas7bit::drawFastVLine(int16_t x, int16_t y, int16_t h,
                               uint16_t color) {

  if (h < 0) { // Convert negative heights to positive equivalent
    h *= -1;
    y -= h - 1;
    if (y < 0) {
      h += y;
      y = 0;
    }
  }

  // Edge rejection (no-draw if totally off canvas)
  if ((x < 0) || (x >= width()) || (y >= height()) || ((y + h - 1) < 0)) {
    return;
  }

  if (y < 0) { // Clip top
    h += y;
    y = 0;
  }
  if (y + h > height()) { // Clip bottom
    h = height() - y;
  }

  if (getRotation() == 0) {
    drawFastRawVLine(x, y, h, color);
  } else if (getRotation() == 1) {
    int16_t t = x;
    x = WIDTH - 1 - y;
    y = t;
    x -= h - 1;
    drawFastRawHLine(x, y, h, color);
  } else if (getRotation() == 2) {
    x = WIDTH - 1 - x;
    y = HEIGHT - 1 - y;

    y -= h - 1;
    drawFastRawVLine(x, y, h, color);
  } else if (getRotation() == 3) {
    int16_t t = x;
    x = y;
    y = HEIGHT - 1 - t;
    drawFastRawHLine(x, y, h, color);
  }
}

/**************************************************************************/
/*!
   @brief  Speed optimized horizontal line drawing
   @param  x      Line horizontal start point
   @param  y      Line vertical start point
   @param  w      Length of horizontal line to be drawn, including first point
   @param  color  Color to fill with
*/
/**************************************************************************/
void GFXcanvas7bit::drawFastHLine(int16_t x, int16_t y, int16_t w,
                               uint16_t color) {
  if (w < 0) { // Convert negative widths to positive equivalent
    w *= -1;
    x -= w - 1;
    if (x < 0) {
      w += x;
      x = 0;
    }
  }

  // Edge rejection (no-draw if totally off canvas)
  if ((y < 0) || (y >= height()) || (x >= width()) || ((x + w - 1) < 0)) {
    return;
  }

  if (x < 0) { // Clip left
    w += x;
    x = 0;
  }
  if (x + w >= width()) { // Clip right
    w = width() - x;
  }

  if (getRotation() == 0) {
    drawFastRawHLine(x, y, w, color);
  } else if (getRotation() == 1) {
    int16_t t = x;
    x = WIDTH - 1 - y;
    y = t;
    drawFastRawVLine(x, y, w, color);
  } else if (getRotation() == 2) {
    x = WIDTH - 1 - x;
    y = HEIGHT - 1 - y;

    x -= w - 1;
    drawFastRawHLine(x, y, w, color);
  } else if (getRotation() == 3) {
    int16_t t = x;
    x = y;
    y = HEIGHT - 1 - t;
    y -= w - 1;
    drawFastRawVLine(x, y, w, color);
  }
}

/**************************************************************************/
/*!
   @brief    Speed optimized vertical line drawing into the raw canvas buffer
   @param    x   Line horizontal start point
   @param    y   Line vertical start point
   @param    h   length of vertical line to be drawn, including first point
   @param    color   Binary (on or off) color to fill with
*/
/**************************************************************************/
void GFXcanvas7bit::drawFastRawVLine(int16_t x, int16_t y, int16_t h,
                                  uint16_t color) {
  // x & y already in raw (rotation 0) coordinates, no need to transform.
  uint8_t *buffer = this->getBuffer();

  uint8_t byte_nr = x / BITS_IN_BYTE;
  uint8_t bit_nr = x % BITS_IN_BYTE;

  uint8_t *ptr = &buffer[byte_nr + y * bytesInRow];

  if (color > 0) {
#ifdef __AVR__
    uint8_t bit_mask = pgm_read_byte(&GFXsetBit[bit_nr]);
#else
    uint8_t bit_mask = (0x01 << bit_nr);
#endif
    for (int16_t i = 0; i < h; i++) {
      *ptr |= bit_mask;
      ptr += bytesInRow;
    }
  } else {
#ifdef __AVR__
    uint8_t bit_mask = pgm_read_byte(&GFXclrBit[bit_nr]);
#else
    uint8_t bit_mask = ~(0x01 << bit_nr);
#endif
    for (int16_t i = 0; i < h; i++) {
      *ptr &= bit_mask;
      ptr += bytesInRow;
    }
  }
}

/**************************************************************************/
/*!
   @brief    Speed optimized horizontal line drawing into the raw canvas buffer
   @param    x   Line horizontal start point
   @param    y   Line vertical start point
   @param    w   length of horizontal line to be drawn, including first point
   @param    color   Binary (on or off) color to fill with
*/
/**************************************************************************/
void GFXcanvas7bit::drawFastRawHLine(int16_t x, int16_t y, int16_t w,
                                  uint16_t color) {
  // x & y already in raw (rotation 0) coordinates, no need to transform.
  uint8_t *buffer = this->getBuffer();
  uint8_t byte_nr = x / BITS_IN_BYTE;
  uint8_t bit_nr = x % BITS_IN_BYTE;
  uint8_t *ptr = &buffer[byte_nr + y * bytesInRow];
  size_t remainingWidthBits = w;

  // check to see if first byte needs to be partially filled
  if (bit_nr > 0) {
    // create bit mask for first byte
    uint8_t startByteBitMask = 0x00;
    for (int8_t i = bit_nr; ((i < BITS_IN_BYTE) && (remainingWidthBits > 0)); i++) {
#ifdef __AVR__
      startByteBitMask |= pgm_read_byte(&GFXsetBit[i]);
#else
      startByteBitMask |= (0x01 << i);
#endif
      remainingWidthBits--;
    }
    if (color > 0) {
      *ptr |= startByteBitMask;
    } else {
      *ptr &= ~startByteBitMask;
    }

    ptr++;
  }

  // do the next remainingWidthBits bits
  if (remainingWidthBits > 0) {
    size_t remainingWholeBytes = remainingWidthBits / BITS_IN_BYTE;
    size_t lastByteBits = remainingWidthBits % BITS_IN_BYTE;
    uint8_t wholeByteColor = color > 0 ? 0xFF : 0x00;

    memset(ptr, wholeByteColor, remainingWholeBytes);

    if (lastByteBits > 0) {
      uint8_t lastByteBitMask = 0x00;
      for (size_t i = 0; i < lastByteBits; i++) {
#ifdef __AVR__
        lastByteBitMask |= pgm_read_byte(&GFXsetBit[i]);
#else
        lastByteBitMask |= (0x01 << i);
#endif
      }
      ptr += remainingWholeBytes;

      if (color > 0) {
        *ptr |= lastByteBitMask;
      } else {
        *ptr &= ~lastByteBitMask;
      }
    }  
  }
}
