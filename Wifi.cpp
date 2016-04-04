#include "Arduino.h"
#include "Wifi.h"
#include "UARTv1.h"
#include "PWMSoftware.h"
#include <avr/interrupt.h>


typedef void (* FunctionPointer_t) (char);
typedef void (* FunctionPointer_t2) (uint16_t);
struct pointme {
   FunctionPointer_t functions;
   FunctionPointer_t2 functions2;
};
struct pointme p[10];

void Wifi::commands(void (*functionCallBack)(char))
{
   p[0].functions = functionCallBack;
}

void sendData(String command, const int timeout){
 String  response = "";
    Transceiver.print(command);
    long int time = millis();
    while( (time+timeout) > millis())
    {
      while(Transceiver.peek()>0)
      {
        char c = Transceiver.receive();
        response+=c;
      }  
    }
//    Transceiver.print(response);
}

char openingTag;

void Wifi::initialize(char openTag, String apName, String pass){
	openingTag=openTag;
  sendData("AT+CWMODE=1\r\n",1000);  
  sendData("AT+CWJAP=\""+apName+"\",\""+pass+"\"\r\n",8000);  
}

void Wifi::listen(String ID, String portNumber, String IP){
  sendData("AT+CIPMUX=1\r\n",1000);
  sendData("AT+CIPSTART="+ ID +",\"TCP\",\""+ IP +"\","+portNumber+"\r\n",2000);
  Transceiver.print("Connected!");
}

boolean statemachine = LOW;
char dataneed;

void Wifi::receive(){
  if(Transceiver.peek()>0){
    char letter = Transceiver.receive();
  if(statemachine ==HIGH){
    if(letter == ']'){
    // Transceiver.print((String)dataneed);
      statemachine = LOW; 
    }
    else{
//      Transceiver.send((String)dataneed);
    // control(letter);
      p[0].functions(letter);
    }
  }
  else if(letter == openingTag){
    statemachine = HIGH; 
  }
  }
}

