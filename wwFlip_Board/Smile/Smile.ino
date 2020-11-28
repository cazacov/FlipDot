// Uses FlipDot display http://flipdot.radow.org/

#include "wwFlipdot02.h" 

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

  for (int pos = 0; pos < 16*28; pos++) {
    for (int c = 0; c < 2; c++) {
      for (int i = 0; i < 5; i++) {
        int col = (pos+i)%28 + 1;
        int row = (pos+i)/16 + 1;
        if (c == 0) {          
          setDot(col, row);
        } else {
          resetDot(col, row);
        }
        delay(50);
      }
    }
  }
  resetAll(0);
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
