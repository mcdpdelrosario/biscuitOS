#include "Arduino.h"
#include "pwmv1.h"
uint8_t timerNm;
pwmv1::pwmv1(uint8_t timerNo){
	timerNm = timerNo;
	switch(timerNo){
		case 1:
		TCCR1A |= 0x02;
		TCCR1A &= 0xFE;
		TCCR1B = 0x1D;
		TIMSK1 = 0x00;
		_TCCRnA = &TCCR1A;
		_ICRn = &ICR1;
		break;
		case 3:
		TCCR3A |= 0x02;
		TCCR3A &= 0xFE;
		TCCR3B = 0x1D;
		TIMSK3 = 0x00;
		_TCCRnA = &TCCR3A;
		_ICRn = &ICR3;
		break;
		default:
		break;
	}
}
void pwmv1::setPeriod(uint16_t period){
	*_ICRn = period;
}
void pwmv1::attachOCR(uint8_t OCRno){
	if(timerNm == 1){
		switch(OCRno){
			case 1:
			OCR1A = 23;
			_OCRnX = &OCR1A;
			*_TCCRnA |= 0x80;
			*_TCCRnA &= 0xBF;
			break;
			case 2:
			OCR1B = 23;
			_OCRnX = &OCR1B;
			*_TCCRnA |= 0x40;
			*_TCCRnA &= 0xEF;
			break;
			case 3:
			OCR1C = 23;
			_OCRnX = &OCR1C;
			*_TCCRnA |= 0x08;
			*_TCCRnA &= 0xFB;
			break;
			default:
			break;
		}
	}else if(timerNm ==3){
		switch(OCRno){
			case 1:
			OCR3A = 23;
			_OCRnX = &OCR3A;
			*_TCCRnA |= 0x80;
			*_TCCRnA &= 0xBF;
			break;
			case 2:
			OCR3B = 23;
			_OCRnX = &OCR3B;
			*_TCCRnA |= 0x40;
			*_TCCRnA &= 0xEF;
			break;
			case 3:
			OCR3C = 23;
			_OCRnX = &OCR3C;
			*_TCCRnA |= 0x08;
			*_TCCRnA &= 0xFB;
			break;
			default:
			break;
		}
	}
}
void pwmv1::setTime(uint16_t ticks){
	*_OCRnX = ticks;
}