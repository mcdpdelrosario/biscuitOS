#include "Arduino.h"
#include "Wifi.h"
#include "UARTv1.h"
#include "PWMSoftware.h"
#include <avr/interrupt.h>

typedef union {
  uint16_t data;
  char cdata[2];
  uint8_t sdata[2];
}sender;

sender caller;
sender combo;
void sendData(String, const int);
typedef void (* FunctionPointer_t) (char);
struct pointme {
   FunctionPointer_t functions;
};
struct pointme p[10];

uint8_t sendState=0;

void Wifi::gather(String openingTag,String classifier,uint16_t data){
  
    String frame;
    String sendString;
    char lengthdata;
    uint8_t datalength;
    char temp;
    caller.data=data;

    lengthdata=Transceiver.getLength(caller.cdata);
        combo.data=caller.sdata[0] + caller.sdata[1];
    temp = combo.cdata[0];
    temp = combo.cdata[1];
    frame=openingTag + classifier + (String)lengthdata + (String)caller.cdata[0] + (String)caller.cdata[1] + (String)combo.cdata[0] +(String)(combo.cdata[1]) + "]";  
    datalength=Transceiver.getLength(frame);
    // Transceiver.print((String)datalength);
    // delay(1000);
    if(sendState==0){
      Enqueue(SQ,frame);
    sendString="\r\nAT+CIPSEND=1,";
    sendString+=(String)(datalength)+"\r\n";
    Transceiver.print(sendString);
    sendState++;
  }else{
    Transceiver.print(Dequeue(SQ));
    sendState=0;
  }
  
  
}



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
