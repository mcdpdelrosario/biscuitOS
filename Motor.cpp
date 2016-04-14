
//working motor 
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
  int16_t sumError =0;
  int16_t direction;
  int16_t generalError =0;
  int16_t generalCounter =0;
  int16_t dTerm;
  int16_t PID;
  int16_t numberofticksTimeD;
  int16_t percentDuty;

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

void Motor::changeDirection(byte num, int8_t dir)
{

  if(num==leftWheel)
  {
    
    if(dir==backward)
    {
       PORTG = B00010000;                                     //Assembly code for digitalWrite of a pin, setting 1 as high and 0 as low
       
    }

    else if(dir==forward)
    {
      PORTG = 0x00;
  
    }
  }

  else if(num==rightWheel)
  	{
  		if(dir==backward)
  		{
  			PORTE= B00000100;
  		}

  		else if(dir==forward)
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
  // using prescaler 8 with a total number of ticks of 40000
  numberofticksTime = m[num].period / (5e-4);   
  m[num].motorControl.setPeriod(numberofticksTime);

}
    
void Motor::setTime(byte num, int percent)                //Acts as the setDuty cycle, input is in percent
{

 m[num].percent = percent;                               //Percent to be converted again to the number of ticks
  m[num].percentDuty = (m[num].period*m[num].percent);             
  m[num].percentDuty = abs(m[num].percentDuty)/1000;
  m[num].numberofticksTimeD = m[num].percentDuty/(5e-4); 
  m[num].motorControl.setPWM(m[num].numberofticksTimeD);

}

void Motor::setTarget(byte num, int16_t targetTime)     //function used by the user to set the target ticks
{ 
 
 m[num].targetTime = targetTime;
 if(m[num].targetTime>0)
 {
      
    changeDirection(num,forward);
 
 }

 else if(m[num].targetTime<0)
 {

  changeDirection(num,backward);
  
 }
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
  return m[num].generalError;
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
    m[leftWheel].direction |= B10111111; //panlinis
    if(m[leftWheel].direction==0xFF)
      {
        return backward;
      }
        return forward;
  }
  else if(num==rightWheel){
    m[rightWheel].direction |= B11111011;
    if(m[rightWheel].direction==0xFF){
      return backward;
    }
      return forward;
          
  }

}  

int16_t knowDir(byte num){
  if(num==leftWheel){
    m[leftWheel].direction |= B10111111; //panlinis
    if(m[leftWheel].direction==0xFF)
      {
        return backward;
      }
        return forward;
  }
  else if(num==rightWheel){
    m[rightWheel].direction |= B11111011;
    if(m[rightWheel].direction==0xFF){
      return backward;
    }
      return forward;
          
  }
}

void Motor::correctSpeed(byte num){


  uint8_t kP = 10;
  uint8_t kI = 5;
  uint8_t kD = 5;

  checkError(num);
  m[num].pastError = m[num].currentError;
  m[num].currentError = m[num].generalError/m[num].generalCounter;
  m[num].sumError += m[num].currentError;
  PrintSpeed(num);
  m[num].generalError = 0;
  m[num].generalCounter =0;

  m[num].dTerm =  m[num].currentError - m[num].pastError;
  // m[num].PID = -(m[num].sumError/kI) + (m[num].currentError/kP) + ;
  m[num].PID = -(m[num].sumError/kI) + (m[num].currentError/kP);
  //Transceiver.println((String)m[num].currentError);
 setTime(num, m[num].PID);

}


void Motor::checkError(byte num){
  if(m[num].generalCounter<1){
   // Transceiver.print(("c"));
    m[num].presentTime = millis();
    m[num].actualTime =  (10000/(m[num].presentTime - m[num].pastTime));
    m[num].actualTime = (m[num].actualTime)*applyDirection(num);
    m[num].generalError += m[num].targetTime - m[num].actualTime;
    m[num].generalCounter++;     
  } 
}


void Motor::PrintSpeed(byte num)
{ 
  // Transceiver.print((String)(m[num].generalError)+ "\t");
  // Transceiver.print(((String)(m[num].currentError))+"\t");
  // Transceiver.print ((String)(m[num].PID)+"\t");
  Transceiver.print ((String)(m[num].actualTime)+"\t");
 // Transceiver.print(((String)(m[num].generalCounter))+ "\t");
 //  Transceiver.println((String)(m[num].actualTime));
  // Transceiver.println("---------------------------");
}
ISR(INT2_vect)										//19
{
  
 m[rightWheel].pastTime = m[rightWheel].presentTime;
 m[rightWheel].presentTime = millis();
 m[rightWheel].actualTime =  (10000/(m[rightWheel].presentTime - m[rightWheel].pastTime));
 m[rightWheel].actualTime = (m[rightWheel].actualTime)*knowDir(rightWheel);
 m[rightWheel].generalError += m[rightWheel].targetTime - m[rightWheel].actualTime;
 m[rightWheel].generalCounter++;
}

ISR(INT3_vect)
{
	m[rightWheel].direction = PIND;
}

ISR(INT6_vect)                                       //Interrupts used. Once it hits int6 before int 7, it means forward. Then the number of rotations will just
                                                     //increment every falling edge.
{
  
 m[leftWheel].pastTime = m[leftWheel].presentTime;
 m[leftWheel].presentTime = millis();
 m[leftWheel].actualTime =  (10000/(m[leftWheel].presentTime - m[leftWheel].pastTime));
 m[leftWheel].actualTime = (m[leftWheel].actualTime)*knowDir(leftWheel);
 m[leftWheel].generalError += m[leftWheel].targetTime - m[leftWheel].actualTime;
 m[leftWheel].generalCounter++;

 // Transceiver.println((String)(m[0].actualTime));

// m[0].currentError = m[0].targetTime - m[0].actualTime;

 //m[0].sumError += m[0].currentError;
}

ISR(INT7_vect)                                      //Same with interrupt 6 but if it hits first before interrupt 6, means the motor is in backward direction. 
{
m[leftWheel].direction = PINE;	
} 


