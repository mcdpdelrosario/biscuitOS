#ifndef PWMSoftware_h
#define PWMSoftware_h

#include "Arduino.h"

class PWMSoftware
{
	public:
	PWMSoftware();
	void init(uint8_t timerNo, uint8_t ocrLetter);
	void setPeriod(uint16_t noofTicks);
	void setPWM(uint32_t noofTicks);
	private:
	volatile uint16_t *_OCRnX;
	volatile uint8_t *_TCCRnA;
	volatile uint16_t *_ICRn;
	volatile uint8_t *_TCCRnB;
	uint8_t _timerNo;
	uint8_t _ocrLetter;
	
};
#endif