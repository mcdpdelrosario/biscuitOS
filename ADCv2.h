#ifndef ADCv2_h
#define ADCv2_h

#include "Arduino.h"

class ADCv2
{
  public:
	ADCv2();
	void enable(uint8_t pin);
	uint16_t getReading(uint8_t pin);
  private:
};

#endif