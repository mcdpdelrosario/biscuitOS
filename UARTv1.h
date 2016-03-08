#ifndef UARTv1_h
#define UARTv1_h

#include "Arduino.h"

class UARTv1
{
  public:
	void baud(uint16_t);
    void print(String data);
	char receive(); //for debugging
	uint8_t peek();
  private:
};
static UARTv1 Transceiver;
#endif