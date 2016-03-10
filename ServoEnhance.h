#ifndef ServoEnhance_h
#define ServoEnhance_h
#include "PWMSoftware.h"
#include "Arduino.h"

class ServoEnhance
{

public:
ServoEnhance();
void attach(uint8_t pin);
void setAngle(uint16_t angle);
void detach(uint8_t pin);
PWMSoftware p;
private:

volatile uint8_t _pin;
volatile uint8_t _output;


};
#endif