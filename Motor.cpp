
#include "Arduino.h"
#include "Motor.h"
#include "PWMSoftware.h"  
#include "UARTv1.h"  

#include <avr/interrupt.h>
#define MAX_MOTORS 2
#define forward 1
#define backward -1
#define leftWheel 0
#define rightWheel 1

struct motors
{
  uint8_t motorPWMPin;
  uint8_t motorDirectionPin;
  float diameter;
  volatile uint16_t rotations=0;
  volatile byte flag;
  uint32_t lastProcessTime;
  int percent;
  uint16_t period;
  int16_t proportionalFormula;

  // ---------


  // int16_t presentTime;
  // int16_t pastTime;
  // int16_t actualTime;
  // int16_t targetTime;
  // int16_t pastError;
  // int16_t currentError;
  // int16_t sumError =1000;
  // int16_t direction;
  // int16_t generalError =0;
  // int16_t generalCounter =0;
  int16_t presentTime;
  int16_t pastTime;
  int16_t actualTime;
  int16_t targetTime;
  int16_t pastError;
  int16_t currentError;
  int16_t sumError =1000;
  int16_t direction;
  int16_t generalError =0;
  int16_t generalCounter =0;

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

  if(num==leftWheel)
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

  else if(num==rightWheel)
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

void Motor::setTarget(byte num, uint16_t targetTime)     //function used by the user to set the target ticks
{ 
 
 m[num].targetTime = (10000/targetTime);
}





int16_t Motor::targetTime(byte num)                    //Function that returns the value of the actual Speed
{
  return m[num].targetTime;
}

int16_t Motor::presentTime(byte num)                    //Function that returns the value of the actual Speed
{
  return m[num].presentTime;
}

int16_t Motor::pastTime(byte num)                    //Function that returns the value of the actual Speed
{
  return m[num].pastTime;
}

int16_t Motor::actualTime(byte num)                    //Function that returns the value of the actual Speed
{
  return m[num].actualTime;
}

int16_t Motor::currentError(byte num)                    //Function that returns the value of the actual Speed
{
  return m[num].currentError;
}


int16_t Motor::pastError(byte num)                    //Function that returns the value of the actual Speed
{
  return m[num].pastError;
}


int16_t Motor::sumError(byte num)                    //Function that returns the value of the actual Speed
{
  return m[num].sumError;
}






void Motor::getDirection(byte num)                            // FUnction that determines the direction of the motor
{
  // a = getConda();
  // b = getCondb();

  int16_t applyDVar = applyDirection(num); 

    
    if(num==leftWheel)
    {
        if(applyDVar==backward)
        {
          Transceiver.println((String)"I am backward");
        }
        else if(applyDVar==forward)
        {

          Transceiver.println((String)"I am forward");
   
        } 
    }

    else if(num==rightWheel)
    {
        if(applyDVar==backward)
      {
        Transceiver.println((String)"I am backward");
      }
      else if(applyDVar==forward)
      {

      Transceiver.println((String)"I am forward");
     
      } 
    }
    
  
       
}


int16_t Motor::applyDirection(byte num)
{
  if(num==leftWheel){
    m[0].direction |= B10111111; //panlinis
    if(m[0].direction==0xFF)
      {
        return backward;
      }
        return forward;
  }
  else if(num==rightWheel){
    m[1].direction |= B11111011;
    if(m[1].direction==0xFF){
      return backward;
    }
      return forward;
          
  }

}  

int16_t knowDir(byte num){
  if(num==leftWheel){
    m[0].direction |= B10111111; //panlinis
    if(m[0].direction==0xFF)
      {
        return backward;
      }
        return forward;
  }
  else if(num==rightWheel){
    m[1].direction |= B11111011;
    if(m[1].direction==0xFF){
      return backward;
    }
      return forward;
          
  }
}

void Motor::correctSpeed(byte num){
  checkError(num);
  m[num].pastError = m[num].currentError;
  m[num].currentError = m[num].generalError/m[num].generalCounter;
  m[num].sumError += m[num].currentError;
  m[num].generalError = 0;
  m[num].generalCounter =0;
}


void Motor::checkError(byte num){
  if(m[num].generalCounter<2){
    m[num].presentTime = millis();
    m[num].actualTime =  (10000/(m[num].presentTime - m[num].pastTime));
    m[num].actualTime = (m[num].actualTime)*applyDirection(num);
    m[num].generalError += m[num].targetTime - m[num].actualTime;
    m[num].generalCounter++;
  }
}

ISR(INT2_vect)										//19
{
  
  m[1].rotations++;
}

ISR(INT3_vect)
{
	m[1].direction = PIND;
}

ISR(INT6_vect)                                       //Interrupts used. Once it hits int6 before int 7, it means forward. Then the number of rotations will just
                                                     //increment every falling edge.
{
  float data =10;
  
 m[0].pastTime = m[0].presentTime;
 m[0].presentTime = millis();
 m[0].actualTime =  (10000/(m[0].presentTime - m[0].pastTime));
 m[0].actualTime = (m[0].actualTime)*knowDir(0);
 m[0].generalError += m[0].targetTime - m[0].actualTime;
 m[0].generalCounter++;

 // Transceiver.println((String)(m[0].actualTime));

// m[0].currentError = m[0].targetTime - m[0].actualTime;

 //m[0].sumError += m[0].currentError;
}

ISR(INT7_vect)                                      //Same with interrupt 6 but if it hits first before interrupt 6, means the motor is in backward direction. 
{
m[0].direction = PINE;	
} 


