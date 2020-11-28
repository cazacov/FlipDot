#include <Arduino.h>
#include <Wire.h>

#include "flipBoard.h"
#include "textwriter.h"
#include "glcdfonts.h"
#include "Command.h"
#include "IntcodeComputer.h"

FlipBoard flipBoard;
TextWriter textwriter(flipBoard);

enum Tile {
    Blank,
    Wall,
    Block,
    Paddle,
    Ball
};

Panel panels[] = {
    {10, D5},
    {11, D6},
    {12, D7}};

void setup()
{
  // put your setup code here, to run once:
  flipBoard.begin(panels, 1, 3);  // Panels in 1 row and 3 columns
  flipBoard.clearScreen();
  delay(10000);
  flipBoard.clearScreen();
}

int last_ball_x = 0;
int last_paddle_x = 0;

long on_input() {
  delay(50);
  if (last_ball_x < last_paddle_x) {
      return -1;
  } else if (last_ball_x > last_paddle_x) {
      return 1;
  }
  else {
      return 0;
  }
}

void show_score(int32_t score, int32_t last_score);
int32_t last_score = 0;

IntcodeComputer computer;
void loop()
{
  computer.load_day_13();
  computer.ram[0] = 2; // play for free

  int out[3];
  int out_pos = 0;
  while (!computer.is_halted()) {
    if (computer.step(false, on_input)) {
      out[out_pos++] = (int)computer.get_last_output();
      if (out_pos == 3) {
        if (out[0] == -1 && out[1] == 0) {  // show new score
          show_score(out[2], last_score);
          last_score = out[2];
        } else {
            if (out[2] == 0) {
              flipBoard.dot_reset(out[0]-1, out[1]-1);  
            }
            else {
              flipBoard.dot_set(out[0]-1, out[1]-1); 
            }
        }
        if (out[2] == Tile::Ball) {
            last_ball_x = out[0];
        }
        if (out[2] == Tile::Paddle) {
            last_paddle_x = out[0];
        }
        out_pos = 0;
      }
    }
  }
  delay(10000);
}

void show_score(int32_t score, int32_t last_score)
{
  textwriter.SmallNumber(score, 44, 2, 5, last_score);
}
