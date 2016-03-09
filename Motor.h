

#ifndef Motor_h
#define Motor_h


#include "Arduino.h"
#include "PWMSoftware.h"

class Motor
{
  public:
    PWMSoftware motorControl;
    void initialize(byte num, uint8_t motorPWMPin, uint8_t motorDirectionPin, float diameter);
    void setPeriod(byte num, uint16_t period);
    void setTime(byte num, int percent);
    uint16_t getSpeed(byte num);  
    void setTarget(byte num, uint16_t targetSpeed);
    void correctSpeed(byte num);
    void computeSpeed(byte num); 
    void getDirection();
  private:
  	uint8_t _motorPWMPin;
 	  uint8_t _motorDirectionPin;
  	uint16_t _targetspeedTime;
  
  

};
static Motor motors;
#endif

