//
#include <Wire.h>
#include "wwMultiFlip.h"

void setup() {
   multiFlipStart();
   allModuleDotPowerOff();
   delay(1000);
}

/*=========================================================================*/
void loop() {
   for ( int y = 1; y <= 7 ; y++) {
     for ( int x = 1; x <= 5; x++) {
       for (int modul = 14; modul <= 14; modul++) {
         Wire.beginTransmission(modul); // transmit to device #8
         Wire.write(x);                 // sends one byte
         Wire.write(y);
         Wire.endTransmission();        // stop transmitting
         delay(2);
       }
     }
   }
   delay(1000);
   for ( int y = 1; y <= 7 ; y++) {
     for ( int x = 1; x <= 5; x++) {
       for (int modul = 14; modul <= 14; modul++) {
         Wire.beginTransmission(modul); // transmit to device #8
         Wire.write(x + 100);           // sends one byte
         Wire.write(y);
         Wire.endTransmission();        // stop transmitting
         delay(3);
       }
     }
   }
   delay(1000);
}

