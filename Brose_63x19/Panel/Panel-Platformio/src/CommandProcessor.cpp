#include "CommandProcessor.h"

#define PANEL_WIDTH 21 
#define PANEL_HEIGHT 19

void CommandProcessor::init() {
  dotSetup(28 - PANEL_WIDTH + 1, PANEL_WIDTH, 1, PANEL_HEIGHT, 0); 
  setCoilOnDuration(250);
}

void CommandProcessor::execute(uint8_t command, uint8_t param1, uint8_t param2) {
  switch (command) {
  case CMD_START:
    start();
    break;
  case CMD_ALL_SET:
    setAll(0);
    break;
  case CMD_ALL_RESET:
    resetAll(0);
    break;
  case CMD_POWER_ON:
    dotPowerOn();
    break;
  case CMD_POWER_OFF:
    dotPowerOff();
    break;
  case CMD_DOT_SET:
    setDot(param1, param2);
    break;
  case CMD_DOT_RESET:
    resetDot(param1, param2);
    break;
  case CMD_DURATION_SET:
    if (param1 >= 1 && param1 <= 10) {
      setCoilOnDuration((int)param1 * 100);
    }
    break;
  case CMD_TEST:
    test();
    break;
  case CMD_CALIBRATE:
    calibrate();
    break;
  case CMD_SHOWID:
    showId();
    break;
  case CMD_DELAY:
    delay100ms(param1);
  }
}

const uint8_t digits[][4] = {
    {0x7C, 0x82, 0x82, 0x7C}, // 0
    {0x00, 0x42, 0xFE, 0x02}, // 1
    {0x46, 0x8A, 0x92, 0x62}, // 2
    {0x44, 0x82, 0x92, 0x6C}, // 3
    {0x30, 0x50, 0x90, 0xFE}, // 4
    {0xE4, 0xA2, 0xA2, 0x9C}, // 5
    {0x7C, 0xA2, 0xA2, 0x1C}, // 6
    {0x86, 0x88, 0x90, 0xE0}, // 7
    {0x6C, 0x92, 0x92, 0x6C}, // 8
    {0x70, 0x8A, 0x8A, 0x7C}, // 9
};

void CommandProcessor::drawChar(uint8_t digit, uint8_t x0, uint8_t y0) {
  uint8_t bitmask = 0;

  for (uint8_t xc = 0; xc < 4; xc++) {
    bitmask = digits[digit][xc];
    for (uint8_t yc = 0; yc < 7; yc++) {
      if (bitmask & 0x80) {
        setDot(x0 + xc, y0 + yc);
      }
      else {
        resetDot(x0 + xc, y0 + yc);
      }
      bitmask <<= 1; //select next bit
      delay(2);
    }
  }
}

void CommandProcessor::test()
{
  delay(50);
  // Fill the screen
  for (uint8_t row = 1; row <= PANEL_HEIGHT; row++) {
    for (uint8_t column = 1; column <= PANEL_WIDTH; column++) {
      setDot(column, row);
      delay(5);
    }
    delay(300);
  }
  delay(1000);

  // Clear the screen
  for (uint8_t row = 1; row <= PANEL_HEIGHT; row++) {
    for (uint8_t column = 1; column <= PANEL_WIDTH; column++) {
      resetDot(column, row);
      delay(5);
    }
    delay(300);
  }
  delay(1000);

  // Draw a frame

  // Vertical lines
  for (uint8_t row = 1; row <= PANEL_HEIGHT; row++) {
    setDot(1, row);
    setDot(PANEL_WIDTH, row);
    delay(5);
  }

  // Horizontal lines
  for (uint8_t column = 1; column <= PANEL_WIDTH; column++) {
    setDot(column, 1);
    setDot(column, PANEL_HEIGHT);
    delay(5);
  }
}

void CommandProcessor::calibrate() {
  resetAll(0);
  for (uint16_t pos = 0; pos < PANEL_WIDTH * PANEL_HEIGHT; pos++) {
    for (uint8_t c = 0; c < 2; c++) {
      for (uint8_t i = 0; i < 5; i++) {
        uint8_t col = (pos+i) % PANEL_WIDTH + 1;
        uint8_t row = (pos+i) / PANEL_WIDTH + 1;
        if (c == 0) {          
          setDot(col, row);
        } else {
          resetDot(col, row);
        }
        delay(25);
      }
    }
  }
  resetAll(0);
}      

void CommandProcessor::showId() {

  resetAll(2);

    // Vertical lines
  for (uint8_t row = 1; row <= PANEL_HEIGHT; row++) {
    setDot(1, row);
    setDot(PANEL_WIDTH, row);
  }
  delay(2*PANEL_HEIGHT);

  // Horizontal lines
  for (uint8_t column = 1; column <= PANEL_WIDTH; column++) {
    setDot(column, 1);
    setDot(column, PANEL_HEIGHT);
  }  
  delay(2*PANEL_WIDTH);
  drawChar(panel_number / 10, 5, 5);
  drawChar(panel_number % 10, 10, 5);
}

void CommandProcessor::start() {
  dotPowerOn();
  resetAll(1);
}

void CommandProcessor::delay100ms(uint8_t n) {
  delay(n*100);
}

bool CommandProcessor::isValidCommand(uint8_t command) {
  return command > 0 && command <= CMD_DELAY;
}