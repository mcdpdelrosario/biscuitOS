

#ifndef Motor_h
#define Motor_h


#include "Arduino.h"
#include "PWMSoftware.h"

class Motor
{
  public:
    PWMSoftware motorControl;
    void initialize(byte num, uint8_t motorPWMPin, uint8_t motorDirectionPin, float diameter);        //initialize the values to be used for PWMPin, DirectionPin, Diameter of the motor
    void setPeriod(byte num, uint16_t period);                                                        //Set the total period for the motor example is 20 which corresponds to 20ms
    void setTime(byte num, int percent);                                                              //Set the PWM of the motor, in percent
    uint16_t getSpeed(byte num);                                                                      //Function that returns the speed of the motor        
    void setTarget(byte num, uint16_t targetSpeed);                                                   //Used by the user to set the target ticks the user wants the motor to reach
    void correctSpeed(byte num);                                                                      //Function that always runs to reach the target ticks set by the user
    void computeSpeed(byte num);                                                                      //Function that passes the number of rotations from the interrupt to a variable and computes the speed based on the rotations
    void getDirection();                                                                              //Function that prints the direction of the motor
    void changeDirection(byte num, byte dir);      
    void resetFlags();
    uint8_t getConda(); 
    uint8_t getCondb();
                                                       //Function that sets the direction of the motor based on the users input. 1 means forward, 0 means backward
  private:
  	uint8_t _motorPWMPin;
 	  uint8_t _motorDirectionPin;
  	uint16_t _targetspeedTime;
  
  

};
static Motor motors;
#endif

