
#ifndef Battery_h
#define Battery_h
#include "Arduino.h"

class Battery
{
  public:
	void setMode(int mode);
	void enable(int pin);
	int getReading(int pin);
	void convertToPercentage();
  
  private:
	int _mode;
	int _pin;
};



#endif