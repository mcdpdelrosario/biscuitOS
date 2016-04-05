#ifndef ServoEnhance_h
#define ServoEnhance_h
#include "PWMSoftware.h"
#include "Arduino.h"
#include "ImaginaryPWM.H"

class ServoEnhance
{

public:
ServoEnhance();
void attach(uint8_t pin);
void setAngle(uint32_t angle);
void detach(uint8_t pin);
uint8_t getAngle();
PWMSoftware p;
ImaginaryPWM i;
private:

volatile uint8_t _pin;
volatile uint8_t _output;
volatile uint8_t _flagServo;
volatile uint8_t _currentAngle;
};
#endif