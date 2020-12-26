// Uses FlipDot display http://flipdot.radow.org/

#include "wwFlipdot02.h" 

void calibrate();
void drawSmile(uint8_t x0, uint8_t y0);

// ===========================================================================================
void setup() {
  dotSetup( 1, 28, 1, 16, 0);  //28x16
  delay(100);  
  dotPowerOn();    
  delay(50);      
  resetAll(5);
  setCoilOnDuration(300);
}
// ===========================================================================================
void loop() {
  calibrate();
  delay(1000);
  drawSmile(4, 1);
  delay(10000);
  while(true);
}
// ===========================================================================================

void calibrate() {
  resetAll(0);

  for (int s = 0; s < 2; s++) {
    for (int y = 1; y <= 16; y++) {
      for (int x = 1; x <= 28; x++) {
        if (s == 0) {          
          setDot(x, y);
        } else {
          resetDot(x, y);
        }
        delay(50);
      }
    }
  }
}



void drawSmile(uint8_t x0, uint8_t y0)
{
  for (uint8_t x = 1; x <= 28; x++)
  {
    for (uint8_t y = 1; y <= 16; y++)
    {
      setDot(x, y);
      delay(20);
    }
  }

  resetDot(x0, y0+5);  
  resetDot(x0, y0+6);
  resetDot(x0, y0+7);
  resetDot(x0, y0+8);  
  resetDot(x0, y0+9);  

  resetDot(x0+1, y0+3);  
  resetDot(x0+1, y0+4);
  resetDot(x0+1, y0+5);
  resetDot(x0+1, y0+10);  
  resetDot(x0+1, y0+11);  

  resetDot(x0+2, y0+2);  
  resetDot(x0+2, y0+5);
  resetDot(x0+2, y0+6);
  resetDot(x0+2, y0+7);  
  resetDot(x0+2, y0+12);  

  resetDot(x0+3, y0+1);  
  resetDot(x0+3, y0+5);
  resetDot(x0+3, y0+8);
  resetDot(x0+3, y0+13);  

  resetDot(x0+4, y0+1);  
  resetDot(x0+4, y0+5);
  resetDot(x0+4, y0+7);
  resetDot(x0+4, y0+8);  
  resetDot(x0+4, y0+13);  

  resetDot(x0+5, y0);  
  resetDot(x0+5, y0+5);
  resetDot(x0+5, y0+6);
  resetDot(x0+5, y0+7);  
  resetDot(x0+5, y0+8);    
  resetDot(x0+5, y0+14);  

  resetDot(x0+6, y0);  
  resetDot(x0+6, y0+5);
  resetDot(x0+6, y0+6);
  resetDot(x0+6, y0+7);  
  resetDot(x0+6, y0+11);    
  resetDot(x0+6, y0+14);    

  resetDot(x0+7, y0);  
  resetDot(x0+7, y0+5);
  resetDot(x0+7, y0+6);
  resetDot(x0+7, y0+11);    
  resetDot(x0+7, y0+14);    

  resetDot(x0+8, y0);  
  resetDot(x0+8, y0+5);
  resetDot(x0+8, y0+6);
  resetDot(x0+8, y0+7);  
  resetDot(x0+8, y0+11);    
  resetDot(x0+8, y0+14);    

  resetDot(x0+9, y0);  
  resetDot(x0+9, y0+5);
  resetDot(x0+9, y0+8);
  resetDot(x0+9, y0+11);    
  resetDot(x0+9, y0+14);    

  resetDot(x0+10, y0+1);  
  resetDot(x0+10, y0+5);
  resetDot(x0+10, y0+7);  
  resetDot(x0+10, y0+8);
  resetDot(x0+10, y0+10);    
  resetDot(x0+10, y0+13);    

  resetDot(x0+11, y0+1);  
  resetDot(x0+11, y0+5);
  resetDot(x0+11, y0+6);  
  resetDot(x0+11, y0+7);  
  resetDot(x0+11, y0+8);
  resetDot(x0+11, y0+13);    

  resetDot(x0+12, y0+2);  
  resetDot(x0+12, y0+5);
  resetDot(x0+12, y0+6);  
  resetDot(x0+12, y0+7);  
  resetDot(x0+12, y0+12);    

  resetDot(x0+13, y0+3);  
  resetDot(x0+13, y0+4);
  resetDot(x0+13, y0+5);  
  resetDot(x0+13, y0+10);  
  resetDot(x0+13, y0+11);    

  resetDot(x0+14, y0+5);  
  resetDot(x0+14, y0+6);
  resetDot(x0+14, y0+7);  
  resetDot(x0+14, y0+8);  
  resetDot(x0+14, y0+9);    
}