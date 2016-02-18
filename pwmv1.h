#ifndef pwmv1_h
#define pwmv1_h

#include "Arduino.h"

class pwmv1
{
  public:
	pwmv1(uint8_t timerNo);
    void setPeriod(uint16_t period);
    void attachOCR(uint8_t OCRno);
	void setTime(uint16_t ticks);
  private:
	volatile uint16_t *_OCRnX;
	volatile uint8_t *_TCCRnA;
	volatile uint16_t *_ICRn;
	
};

#endif