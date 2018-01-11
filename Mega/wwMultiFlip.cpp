
#include "wwMultiFlip.h"

int lastX = 0;  //for cool down strategy
int lastY = 0;  //for cool down strategy

// =============================================================================
void multiFlipStart() {
  allModuleReset();
  Wire.begin(); // join i2c bus (address optional for master)
  Wire.setClock(400000);
  delay(500);
  allModuleDotPowerOn();
  // Alles Xmal durchschütteln --------------------------------
  for (int lauf = 1; lauf <= 1; lauf++) {
    allModuleDotSet();
    delay(200);
    allModuleDotReset();
    delay(200);
  }

}

// =============================================================================
void allModuleReset() {
  //static int resetPins[] = {2, 3, 4, 5, 6, 7};
  //Module Resetten ------------------------------------------
  for (int module = 2; module <= 7; module++) {
    pinMode(module, OUTPUT);
    digitalWrite(module, LOW);
    delay(10);
    pinMode(module, INPUT);
  }
  delay(1000);  // Notwendig, damit die Nanos wieder denken können bevor sie angesprochen werden
}
// =============================================================================
void allModuleDotPowerOn() {
  // Dot Power für alle einschalten ----------------------------
  for (int module = 14; module <= 14; module++) {
    Wire.beginTransmission(module); // transmit to device #8
    Wire.write(203);              // switch on the 13,5 Volt Dot Power per Module
    Wire.endTransmission();    // stop transmitting
  }
  delay(200); // Notwendig zur Stabilisierung der Spannung
}
// =============================================================================
void allModuleDotPowerOff() {
  // Dot Power für alle einschalten ----------------------------
  for (int module = 14; module <= 14; module++) {
    Wire.beginTransmission(module); // transmit to device #8
    Wire.write(204);              // switch on the 13,5 Volt Dot Power per Module
    Wire.endTransmission();    // stop transmitting
  }
}
// =============================================================================
void allModuleDotSet() {
  for (int module = 14; module <= 14; module++) {
    Wire.beginTransmission(module); // transmit to device #module
    Wire.write(201);              // sends one byte
    Wire.endTransmission();    // stop transmitting
  }
}
// =============================================================================
void allModuleDotReset() {
  for (int module = 14; module <= 14; module++) {
    Wire.beginTransmission(module); // transmit to device #module
    Wire.write(202);              // sends one byte
    Wire.endTransmission();    // stop transmitting
  }
}

/*=========================================================================*/
void dotSetPanel(int x, int y) {
  int module = 0;
  int moduleRow = 0;
  bool coolDown = false;

  // wenn das Dot gerade erst umgeschaltet wurde zum Abkühlen etwas warten
  if (x == lastX) {
    if (y == lastY)
      coolDown = true;
  }
  lastX = x;  // aktuelles Dot als gerade umgeschaltet merken
  lastY = y;
  //--------------------------------------
  module = (x - 1) / moduleX; // = Modulnummer in x Richtung
  x -= moduleX * module;      // = x Adresse im oben errechneten Modul

  if (y > moduleY) {
    y -= moduleY;    // = y Adresse im oben errechneten Modul der Spalte
    module += 3;
  }
  module += 11;
  Wire.beginTransmission(module); // transmit to device #8
  Wire.write(x);                 // sends one byte
  Wire.write(y);
  Wire.endTransmission();        // stop transmitting
  //--------------------------------------
  if (coolDown)
    delay(emergencyDelay);   // Die Module warten eigenständig, daher darf man sie nicht noch 1x ansprechen
}
/*=========================================================================*/
void dotResetPanel(int x, int y) {
  int module = 0;
  int moduleRow = 0;
  bool coolDown = false;

  // wenn das Dot gerade erst umgeschaltet wurde zum Abkühlen etwas warten
  if (x == lastX) {
    if (y == lastY)
      coolDown = true;
  }
  lastX = x;  // aktuelles Dot als gerade umgeschaltet merken
  lastY = y;
  //--------------------------------------
  module = (x - 1) / moduleX; // = Modulnummer in x Richtung
  x -= moduleX * module;      // = x Adresse im oben errechneten Modul

  if (y > moduleY) {
    y -= moduleY;    // = y Adresse im oben errechneten Modul der Spalte
    module += 3;
  }
  module += 11;
  Wire.beginTransmission(module); // transmit to device #8
  Wire.write(x + 100);               // sends one byte
  Wire.write(y);
  Wire.endTransmission();        // stop transmitting
  //--------------------------------------
  if (coolDown)
    delay(emergencyDelay);   // Die Module warten eigenständig, daher darf man sie nicht noch 1x ansprechen
}

// =============================================================================
// =============================================================================
