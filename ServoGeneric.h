#ifndef ServoGeneric_h
#define ServoGeneric_h
#include "PWMSoftware.h"
#include "Arduino.h"



class ServoGeneric
{
	
	public:
	ServoGeneric();
	void servoInit(uint8_t num,uint8_t servoPin, byte maxAngle,byte minAngle,long totalPeriod,long maxTon,long minTon);
	void setAngle(long angle,uint8_t num);
	void servoUpdate();
	private:
volatile uint8_t _num;	
volatile uint8_t _servoPin;
	
	
	
};
#endif