#ifndef Wifi_h
#define Wifi_h

#include "Arduino.h"

class Wifi
{
  public:
	void initialize(char,String,String);
    void listen(String,String,String);
    void commands(void (*functionCallBack)(char));
    void gatherData(void (*functionCallBack)(uint16_t));
	//void send(); under construction
  private:
  	// char myCommand;
};
static Wifi Wifi;
#endif