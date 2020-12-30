/*********************************************************************
wwFlipdotPar02.h

Rainer Radow
30171 Hannover, Germany

2017-04-08 neues Platinenlayout mit paralleler Ansteuerung der Brose Adresspins über einen Port des Arduino zum schnelleren Flippen
2017-06-26 - ein kleines Wenig aufgeräumt
2017-06-26 - Beispiele überarbeitet
2017-08-01 Teile der "timer one library" hinzugefügt, um hier Kompatibilitätsproblemen aus dem Weg zu gehen.

*********************************************************************/

#ifndef _WWFLIPDOT02_h
#define _WWFLIPDOT02_h


/*
 *  TimerOne.h
 *  Interrupt and PWM utilities for 16 bit Timer1 on ATmega168/328
 *  Original code by Jesse Tane for http://labs.ideo.com August 2008
 *  Modified March 2009 by Jérôme Despatis and Jesse Tane for ATmega328 support
 *  Modified June 2009 by Michael Polli and Jesse Tane to fix a bug in setPeriod() which caused the timer to stop
 *
 *  This is free software. You can redistribute it and/or modify it under
 *  the terms of Creative Commons Attribution 3.0 United States License. 
 *  To view a copy of this license, visit http://creativecommons.org/licenses/by/3.0/us/ 
 *  or send a letter to Creative Commons, 171 Second Street, Suite 300, San Francisco, California, 94105, USA.
 *
 */


#include <avr/io.h>			//TimerOne.h
#include <avr/interrupt.h>	//TimerOne.h
#define RESOLUTION 65536    // Timer1 is 16 bit //TimerOne.h


#include "Arduino.h"
#define WIRE_WRITE Wire.write

#if defined(__SAM3X8E__)
typedef volatile RwReg PortReg;
typedef uint32_t PortMask;
#define HAVE_PORTREG
#elif defined(ARDUINO_ARCH_SAMD)
// not supported
#elif defined(ESP8266) || defined(ESP32) || defined(ARDUINO_STM32_FEATHER) || defined(__arc__)
typedef volatile uint32_t PortReg;
typedef uint32_t PortMask;
#elif defined(__AVR__)
typedef volatile uint8_t PortReg;
typedef uint8_t PortMask;
#define HAVE_PORTREG
#else
// chances are its 32 bit so assume that
typedef volatile uint32_t PortReg;
typedef uint32_t PortMask;
#endif

#include <SPI.h>

/*=========================================================================*/
#define clockPin 11   //pin connected to ST_CP of 74HC595
#define latchPin  9   //pin connected to SH_CP of 74HC595
#define dataPin 10    //pin connected to DS of 74HC595
#define dotPower 12    //pin connected to ENABLE the DC/DC Module
//--- Important: All Pins must be 8 or higher (in PORTB range)
#define latchPinPORTB 1  //int latchPinPORTB = latchPin - 8;
#define clockPinPORTB 3  //int clockPinPORTB = clockPin - 8;
#define dataPinPORTB  2  //int dataPinPORTB = dataPin - 8;

//BROSE Enable pin will power the outputs - set only for a short time to avoid coil damage
#define broseEnablePin  8//

#define emergencyDelay 25    // while(millis()-flipTime < emergencyDelay);

//Originalverdrahtung
#define dotOn 0         //bit position in the shift register
#define dotOff 4       //bit position in the shift register
#define dotEnable 1     //bit position in the shift register - only for old 9.5 Volt Version


/*=========================================================================*/

	extern void dotSetup(int startX, int xAnzahl, int startY, int yAnzahl, int version);
	extern void dotPowerOn(); 
	extern void dotPowerOff();
	extern void setDot(int zeile, int spalte ); 
	extern void resetDot(int zeile, int spalte ); 
	extern void setAll(int wartezeit);
	extern void resetAll(int wartezeit);
	extern void setCoilOnDuration(int durationDesired);
	//extern void punkt();

	void shiftOutFast(byte myDataOut);
	void shiftOutZero();
	void dotStromAus();

/*=========================================================================*/
/*=========================================================================*/
//Übernommen aus der TimerOne.h
class TimerOne
{
  public:
  
    // properties
    unsigned int pwmPeriod;
    unsigned char clockSelectBits;

    // methods
    void initialize(long microseconds=1000000);
    void start();
    void stop();
    void restart();
	
    void attachInterrupt(void (*isr)(), long microseconds=-1);
    void detachInterrupt();
	void setPeriod(long microseconds);

	
    void (*isrCallback)();
};

extern TimerOne Timer1;
/*=========================================================================*/
/*=========================================================================*/

#endif
