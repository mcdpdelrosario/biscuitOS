/*
  Morse.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#ifndef Battery_h
#define Battery_h
#include "Arduino.h"

class Battery
{
  public:
  
  void enable(uint8_t pin);
  uint16_t getReading(uint8_t pin);
  
  private:
 
 

  
  };

#endif