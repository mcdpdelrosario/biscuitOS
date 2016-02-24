#ifndef ADCv1_h
#define ADCv1_h

#include "Arduino.h"

class ADCv1
{
  public:
	ADCv1();
	void enable(uint8_t pin);
    void setMode(uint8_t mode);
	uint16_t getReading(uint8_t pin); //for debugging
	
  private:
};

#endif