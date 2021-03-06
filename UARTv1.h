#ifndef UARTv1_h
#define UARTv1_h

#include "Arduino.h"

class UARTv1
{
  public:
	void start(uint32_t);
    void print(String data);
    void println(String data);
	char receive(); //for debugging
	uint8_t peek();
	uint8_t getLength(String);
  private:
};
static UARTv1 Transceiver;
#endif