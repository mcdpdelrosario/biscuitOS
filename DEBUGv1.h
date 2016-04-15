#ifndef DEBUGv1_h
#define DEBUGv1_h

#include "Arduino.h"

class DEBUGv1
{
  public:
	void initialize(uint16_t);
    void send(String data);
	char receive(); //for debugging
	uint8_t peek();
  private:

};
static DEBUGv1 rDebug;
#endif