#include "Arduino.h"
#include "ServoV1.h"

void ServoV1::attachServo(uint8_t pin)
{	_pin = pin;
	  switch(_pin){
		case 3:
		DDRD |= 0x08;
		TCCR2A |= 0x23;
		TCCR2A &= 0xEF;
		TCCR2B = 0x07;
		TIMSK2 = 0x00;
		OCR2B = 23;
		_output=&OCR2B;
		break;
		
		//--------------------------
		case 11:
		DDRB |= 0x08;
		TCCR2A |= 0x83;
		TCCR2A &= 0xBF;
		TCCR2B = 0x07;
		TIMSK2 = 0x00;
		OCR2A = 23;
		_output=&OCR2A;
		break;
		
		//--------------------------
		case 10:
		DDRB |= 0x04;
		TCCR1A |= 0x22;
		TCCR1A &= 0xEE;
		TCCR1B = 0x1D;
		TCCR1C = 0x00;
		ICR1 = 312;
		TIMSK1 = 0x00;
		OCR1B = 23;
		_output=&OCR1BL;
		break;

		//--------------------------
		case 9:
		DDRB |= 0x02;
		TCCR1A |= 0x82;
		TCCR1A &= 0xBE;
		TCCR1B = 0x1D;//pre scale 1024
		TCCR1C = 0x00;
		ICR1 = 312; // this is the limit
		TIMSK1 = 0x00;
		OCR1A = 23;
		_output=&OCR1AL;
		break;
		default:
		break;
	  }
}

void ServoV1::setAngle(uint8_t angle){
	*_output=(angle*29/180)+9;
}
void ServoV1::detachServo(){
	switch(_pin){
		case 3:
		DDRD &= 0xF7;
		TCCR2A &= 0xCF;
		
		break;
		
		//--------------------------
		case 11:
		DDRB &= 0xF7;
		TCCR2A &= 0x3F;
		
		break;
		
		//--------------------------
		case 10:
		DDRB &= 0xFB;
		TCCR1A &= 0xCF;
		
		break;

		//--------------------------
		case 9:
		DDRB &= 0xFD;
		TCCR1A &= 0x3F;

		break;
		default:
		break;
	}
}

