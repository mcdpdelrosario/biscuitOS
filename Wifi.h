#ifndef Wifi_h
#define Wifi_h

#include "Arduino.h"

class Wifi
{
  public:
	void initialize(uint32_t,String,String);
    void listen(String,String);
    void commands(void (*functionCallBack)(char));
	void receive(); 
	//void send(); under construction
  private:
  	// char myCommand;
};
static Wifi Wifi;
#endif