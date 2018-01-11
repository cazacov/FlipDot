/*********************************************************************
Rainer Radow
*********************************************************************/
#include "Arduino.h"
#include <Wire.h>

#define moduleX 21   // Anzahl Dots in X-Richtung je Modul
#define moduleY 19   // Anzahl Dots in Y Richtung je Modul
#define emergencyDelay 25

/*=========================================================================*/
extern void multiFlipStart();
extern void allModuleReset();
extern void allModuleDotPowerOn();
extern void allModuleDotPowerOff();
extern void allModuleDotSet();
extern void allModuleDotReset();
extern void dotSetPanel(int x, int y);
extern void dotResetPanel(int x, int y);
/*=========================================================================*/