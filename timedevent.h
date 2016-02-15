#ifndef timedevent_h
#define timedevent_h

#include "Arduino.h"

class timedevent
{
  public:
	timedevent();
    void timeIn(uint16_t nextmS,void (*pointF)());
	void printQueue();
	void timeStart();
  private:
};

#endif