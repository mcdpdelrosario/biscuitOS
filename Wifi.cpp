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
struct pointme p;

uint8_t sendState=0;
String secondFrame;
void Wifi::gather(char openingTag,char classifier,uint16_t data){
  // Transceiver.print((String)data);
    char frame[10];
    String sendString;
    char lengthdata;
    uint8_t datalength;
    char temp;
    if(data==256){
      data=257;
    }
    caller.data=data;
    
    lengthdata=Transceiver.getLength(caller.cdata);
    combo.cdata[0]=caller.sdata[0] + caller.sdata[1];
    // Transceiver.print((String)combo.sdata[0]);

    //frame=openingTag + classifier + (String)lengthdata + (String)caller.cdata[0] + (String)caller.cdata[1] + (String)combo.cdata[0] ;  
    uint8_t nextInLine = 0;
    frame[nextInLine]=openingTag; nextInLine++;
    frame[nextInLine]=classifier;nextInLine++;
    frame[nextInLine]=lengthdata;nextInLine++;
    while((nextInLine-3)<lengthdata){
      frame[nextInLine]=caller.cdata[nextInLine-3];
      //Transceiver.println("\t"+(String)caller.sdata[nextInLine-3]+"\t");
      nextInLine++;
    }
    frame[nextInLine] = combo.cdata[0];nextInLine++;
    while(nextInLine<10){
      frame[nextInLine] = 0x00;
      nextInLine++;
    }

    datalength=Transceiver.getLength(frame);
    secondFrame=frame;
    sendString="AT+CIPSEND=1,";
    sendString+=(String)(datalength)+"\r\n";
    Transceiver.print(sendString);
  
}

void Wifi::send(){

  Transceiver.print(secondFrame);
}

void Wifi::commands(void (*functionCallBack)(char))
{
   p.functions = functionCallBack;
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


void Wifi::initialize(String apName, String pass){
  sendData("AT+CWMODE=1\r\n",1000);  
  sendData("AT+CWJAP=\""+apName+"\",\""+pass+"\"\r\n",8000);  
}

void Wifi::listen(String ID, String portNumber, String IP){
  sendData("AT+CIPMUX=1\r\n",1000);
  sendData("AT+CIPSTART="+ ID +",\"TCP\",\""+ IP +"\","+portNumber+"\r\n",2000);
  Transceiver.print("Connected!");
}

int8_t statemachine = 0;
char dataReceived;
void Wifi::receive(char receiveTagStart,char receiveTagEnd){
  // if(Transceiver.peek()>0){
  //   char letter = Transceiver.receive();
  //   if(statemachine==HIGH){
  //       statemachine = LOW;
  //       p.functions(letter);
  //   }
  //   else if(letter == receiveTag){
  //     statemachine = HIGH; 
  //   }
  // }
  if(Transceiver.peek()>0){
    char letter = Transceiver.receive();
    if(letter == receiveTagStart && statemachine==0){
      statemachine = 1;
    }else if(statemachine==1){
      dataReceived = letter;
      statemachine=2;
    }else if(statemachine==2 && letter == receiveTagEnd){
      p.functions(dataReceived);
      statemachine = 0;
    }else{
      statemachine = 0;
    }
  }


}
