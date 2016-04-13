
#include "Arduino.h"
#include "ServoGeneric.h"
#define MAX_SERVOS 3
//

//End

// 
struct servos{
  byte servoPin;
  byte maxAngle;
  byte minAngle;
  long totalPeriod;
  long maxTon;
  long minTon;
  long servoOn;
  long servoOff;
  bool servoStatus;
  unsigned long servoCounter;
  long currentAngle;
  };
struct servos s[MAX_SERVOS];

ServoGeneric::ServoGeneric(){

}
void ServoGeneric:: servoInit(uint8_t num,uint8_t servoPin, byte maxAngle,byte minAngle,long totalPeriod,long maxTon,long minTon){
 _num =num;
 _servoPin = servoPin;
  s[_num].servoPin = servoPin;
  s[_num].maxAngle = maxAngle;
  s[_num].minAngle = minAngle;
  s[_num].totalPeriod = totalPeriod;
  s[_num].maxTon = maxTon;
  s[_num].minTon = minTon;
  s[_num].servoOn = 0;
  s[_num].servoOff = 0;
  s[_num].servoStatus = LOW;
  pinMode(_servoPin,OUTPUT);
  s[_num].servoCounter = micros();
  
  
}
  
  
  

void ServoGeneric :: servoUpdate() {
unsigned long MS = micros();
for(int i = 0;i<MAX_SERVOS;i++){
  if (s[i].servoStatus == LOW) {
    if ((MS - s[i].servoCounter) > s[i].servoOff) {
      s[i].servoCounter = MS;  
      s[i].servoStatus = HIGH;
     digitalWrite(s[i].servoPin ,HIGH);
    //  SET(PORTD,s[i].servoPin);
    }
  }
  else{  
    if((MS- s[i].servoCounter) > s[i].servoOn) {
     s[i].servoCounter = MS;
     s[i].servoStatus = LOW;
     //
     //CLR(PORTD, s[i].servoPin) ;
      digitalWrite(s[i].servoPin,LOW);
       }
      } 
 }
}

void ServoGeneric::setAngle(long angle,uint8_t num){
  _num = num;
 long x1 = s[_num].minAngle;
 long x3 = s[_num].maxAngle;
 long y1 = s[_num].minTon;
 long y3 = s[_num].maxTon;
 long x2 = angle;
 long y2 = 0;
 long a;
 long b;
 long c;
 a = x2-x1;
 b = y3-y1;
 c = x3-x1;
 y2 = ((a*b)/c)+y1;//Calculated Ton;
 noInterrupts();
    if(angle==0){
      s[_num].servoOn = 500;
      s[_num].servoOff = 23500; 
    }
      else{
      s[_num].servoOn = y2;
      s[_num].servoOff = s[num].totalPeriod - y2;
      }
      s[_num].currentAngle = angle;
interrupts();
}
