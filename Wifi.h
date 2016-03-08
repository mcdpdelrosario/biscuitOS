#ifndef Wifi_h
#define Wifi_h

#include "Arduino.h"

class Wifi
{
  public:
	void initialize(uint16_t,String,String);
    void listen(String,String);
	void receive(); 
	//void send(); under construction
  private:
};
static Wifi Wifi;
#endif