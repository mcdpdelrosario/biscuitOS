#ifndef Wifi_h
#define Wifi_h

#include "Arduino.h"

class Wifi
{
  public:
  	// void transfer();
  	void receive();
	void initialize(char,String,String);
    void listen(String,String,String);
    void commands(void (*functionCallBack)(char));
    void gather(String,String,uint16_t);
	//void send(); under construction
  private:
  	// char myCommand;
};
static Wifi Wifi;
#endif