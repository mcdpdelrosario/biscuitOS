
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
  int16_t proportionalFormula;
  PWMSoftware motorControl;
};
struct motors m[MAX_MOTORS];
uint8_t a;
uint8_t b;
uint8_t temp;
uint8_t temp1;
byte _num;
void Motor::initialize(byte num, uint8_t motorPWMPin, uint8_t motorDirectionPin, float diameter){

  EICRA = B10010000;
  EICRB = B10010000;                                              //ena ble int 7 and int 6 falling edge
  EIMSK = B11001100;  
  m[num].motorPWMPin = motorPWMPin;                               //passed the value from the user to the variable struct motorPWMPin


  if(motorDirectionPin==42) 
  {
    DDRG = B00010000;                                              //assembly code setting the pin 42(Direction Pin) as output
    m[num].motorDirectionPin = DDRG;
  }

  else if(motorDirectionPin==43)
  {
  	DDRE = B00000100;
  	m[num].motorDirectionPin = DDRE;
  }

 if(m[num].motorPWMPin==6)
  {
    m[num].motorControl.init(1,2);                                //Initializing the timers that will be used based on the PWMPin set by the user
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

  DDRE &= B10111111;
  DDRD &= B11111011;
}

void Motor::changeDirection(byte num, byte dir)
{

  if(num==0)
  {
    if(dir==1)
    {
       PORTG = B00010000;                                     //Assembly code for digitalWrite of a pin, setting 1 as high and 0 as low
      
    }

    else if(dir==0)
    {
      PORTG = 0x00;
    }
  }

  else if(num==1)
  	{
  		if(dir==1)
  		{
  			PORTE= B00000100;
  		}

  		else if(dir==0)
  		{
  			PORTE=0x00;
  		}
  	}

 
}

void Motor::resetFlags()
{
	 m[0].rotations=0;
  m[1].rotations=0;
}

void Motor::setPeriod(byte num, uint16_t period)            //User sets the total period of the motor 
{
 uint16_t numberofticksTime;
 
  m[num].period =period;
  if (m[num].period > 20)
  {                                                        //Period to be converted to the number of ticks for the PWMSoftware function setPeriod
    m[num].period = 20;
  }
  numberofticksTime = m[num].period / (64e-3);
  m[num].motorControl.setPeriod(numberofticksTime);

}
    
void Motor::setTime(byte num, int percent)                //Acts as the setDuty cycle, input is in percent
{
  uint16_t numberofticksTimeD;
  uint16_t percentDuty;
  m[num].percent = percent;                               //Percent to be converted again to the number of ticks
  percentDuty = (m[num].period*m[num].percent)/1000;                   
  numberofticksTimeD = percentDuty/(64e-3); 
  m[num].motorControl.setPWM(numberofticksTimeD);

}

void Motor::setTarget(byte num, uint16_t targetSpeed)     //function used by the user to set the target ticks
{ 
 m[num].targetSpeed = targetSpeed;
}


void Motor::correctSpeed(byte num)
{
                                                        //Application of proportional controller to correct the speed and reach the target ticks of the user
 
  computeSpeed(num);                                    //Printing the actual speed function
  uint8_t proportionalConstant = 10;

  m[num].proportionalFormula = (m[num].targetSpeed - m[num].actualSpeed)*100;

  if(m[num].actualSpeed>m[num].targetSpeed)
  {
     m[num].percent = m[num].percent + m[num].proportionalFormula - proportionalConstant; 
    
    if(m[num].percent<=proportionalConstant)
    {
      m[num].percent = proportionalConstant;
    }
  }

  else if(m[num].actualSpeed<m[num].targetSpeed)
  {
    m[num].percent = m[num].percent + m[num].proportionalFormula + proportionalConstant;
    if(m[num].percent>=990)
    {
      m[num].percent = 990;
    }
  }

  setTime(num,m[num].percent);
 // Transceiver.println((String)m[num].percent);

}

void Motor::computeSpeed(byte num)                    //Getting the actual ticks and passing it to the variable struct actualSpeed.
{
  uint32_t temp;
  uint32_t timePassed;
  temp = m[num].rotations;
  m[num].rotations = 0;
  timePassed = millis() - m[num].lastProcessTime;
  m[num].lastProcessTime = millis();
  m[num].actualSpeed = temp;
}

uint16_t Motor::getSpeed(byte num)                    //Function that returns the value of the actual Speed
{
  return m[num].actualSpeed;
}


void Motor::getDirection(byte num)                            // FUnction that determines the direction of the motor
{
  a = getConda();
  b = getCondb();

    
    if(num==0)
    {
        if(a==1)
        {
          Transceiver.println((String)"I am backward");
        }
        else if(a==0)
        {

          Transceiver.println((String)"I am forward");
   
        } 
    }

    else if(num==1)
    {
        if(b==1)
      {
        Transceiver.println((String)"I am backward");
      }
      else if(b==0)
      {

      Transceiver.println((String)"I am forward");
     
      } 
    }
    
  
       
}

uint8_t Motor::getConda()
{
	temp |= B10111111; //panlinis
	if(temp==0xFF)
	{
		return 1;
	}
	return 0;
}

uint8_t Motor::getCondb()
{
  temp1 |= B11111011; //panlinis
  if(temp1==0xFF)
  {
    return 1;
  }
  return 0;

}


ISR(INT2_vect)										//19
{
  
  m[1].rotations++;
}

ISR(INT3_vect)
{
	temp1 = PIND;
}

ISR(INT6_vect)                                       //Interrupts used. Once it hits int6 before int 7, it means forward. Then the number of rotations will just
                                                     //increment every falling edge.
{
  
  m[0].rotations++;

}

ISR(INT7_vect)                                      //Same with interrupt 6 but if it hits first before interrupt 6, means the motor is in backward direction. 
{

 temp = PINE;	
} 

