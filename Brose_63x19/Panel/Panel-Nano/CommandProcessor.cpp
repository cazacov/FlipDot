#include "CommandProcessor.h"

#define PANEL_WIDTH 21 
#define PANEL_HEIGHT 19

//#define TEST

void CommandProcessor::init() {
  dotSetup(8, PANEL_WIDTH, 1, PANEL_HEIGHT, 0); 
  dotPowerOn();
  delay(50);
#ifdef SERIAL_TRACE
  Serial.println("Panel is on");
#endif
  resetAll(5);
  setCoilOnDuration(250);
#ifdef SERIAL_TRACE
  Serial.println("Init done");
#endif  
#ifdef TEST
  calibrate();
#endif
#ifdef SERIAL_TRACE
  Serial.println("Test done");
#endif
  displayNumber(panel_number);
#ifdef SERIAL_TRACE
  Serial.println("Show panel number done");
#endif
}

void CommandProcessor::execute(int command, int param1, int param2) {
  switch (command) {
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
      setCoilOnDuration(param1 * 100);
    }
    break;
  case CMD_TEST:
    test();
    break;
  case CMD_CALIBRATE:
    calibrate();
    break;
  }
}

const uint8_t ziffer[][4] = {
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

void CommandProcessor::drawChar(int charNumber, int x0, int y0) {
  uint8_t anzeigeByte = 0;

  for (int xc = 0; xc < 4; xc++) {
    anzeigeByte = ziffer[charNumber][xc];
    for (int yc = 0; yc < 7; yc++) {
      if ((anzeigeByte & 128) == 128) {
        setDot(x0 + xc, y0 + yc);
      }
      else {
        resetDot(x0 + xc, y0 + yc);
      }
      anzeigeByte = anzeigeByte << 1; //select next bit
    }
  }
}

void CommandProcessor::displayNumber(int id)
{
  drawChar(id / 10, 5, 5);
  drawChar(id % 10, 10, 5);
}

void CommandProcessor::test()
{
  delay(500);

  // Fill the screen
  for (int row = 1; row <= 19; row++) {
    for (int column = 1; column <= 21; column++) {
      setDot(column, row);
      delay(5);
    }
    delay(300);
  }
  delay(1000);

  // Clear the screen
  for (int row = 1; row <= 19; row++) {
    for (int column = 1; column <= 21; column++) {
      resetDot(column, row);
      delay(5);
    }
    delay(300);
  }
  delay(1000);

  // Draw a frame

  // Vertical lines
  for (int row = 1; row <= 19; row++) {
    setDot(1, row);
    setDot(21, row);
    delay(5);
  }

  // Horizontal lines
  for (int column = 1; column <= 21; column++) {
    setDot(column, 1);
    setDot(column, 19);
    delay(5);
  }
}

void CommandProcessor::calibrate() {
  resetAll(0);

  for (int pos = 0; pos < 19*21; pos++) {
    for (int c = 0; c < 2; c++) {
      for (int i = 0; i < 5; i++) {
        int col = (pos+i)%21 + 1;
        int row = (pos+i)/21 + 1;
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
