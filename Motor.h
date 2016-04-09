

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
    void setTime(byte num, int percent);                                                              //Set the PWM of the motor, in percent                                                                  //Function that returns the speed of the motor        
    void setTarget(byte num, int16_t targetTime);                                                        //Function that always runs to reach the target ticks set by the user                                                             //Function that passes the number of rotations from the interrupt to a variable and computes the speed based on the rotations
    void getDirection(byte num);                                                                              //Function that prints the direction of the motor
    void changeDirection(byte num, byte dir);      
    uint8_t getConda(); 
    uint8_t getCondb();

    // -----
    int16_t presentTime(byte num);  
    int16_t pastTime(byte num);
    int16_t actualTime(byte num);
    int16_t targetTime(byte num);
    int16_t pastError(byte num);
    int16_t currentError(byte num);
    int16_t sumError(byte num);
    int16_t printPID(byte num);
    void correctSpeed(byte num);
    void checkPresentTime(byte num);

                                                       //Function that sets the direction of the motor based on the users input. 1 means forward, 0 means backward
  private:
  	uint8_t _motorPWMPin;
 	  uint8_t _motorDirectionPin;
  	uint16_t _targetspeedTime;
  
  

};
static Motor motors;
#endif

