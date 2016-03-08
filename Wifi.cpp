#include "Arduino.h"
#include "Wifi.h"
#include "UARTv1.h"
#include "PWMSoftware.h"
// #include <UARTv1/UARTv1.h>
#include <avr/interrupt.h>

void control(char Command) {

  switch (Command) {
    case 'X':
    	digitalWrite(42,LOW);
    	digitalWrite(43,LOW);
    	motorLeft.setPWM(10);
    	motorRight.setPWM(10);
        Transceiver.print("S\n");
      break;
    case 'W':
    	digitalWrite(42,LOW);
    	digitalWrite(43,LOW);
    	motorLeft.setPWM(300);
    	motorRight.setPWM(300);
        Transceiver.print("W\n");
      break;
    case 'D':
    	digitalWrite(42,LOW);
    	digitalWrite(43,LOW);
    	motorLeft.setPWM(150);
    	motorRight.setPWM(300);
        Transceiver.print("D\n");
      break;
    case 'A':
    	digitalWrite(42,LOW);
    	digitalWrite(43,LOW);
    	motorLeft.setPWM(300);
    	motorRight.setPWM(150);
        Transceiver.print("A\n");
      break;

    case 'S':
    	//digitalWrite(42,)
    	digitalWrite(42,HIGH);
    	digitalWrite(43,HIGH);
    	motorLeft.setPWM(300);
    	motorRight.setPWM(300);
        Transceiver.print("S\n");
      break;
    case 'F':
        Transceiver.print("F\n");
      break;
    default:
      break;
  }
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

void Wifi::initialize(uint16_t baud, String apName, String pass){
  Transceiver.baud(baud);
  sendData("AT+CWJAP=\""+apName+"\",\""+pass+"\"\r\n",8000);  
}

void Wifi::listen(String portNumber, String IP){
  sendData("AT+CIPMUX=1\r\n",1000);
  sendData("AT+CIPSERVER=1,"+portNumber+"\r\n",2000);
  sendData("AT+CIPSTA=\""+IP+"\"\r\n",3000);
  Transceiver.print("Connect Now!\n");
}

boolean statemachine = LOW;
char dataneed;

void Wifi::receive(){
  if(Transceiver.peek()>0){
    char letter = Transceiver.receive();
  if(statemachine ==HIGH){
    if(letter == ']'){
//     Transceiver.send((String)dataneed);
      statemachine = LOW; 
    }
    else{
//      Transceiver.send((String)dataneed);
    control(letter);
    }
  }
  else if(letter == '~'){
    statemachine = HIGH; 
  }
  }
}

