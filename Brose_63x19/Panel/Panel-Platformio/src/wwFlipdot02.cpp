/*********************************************************************
wwFlipdot02.cpp
Historie siehe wwFlipdot02.h

c by
Rainer Radow
30171 Hannover, Germany

*********************************************************************/
#include "wwFlipdot02.h"

// Feldwerte ergen sich aus der Beschaltung des Flip Dot Moduls
// Zeilen Feld zum -Setzen- der Zeilen 0 bis 18 -----------------------------------------------
//                            0,  1,  2,   3,  4,  5,  6,   7,  8,  9, 10,  11, 12, 13, 14,  15, 16, 17, 18
static int zeileSetHig[]  = { 0,  0,  0,   0,  0,  0,  0,   0,  0,  0,  0,   0,  0,  0,  0,   0,  1,  2,  4};
static int zeileSetMid[]  = { 0,  0,  0,   0,  0,  0,  0,   0,  1,  2,  4,   8, 16, 32, 64, 128,  0,  0,  0};
static int zeileSetLow[]  = { 1,  2,  4,   8, 16, 32, 64, 128,  0,  0,  0,   0,  0,  0,  0,   0,  0,  0,  0};

// Zeilen Feld zum -Löschen- der Zeilen 0 bis 18 -----------------------------------------------
static int zeileResHig[]  = { 0,  0,  0,   0,  0,  0,  0,   0,  0,  0,  0,   0,  1,  2,  4,   8, 16, 32, 64};
static int zeileResMid[]  = { 0,  0,  0,   0,  1,  2,  4,   8, 16, 32, 64, 128,  0,  0,  0,   0,  0,  0,  0};
static int zeileResLow[]  = {16, 32, 64, 128,  0,  0,  0,   0,  0,  0,  0,   0,  0,  0,  0,   0,  0,  0,  0};

// Spalten-Feld zur Anwahl der Spalten 0 bis 20 ------------------------------------------------
//Originalverdrahtung         0,   1,   2,   3,  4,  5,  6,  7,  8,  9, 10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27
static int spaltenWahl[] = {  8,  16,  24,  32, 40, 48, 56, 74, 80, 88, 96, 104, 112, 120, 136, 144, 152, 160, 168, 176, 184, 200, 208, 216, 224, 232, 240, 248};

	// Beschreibung des Displaylayouts
	int arrayStartX;     //Schiberegister-Position des ersten Pixels in X
	int arrayStartY;     //Schiberegister-Position des ersten Pixels in Y
	int arrayMaxX;       //größte erlaubte Arrayposition in X = 0 bis 27 = 28 Pixel
	int arrayMaxY;       //größte erlaubte Arrayposition in Y = 0 bis 18 = 19 Pixel
	int xMaxAnzahl; 
	int yMaxAnzahl;
	int lastX = 0;       // letzter geflippte Dot - x Position: verhindert mehrmaliges oder endloses Flippen eines Dots als Schutz vor dem Durchbrennen
	int lastY = 0;       // letzter geflippte Dot - y Position
	unsigned long flipTime;  //remember time of the last flip action to ensure cool down time
	int coilOnDuration = 500;   // Timer1.setPeriod(coilOnDuration); Dauer des Flippimpuls.

/*=========================================================================*/
	volatile int dotPowerIstAn;
 
 // Im Setup werden die Daten des Displays übergeben. 
 // Im Programm muss man sich dann um den physikalischen Aufbau des Displays nicht mehr kümmern. 
 // Punkt x=1 , Y=1 liegt oben rechts in der Ecke
 
 // ===========================================================================================
extern void dotSetup(int startX, int xAnzahl, int startY, int yAnzahl, int version){
  //Hier wählt man das Layout seines Moduls aus - dabei helfe ich gerne
  //dotSetup( 1, 28, 2, 15, 0);  //28x19 Startspalte (x), Anzahl Spalten, Startzeile (y), Anzahl Zeilen, Platinenversion
  //dotSetup( 8, 21, 1, 19, 0);  //21x19
  //dotSetup( 8, 21, 6, 11, 0);  //21x11
  //dotSetup( 8, 21, 7, 13, 0);  //21x13
  // Überprüfen der Eingabewerte und errechnen internr Werte
  // Version ist ein reservierter Wert um später mal anderre Module/Schaltungen zu bespielen
  if (startX > 28) startX = 28; // mehr als 28 Spalten gibt es nicht 
  if (startX <1) startX = 1;    // mindestens ein Pixel nötig   
  arrayStartX = startX - 2; 	// wir starten das Array bei 0 wenn später jemand 1 eingibt muss 0 aufgerufen werden
 
  if (xAnzahl > 28) xAnzahl = 28;  
  if (xAnzahl <  1) xAnzahl = 1; 
  xMaxAnzahl = xAnzahl;         // wird später für die Überprüfung der Punktkoordinaten benötigt 
  arrayMaxX = startX + xAnzahl - 1;  // größte erlaubte Arrayposition in X = 0 bis 27 
  
  if (startY > 19) startY = 19; // mehr als 19 Zeilen gibt es nicht
  if (startY < 1) startY = 1;   // mindestens ein Pixel nötig
  arrayStartY = startY - 2;     // wir starten das Array bei 0
  
  if (yAnzahl > 19) yAnzahl = 19;     // größte erlaubte Arrayposition in Y = 0 bis 18 
  if (yAnzahl <  1) yAnzahl = 1;   
  yMaxAnzahl = yAnzahl;
  arrayMaxY = startY + yAnzahl - 1;  

  //set pins to output so you can control the shift register
  pinMode(clockPin, OUTPUT);    //Clock Leitung zu der Schieberegisterkette
  pinMode(dataPin,  OUTPUT);    //Daten Leitung zu der Schieberegisterkette
  pinMode(latchPin, OUTPUT);    //Freigabepin: HIGH = Alle Registerdaten werden an Ausgänge weitergegeben
  
  DDRD = DDRD | B11111100;  // Setzt die Bits/Pins 7 bis 2 im Data Direction Register des Ports D auf Ausgang 
						    // Port D gehört zu den Arduino Pins 0 bis 7. Auf Pin 0 und 1 liegen RX und TX !!!
  
  //clear the shift register because you never know its initial state and you dont want to burn a coil...
  digitalWrite(latchPin, LOW);
  shiftOutZero();
  shiftOutZero();
  shiftOutZero();
  shiftOutZero();
  shiftOutZero();
  digitalWrite(latchPin, HIGH);          //Lege die neuen Daten an die Ausgänge der Schieberegister  
  
  // ------------------------------------
  Timer1.initialize(coilOnDuration);
  Timer1.attachInterrupt(dotStromAus);
  Timer1.stop();
  dotPowerIstAn = 0; 
} 
  // ==========================================================================
void dotStromAus() {
  //Serial.println("Strom Aus");
  Timer1.stop();
  digitalWrite(broseEnablePin, LOW);
  dotPowerIstAn = 0;
}
    
  // ===========================================================================================
extern void dotPowerOn(){
  pinMode(dotPower, OUTPUT);     //Schaltet den DC-DC Converter ein und aus
  pinMode(broseEnablePin, OUTPUT);
  digitalWrite(broseEnablePin, LOW); 
  delay(50);                     //Bevor man den Converter einschaltet sollte man immer ein wenig warten, damit vorher alle Kondensatoren auf der Platine geladen wurden.
  digitalWrite(dotPower, HIGH);
  delay(50);                     //Bei schwachem 5 Voltnetzteil kann es beim Einschalten zu Spannungsschwankungen kommen, daher mal kurz nichts machen...
}
// ===========================================================================================
extern void dotPowerOff(){
  pinMode(dotPower, INPUT); //Zur Sicherheit ausschalten, damit bei unklaren Schieberegisterstellungen nicht zu hohe Ströme fließen können.
  pinMode(broseEnablePin, INPUT);
}

// ===========================================================================================  
extern void setCoilOnDuration(int durationDesired){
  if(durationDesired <=1000)	
      coilOnDuration = durationDesired;
}

// ===========================================================================================
extern void setDot(int x, int y ) {
// Erlaubt sind Punktkoordinaten von X: 1 bis 28 und für YS 1 bis 19
// Die Umrechnung gemäß des Displaylayouts und für die Arrays findet hier intern statt
// X=1, Y=1 liegt in der Ecke oben/links

  // Wenn man eine solche Korrektur vornimmt, kann es bei Fehlern zur Überlastung der "Randpins" kommen
  // if (x <  1) x  =  1;                     //Koordinaten kleiner 1 nicht erlaubt
  // if (x  > xMaxAnzahl) x  = xMaxAnzahl;    //nur so viele Pixel wie vorab definiert
  // if (y <  1) y =  1;                      //Koordinaten kleiner 1 nicht erlaubt
  // if (y > yMaxAnzahl) y = yMaxAnzahl;      //nur so viele Pixel wie vorab definiert
  
  // Bei nicht zum Display passedenden Koordian hier abbrechen   
  if (x <  1) return;                     //Koordinaten kleiner 1 nicht erlaubt
  if (x  > xMaxAnzahl) return;    //nur so viele Pixel wie vorab definiert
  if (y <  1) return;                      //Koordinaten kleiner 1 nicht erlaubt
  if (y > yMaxAnzahl) return;      //nur so viele Pixel wie vorab definiert
 
  // wenn das Dot gerade erst umgeschaltet wurde zum Abkühlen etwas warten 
  if (x == lastX) {
	  if (y == lastY){
		  while(millis()-flipTime < emergencyDelay)
              ;
	  }  
  }
  lastX = x;  // aktuelles Dot als gerade umgeschaltet merken
  lastY = y;
  flipTime = millis();
  
  y += arrayStartY;
  
  digitalWrite(latchPin, LOW);             //Nur zur Sicherheit - sollte low sein!
  shiftOutZero();
  shiftOutZero();
  shiftOutFast(zeileSetHig [y]);
  shiftOutFast(zeileSetMid [y]);
  shiftOutFast(zeileSetLow [y]); 
  while (dotPowerIstAn == 1)     //Warten bis der vorherige Schaltvorgang abgschlossen ist
    ;
  digitalWrite(latchPin, HIGH);           //Lege die neuen Daten an die Ausgänge der Schieberegister  
  PORTD = spaltenWahl[arrayStartX + x];  //B00000000; //           //Für SetDot muss BROSE Data = LOW sein
  digitalWrite(broseEnablePin, HIGH); 
  
  Timer1.setPeriod(coilOnDuration);
  
  Timer1.start();               //Timer für aktuellen Schaltvorgang einstellen  
  dotPowerIstAn = 1;
 
   // digitalWrite(broseEnablePin, HIGH); 
   // delayMicroseconds(500);  //110 //500
   // digitalWrite(broseEnablePin, LOW); 
}

// ===========================================================================================
extern void resetDot(int x, int y ) {
	
  // Wenn man eine solche Korrektur vornimmt, kann es bei Fehlern zur Überlastung der "Randpins" kommen
  // if (x <  1) x  =  1;                     //Koordinaten kleiner 1 nicht erlaubt
  // if (x  > xMaxAnzahl) x  = xMaxAnzahl;    //nur so viele Pixel wie vorab definiert
  // if (y <  1) y =  1;                      //Koordinaten kleiner 1 nicht erlaubt
  // if (y > yMaxAnzahl) y = yMaxAnzahl;      //nur so viele Pixel wie vorab definiert
  
  // Bei nicht zum Display passedenden Koordian hier abbrechen   
  if (x <  1) return;                     //Koordinaten kleiner 1 nicht erlaubt
  if (x  > xMaxAnzahl) return;    //nur so viele Pixel wie vorab definiert
  if (y <  1) return;                      //Koordinaten kleiner 1 nicht erlaubt
  if (y > yMaxAnzahl) return;      //nur so viele Pixel wie vorab definiert
 
  // wenn das Dot gerade erst umgeschaltet wurde zum Abkühlen etwas warten 
  if (x == lastX) {
	  if (y == lastY){
		  while(millis()-flipTime < emergencyDelay)
              ;
	  }  
  }
  lastX = x;  // aktuelles Dot als gerade umgeschaltet merken
  lastY = y;
  flipTime = millis();

  y += arrayStartY;
  
  digitalWrite(latchPin, LOW);
  shiftOutFast(zeileResHig [y]);
  shiftOutFast(zeileResMid [y]);
  shiftOutFast(zeileResLow [y]);
  shiftOutZero();
  shiftOutZero();
  //bitClear(PORTB, clockPinPORTB); //clockOff() habe ich aus schiftOut Fast hier hoch genommen - ob das nötig ist? - Strom sparen?
  while (dotPowerIstAn == 1)     //Warten bis der vorherige Schaltvorgang abgschlossen ist
    ;
  digitalWrite(latchPin, HIGH);	
  PORTD =spaltenWahl[arrayStartX + x]+4; //     //Für resetDot muss BROSE Data = HIGH sein  4 = B00000100
  digitalWrite(broseEnablePin, HIGH); 
  Timer1.setPeriod(coilOnDuration);
  Timer1.start();               //Timer für aktuellen Schaltvorgang einstellen  
  dotPowerIstAn = 1;
  
  // digitalWrite(broseEnablePin, HIGH); 
  // delayMicroseconds(500);  //110 //500
  // digitalWrite(broseEnablePin, LOW);  
}
  // ===========================================================================================
void shiftOutFast(byte myDataOut) {
  //=== This function shifts 8 bits out MSB first much faster than the normal shiftOut function by writing directly to the memory address for port
  //Send each bit of the myDataOut byte MSBFIRST
  for (int i = 7; i >= 0; i--)  {
    bitClear(PORTB, clockPinPORTB); //clockOff();
    //--- Turn data on or off based on value of bit
    if (bitRead(myDataOut, i) == 1) {
      bitSet(PORTB, dataPinPORTB); // dataOn();
    }
    else {
      bitClear(PORTB, dataPinPORTB); //dataOff();
    }
    //register shifts bits on upstroke of clock pin
    bitSet(PORTB, clockPinPORTB); //clockOn();
  }
}
  // ===========================================================================================
void shiftOutZero() {
  //=== This function shifts 8 bits out MSB first much faster than the normal shiftOut function by writing directly to the memory address for port
  //Send each bit of the myDataOut byte MSBFIRST
  for (int i = 7; i >= 0; i--)  {
    bitClear(PORTB, clockPinPORTB); //clockOff();
    bitClear(PORTB, dataPinPORTB); //dataOff();
    //register shifts bits on upstroke of clock pin
    bitSet(PORTB, clockPinPORTB); //clockOn();
  }
}
// ===========================================================================================
void setAll(int wartezeit){
  for (int y = 1; y <= yMaxAnzahl; y++) {
    for (int x = 1; x <= xMaxAnzahl; x++) {
      setDot(x, y);
	  delay(wartezeit);
    }
  }
}
// ===========================================================================================  
void resetAll(int wartezeit){
  for (int y = 1; y <= yMaxAnzahl; y++) {
    for (int x = 1; x <= xMaxAnzahl; x++) {
      resetDot(x, y);
	  delay(wartezeit);
    }
  }
}
// ===========================================================================================
// ===========================================================================================
//Übernommen aus der TimerOne.h

TimerOne Timer1;              // preinstatiate

ISR(TIMER1_OVF_vect)          // interrupt service routine that wraps a user defined function supplied by attachInterrupt
{
  Timer1.isrCallback();
}

void TimerOne::initialize(long microseconds)
{
  TCCR1A = 0;                 // clear control register A 
  TCCR1B = _BV(WGM13);        // set mode as phase and frequency correct pwm, stop the timer
  setPeriod(microseconds);
}


void TimerOne::setPeriod(long microseconds)
{
  long cycles = (F_CPU * microseconds) / 2000000;                                // the counter runs backwards after TOP, interrupt is at BOTTOM so divide microseconds by 2
  if(cycles < RESOLUTION)              clockSelectBits = _BV(CS10);              // no prescale, full xtal
  else if((cycles >>= 3) < RESOLUTION) clockSelectBits = _BV(CS11);              // prescale by /8
  else if((cycles >>= 3) < RESOLUTION) clockSelectBits = _BV(CS11) | _BV(CS10);  // prescale by /64
  else if((cycles >>= 2) < RESOLUTION) clockSelectBits = _BV(CS12);              // prescale by /256
  else if((cycles >>= 2) < RESOLUTION) clockSelectBits = _BV(CS12) | _BV(CS10);  // prescale by /1024
  else        cycles = RESOLUTION - 1, clockSelectBits = _BV(CS12) | _BV(CS10);  // request was out of bounds, set as maximum
  ICR1 = pwmPeriod = cycles;                                                     // ICR1 is TOP in p & f correct pwm mode
  TCCR1B &= ~(_BV(CS10) | _BV(CS11) | _BV(CS12));
  TCCR1B |= clockSelectBits;                                                     // reset clock select register
}

void TimerOne::attachInterrupt(void (*isr)(), long microseconds)
{
  if(microseconds > 0) setPeriod(microseconds);
  isrCallback = isr;                                       // register the user's callback with the real ISR
  TIMSK1 = _BV(TOIE1);                                     // sets the timer overflow interrupt enable bit
  sei();                                                   // ensures that interrupts are globally enabled
  start();
}

void TimerOne::detachInterrupt()
{
  TIMSK1 &= ~_BV(TOIE1);                                   // clears the timer overflow interrupt enable bit 
}

void TimerOne::start()
{
  TCCR1B |= clockSelectBits;
}

void TimerOne::stop()
{
  TCCR1B &= ~(_BV(CS10) | _BV(CS11) | _BV(CS12));          // clears all clock selects bits
}

void TimerOne::restart()
{
  TCNT1 = 0;
}
// ===========================================================================================
// ===========================================================================================

