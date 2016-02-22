
#ifndef myWifi_h
#define myWifi_h
#include "Arduino.h"

class myWifi
{
  public:
    myWifi(String apName,String pass,String IP, String portNumber);
    void wifiInit();
    void wifiListen();
	void wifiReceive();
    
	void sendData(String command, const int timeout, boolean debug); 
	void Control_Everything(char Command);
	
	void wifiSend();
	void wifiGather();
	void sendTry();
	void sendDataSend(int stringLengthSend, int timeoutSend);
	void Enqueue(int queue_number,unsigned int data);
	int Dequeue(int queue_number);
	void Queue_Init();
	
  private:
	String _response;
    String _apName;
	String _pass;
	String _IP;
	String _portNumber;
	String _sendThis;
	
};



#endif