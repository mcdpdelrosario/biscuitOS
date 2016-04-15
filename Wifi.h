#ifndef Wifi_h
#define Wifi_h

#include "Arduino.h"

class Wifi
{
  public:
  	// void transfer();
  	void receive(char,char);
	void initialize(String,String);
  void send();
    void listen(String,String,String);
    void commands(void (*functionCallBack)(char));
    void gather(char,char,uint16_t);
	//void send(); under construction
  private:
  	// char myCommand;
};
static Wifi Wifi;
#endif