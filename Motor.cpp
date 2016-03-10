
#include "Arduino.h"
#include "Motor.h"
#include "PWMSoftware.h"  
#include "UARTv1.h"  

#include <avr/interrupt.h>
#define MAX_MOTORS 2

struct motors
{
  uint8_t motorPWMPin;
  uint8_t motorDirectionPin;
  float diameter;
  volatile uint16_t rotations=0;
  volatile byte flag;
  uint32_t lastProcessTime;
  uint16_t actualSpeed;
  uint16_t targetSpeed;
  int percent;
  uint16_t period;
  PWMSoftware motorControl;
};
struct motors m[MAX_MOTORS];

byte _num;
void Motor::initialize(byte num, uint8_t motorPWMPin, uint8_t motorDirectionPin, float diameter){

  EICRB = B10100000;  //enable int 7 and int 6 falling edge
  EIMSK = B11000000;
  m[num].motorPWMPin = motorPWMPin;


  if(motorDirectionPin==42) 
  {
    DDRG = B00010000;
    m[num].motorDirectionPin = DDRG;
  }

 if(m[num].motorPWMPin==6)
  {
    m[num].motorControl.init(1,2);
  }

  else if(m[num].motorPWMPin==7)
  {
    m[num].motorControl.init(1,3);
  }

  // else if(_motorPWMPin==9)
  // {
  //   motorControl.initialize(1,1);
  // }

  else
  {
    //Serial.println("Not applicable PWM to your desired pin");
  }
}

void Motor::changeDirection(byte num, byte dir)
{
  if(num==0)
  {
    if(dir==1)
    {
       PORTG = B00010000; 
    }

    else if(dir==0)
    {
      PORTG = 0x00;
    }
  }
}

void Motor::setPeriod(byte num, uint16_t period)
{
 uint16_t numberofticksTime;
 
  m[num].period =period;
  if (m[num].period > 20)
  {
    m[num].period = 20;
  }
  numberofticksTime = m[num].period / (64e-3);
  m[num].motorControl.setPeriod(numberofticksTime);

}

void Motor::setTime(byte num, int percent)
{
  uint16_t numberofticksTimeD;
  uint16_t percentDuty;
  m[num].percent = percent;                          
  percentDuty = (m[num].period*m[num].percent)/100;                   
  numberofticksTimeD = percentDuty/(64e-3); 
  m[num].motorControl.setPWM(numberofticksTimeD);

}

void Motor::setTarget(byte num, uint16_t targetSpeed)
{
 m[num].targetSpeed = targetSpeed;
}


void Motor::correctSpeed(byte num)
{

 
  computeSpeed(num);
  uint8_t proportionalConstant = 5;

  if(m[num].actualSpeed>m[num].targetSpeed)
  {
     m[num].percent = m[num].percent - proportionalConstant; 
    
    if(m[num].percent<=3)
    {
      m[num].percent = 3;
    }
  }

  else if(m[num].actualSpeed<m[num].targetSpeed)
  {
    m[num].percent = m[num].percent+proportionalConstant;
    if(m[num].percent>=99)
    {
      m[num].percent = 99;
    }
  }

  setTime(num,m[num].percent);
//   Transceiver.println((String)m[num].percent);

}

void Motor::computeSpeed(byte num)
{
  uint32_t temp;
  uint32_t timePassed;
  temp = m[num].rotations;
  m[num].rotations = 0;
  timePassed = millis() - m[num].lastProcessTime;
  m[num].lastProcessTime = millis();
  m[num].actualSpeed = temp;
}

uint16_t Motor::getSpeed(byte num)
{
  return m[num].actualSpeed;
}


void Motor::getDirection()
{
  if(m[1].flag==1)
  {
    Transceiver.println((String)("I am backward"));
  }

  if(m[0].flag==1)
  {
    Transceiver.println((String)("I am forward"));
  }

  
        
}


ISR(INT6_vect)
{
  if(m[1].flag==1)
  {
    m[0].flag=0;
  }
  else
  {
    m[0].flag=1;  
  }
  
  m[0].rotations++;
}

ISR(INT7_vect)
{
  if(m[0].flag==1)
  {
    m[1].flag=0;
  }
  else
  {
     m[1].flag=1;   
  }
 
  m[1].rotations++;
} 

