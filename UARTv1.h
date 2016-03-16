#ifndef UV1_h
#define UV1_h

#include "Arduino.h"

class UV1
{
  public:
	void start(uint16_t);
    void print(String data);
    void println(String data);
	char receive(); //for debugging
	uint8_t peek();
  private:
};
static UV1 Transceiver;
#endif