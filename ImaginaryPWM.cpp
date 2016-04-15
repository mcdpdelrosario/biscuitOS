#include "Arduino.h"
#include "ImaginaryPWM.h"
#define MAX_SERVOS 10
#include <UARTv1.h>
uint8_t pin;
char letter;
uint8_t level;
uint8_t num = 0;

struct servos{
  uint8_t servoPin;
  uint16_t servoOn;
  uint16_t servoOff;
  bool servoStatus;
  unsigned long servoCounter;
	uint8_t currentAngle;
  };
struct servos s[MAX_SERVOS];

ImaginaryPWM::ImaginaryPWM(){
	
	
}
	void digitalHigh(uint8_t servoPin){
		switch(servoPin){
			case 4:PORTG|= B00100000;
			break;
			case 8:PORTB|= B00010000;
			break;
			case 10:PORTB&= 0xFE;
			break;
			case 11:PORTB|= 0x04;
			break;
			case 12:PORTB|= 0x08; 
			break;
			case 13:PORTB|= 0x02;
			break;
			default: break;
			
		}
		
	}
	
	void digitalLow(uint8_t servoPin){
		
		switch(servoPin){
			case 4:PORTG&= B11011111;
			break;
			case 8:PORTB&= B11101111;
			break;
			case 10:PORTB&= 0xFE;
			break;
			case 11:PORTB&= 0xFB;
			break;
			case 12:PORTB&= 0xF7; 
			break;
			case 13:PORTB&= 0xFD;
			break;
			default: break;
			
		}
	}
	

void ImaginaryPWM::servoInit(uint8_t servoPin){
	
	_servoPin = servoPin;
	_num = num;
	s[num].servoCounter = micros();
	s[num].servoOn = 0;
	s[num].servoOff = 0;
	s[num].servoPin = _servoPin;
	s[num].servoStatus = LOW;
	s[num].currentAngle = 0;
	num++;
	pinMode(_servoPin,OUTPUT);

	}
	
	
	
	
void ImaginaryPWM::servoUpdate(){
	unsigned long MS =micros();
	for(uint8_t i = 0 ;i<MAX_SERVOS;i++){
		if(s[i].servoStatus == LOW){
			if((MS - s[i].servoCounter) > s[i].servoOff){
				
				s[i].servoCounter = MS;
				s[i].servoStatus = HIGH;
		digitalHigh(s[i].servoPin);
			}
			
		}
		else{
			if((MS - s[i].servoCounter) > s[i].servoOn){
				s[i].servoCounter = MS;
				s[i].servoStatus = LOW;
		digitalLow(s[i].servoPin);
			}	
		}		
	}
	
}

void ImaginaryPWM::setAngle(uint32_t angle){
	_angle = angle;
	s[_num].currentAngle = _angle;
	uint32_t y2 = 0;
	y2 =((_angle*190)/18) + 500;
	cli();
	if(_angle = 0){
		s[_num].servoOn = 500;
		s[_num].servoOff = 19500;
	}
	else{
		s[_num].servoOn = y2;
		s[_num].servoOff = 20000 - y2;
	}
	sei();
	
}
uint8_t ImaginaryPWM::getcurrentAngle(uint8_t num){
	
	_num = num;
	return s[_num].currentAngle;
	
}


