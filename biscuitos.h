#ifndef biscuitos_h
#define biscuitos_h

#include "Arduino.h"

class biscuitos
{
  public:
	void initialize();
    void addProcess(void (*pointF)(), uint16_t nextmS);
	void printQueue(); //for debugging
	void start();
	
  private:
};

#endif