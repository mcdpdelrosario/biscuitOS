#ifndef ServoV1_h
#define ServoV1_h

#include "Arduino.h"

class ServoV1
{
  public:
    void attachServo(uint8_t pin);
    void setAngle(uint8_t angle);
	void detachServo();
  private:
    uint8_t _pin;
	volatile uint8_t *_output;
};

#endif