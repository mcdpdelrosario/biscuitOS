
#include "Arduino.h"
#include "Motor.h"
#include "PWMSoftware.h"  

#include <avr/interrupt.h>
#define MAX_MOTORS 2

struct motors
{
  uint8_t motorPWMPin;
  uint8_t motorDirectionPin;
  float diameter;
  volatile uint32_t previousTime;
  volatile float getSpeedTime = 0;
  int percent;
  uint16_t period;
  PWMSoftware motorControl;
};
struct motors m[MAX_MOTORS];





byte _num;


void Motor::initialize(byte num, uint8_t motorPWMPin, uint8_t motorDirectionPin, float diameter)
{

	EICRB = B10100000;  //enable int 7 and int 6 falling edge
  EIMSK = B11000000;
	m[num].motorPWMPin = motorPWMPin;
	m[num].motorDirectionPin = motorDirectionPin;


  // if(m[num]._motorPWMPin==2)
  // {
  //  m[num].motorControl.initialize(3,3);
  // }

  // else if(m[num]._motorPWMPin==3)
  // {
  //   motorControl.initialize(3,2);
  // }

  // else if(_motorPWMPin==5)
  // {
  //   motorControl.initialize(3,1);
  // }

 if(m[num].motorPWMPin==6)
	{
		m[num].motorControl.initialize(1,2);
	}

	else if(m[num].motorPWMPin==7)
	{
		m[num].motorControl.initialize(1,3);
	}

  // else if(_motorPWMPin==9)
  // {
  //   motorControl.initialize(1,1);
  // }

  else
  {
    Serial.println("Not applicable PWM to your desired pin");
  }
}

void Motor::setPeriod(byte num, uint16_t period)
{
 uint16_t numberofticksTime;
 
m[num].period = m[num].period;
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


void Motor::setTarget(byte num, uint16_t targetspeedTime)
{
  byte proportionalConstant = 5;
 
  if(targetspeedTime<m[num].getSpeedTime)
  {
    m[num].percent = m[num].percent + 1;
    if(m[num].percent>=99)
    {
      m[num].percent = 99;
    }
    setTime(num,m[num].percent);
  }

else if(targetspeedTime>m[num].getSpeedTime)
  {
    m[num].percent = m[num].percent - 1;
    
    if(m[num].percent<=1)
    {
      m[num].percent = 1;
    }
    setTime(num,m[num].percent);
  }

  Serial.println(m[num].percent);
  Serial.println(targetspeedTime);
  Serial.println(m[num].getSpeedTime);
  // if(numberofticksTarget>m[num].getSpeedTime)
  // {
  //   m[num].percent = m[num].percent + 1;

  //   if(m[num].percent>=99)
  //   {
  //     m[num].percent = 99;
  //   }
  // }

  // else if(numberofticksTarget<m[num].getSpeedTime)
  // {
  //     m[num].percent = m[num].percent - 1;    
    
  //   if(m[num].percent<=1)
  //   {
  //     m[num].percent = 1;
  //   }
  // }

  setTime(num,m[num].percent);
  //Serial.println(_percent);


    // if(targetspeedTime<m[num].getSpeedTime)
    // {
    //     _percent = _percent + proportionalConstant;
    //     if(_percent>=99)
    //     {
    //       _percent = 99;
    //     }
    //     setTime(num,_percent);

    // }

    // else if(targetspeedTime>m[num].getSpeedTime)
    // {

    //   _percent = _percent - proportionalConstant;

    //   if(_percent<=3)
    //     {
    //       _percent = 3;
    //     }
    //   setTime(num,_percent);
    // }

}

uint16_t Motor::getSpeed(byte num)
{
  return m[num].getSpeedTime;
}


ISR(INT6_vect)
{

  m[0].getSpeedTime = millis() - m[0].previousTime;
  m[0].previousTime = millis();
}

ISR(INT7_vect)
{
  m[1].getSpeedTime = millis() - m[1].previousTime;
  m[1].previousTime = millis();
} 
