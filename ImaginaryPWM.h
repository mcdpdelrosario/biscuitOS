#ifndef ImaginaryPWM_h
#define ImaginaryPWM_h

#include "Arduino.h"

class ImaginaryPWM
{
public:
ImaginaryPWM();
//void servoInit(uint8_t num);
void servoInit(uint8_t servoPin );
void setAngle(uint32_t angle);
void servoUpdate();
uint8_t getcurrentAngle(uint8_t num);
private:
uint8_t _num;
uint8_t _servoPin;
uint32_t _angle;
uint8_t _letter;
};


static ImaginaryPWM servoMiss;
#endif














