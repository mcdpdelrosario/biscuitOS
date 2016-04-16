



#include "Arduino.h"
#include "PWMSoftware.h"

uint8_t tempTCCRnA = 0x00; 
uint8_t tempTCCRnB = 0x00;
PWMSoftware::PWMSoftware(){

}

void PWMSoftware::init(uint8_t timerNo, uint8_t ocrLetter){
_timerNo = timerNo;
_ocrLetter = ocrLetter;
tempTCCRnB = 0x1A;
if (_timerNo == 3) {

_TCCRnA = &TCCR3A;
_ICRn = &ICR3;
_TCCRnB =&TCCR3B;
	if(_ocrLetter == 1){
		_OCRnX = &OCR3A;
		DDRE |= 0x08; 
		tempTCCRnA |=  0x82;   
		tempTCCRnA &= 0xBE; 
	}	
	
	if(_ocrLetter == 2){
		_OCRnX = &OCR3B;
		DDRE |= 0x10;
		tempTCCRnA|= 0x22;
		tempTCCRnA&= 0xEE;
	}
	
	if(_ocrLetter == 3){
		_OCRnX = &OCR3C;
		DDRE|= 0x20;
		tempTCCRnA |= 0x0A;
		tempTCCRnA &= 0xFA;
	}
}

else{
	
	_TCCRnA = &TCCR1A;
	_ICRn = &ICR1;
	_TCCRnB = &TCCR1B;

	if(_ocrLetter == 1){
		_OCRnX = &OCR1A;
		DDRB |= 0x20; 
		tempTCCRnA |= 0x82; 
		tempTCCRnA &= 0xBE;
	}
	
	if(_ocrLetter == 2){
		_OCRnX = &OCR1B;
		DDRB |= 0x40; 
		tempTCCRnA|= 0x22;
		tempTCCRnA&= 0xEE;
	}
	
	if(_ocrLetter == 3){
		_OCRnX = &OCR1C;
		DDRB |=0x80;
		tempTCCRnA |= 0x0A;
		tempTCCRnA &= 0xFA;
	}
	
}		
	
	
	
}

void PWMSoftware::setPeriod(uint16_t noofTicks){
*_ICRn = noofTicks;
*_TCCRnA = tempTCCRnA;
*_TCCRnB = tempTCCRnB;
}



void PWMSoftware::setPWM(uint32_t noofTicks){
*_OCRnX = noofTicks;
}

void PWMSoftware::detachPin(uint8_t timerNo,uint8_t ocrLetter){
_timerNo = timerNo;
_ocrLetter = ocrLetter;


if(_timerNo == 3){
	_TCCRnA = &TCCR3A;
	tempTCCRnA |= 0x02;
	if(_ocrLetter==1){
		DDRE &= 0xF7;
		tempTCCRnA &= 0x3E;
		
	}
	if(_ocrLetter==2){
		DDRE&=0xEF;
		tempTCCRnA &= 0xCE;
	}
	if(_ocrLetter==3){
		DDRE &=0xDF;
		tempTCCRnA &=0xF2;
	}
	
}

else{
	_TCCRnA = &TCCR1A;
	tempTCCRnA |= 0x02;
	if(_ocrLetter==1){
		DDRB &=0xDF;
		tempTCCRnA &= 0x3E;
	}
	if(_ocrLetter==2){
		DDRB &= 0xBF;
		tempTCCRnA &= 0xCE;
	}
	if(_ocrLetter==3){
		DDRB &= 0x7F;
		tempTCCRnA &=0xF2;
	}
	
}
	
}

