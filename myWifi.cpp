#include "Arduino.h"
#include "myWifi.h"
#define DEBUG true

String response="";
char dataneed;
boolean statemachine = LOW;
boolean S1P0 = LOW;
boolean W1P1 = LOW;
boolean WHEEL_T = LOW;
boolean W2P2 = LOW;
boolean Ba1 = LOW;
int timeoutSend = 1000;
int stringLength;
String string = "";
int timeglobal;
long lastprocesstime = 0l;
boolean stateSend = LOW;
boolean stateSent = HIGH;

#define MAX_QUEUES 2
#define RECIEVE_QUEUE 0
#define SEND_QUEUE 1
#define QUEUE_SIZE 20
#define head 0

struct DataQ {
  unsigned int queue[QUEUE_SIZE];
  int tail;
};
struct DataQ q[MAX_QUEUES];


myWifi::myWifi(String apName,String pass,String IP, String portNumber){
	
	_apName = apName;
	_pass = pass;
	_IP = IP;
	_portNumber = portNumber;
	
}


void myWifi::wifiInit(){
	sendData("AT+CWMODE=?\r\n",1000,DEBUG);
	sendData("AT+CWMODE=1\r\n",2000,DEBUG);
	sendData("AT+CWJAP=\""+_apName+"\",\""+_pass+"\"\r\n",5000,DEBUG);  
}

void myWifi::wifiListen(){
	sendData("AT+CIPMUX=1\r\n",1000,DEBUG);
	sendData("AT+CIPSERVER=1,"+_portNumber+"\r\n",1000,DEBUG);
	sendData("AT+CIPSTA=\""+_IP+"\"\r\n",1000,DEBUG);
}

void myWifi::sendData(String command, const int timeout, boolean debug){
	response = "";
    
    Serial.print(command); // send the read character to the esp8266
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(Serial.available())
      {
        
        // The esp has data so display its output to the serial window 
        char c = Serial.read(); // read the next character.
        response+=c;
      }  
     
    }

if(debug)
    {
     // Serial.println(response);
    }  

	
}

void myWifi::wifiReceive(){
	
	if(Serial.available()){
    char letter = Serial.read();
  if(statemachine ==HIGH){
    if(letter == ']'){
  
     Serial.println(dataneed);
      statemachine = LOW; 
      //Serial.println("state is LOW");
      dataneed=0;
    }
    else{
    Control_Everything(dataneed);
    dataneed +=letter;
    }
  }
  else if(letter == '~'){
    statemachine = HIGH; 
    //Serial.println("state is HIGH");
  }
  }
	
	
}

void myWifi::Control_Everything(char Command) {

  switch (Command) {
    case 'S':
		Serial.println("S");
        
      break;

    case 'Q':
      break;

    case 'W'://masmabagal ung left
      	Serial.println("W");
        
      break;

    case 'D':
		Serial.println("D");
      
      break;
    case 'A':
		Serial.println("A");
      
      break;
    case 'X':
     
      //decrease forward target speed
      break;

    case 'R':
	
	
      break;
    case 'F': 
	
	
      break;
    default:
      break;

  }
}

void myWifi::wifiGather() {

  if (S1P0 != LOW && Ba1 != LOW && W1P1 != LOW && W2P2 != LOW && WHEEL_T != LOW) { //STATE RESET
    S1P0 = LOW;
    W1P1 = LOW;
    WHEEL_T = LOW;
    W2P2 = LOW;
    Ba1 = LOW;
  }
  if (S1P0 != HIGH) { //servo
    Enqueue(SEND_QUEUE, 32767);
    Enqueue(SEND_QUEUE, 32763);
    Enqueue(SEND_QUEUE, 01);
    Enqueue(SEND_QUEUE, 32766);
    S1P0 = HIGH;
  }
  else if (W1P1 != HIGH) { //w1
    Enqueue(SEND_QUEUE, 32767);
    Enqueue(SEND_QUEUE, 32761);
    Enqueue(SEND_QUEUE, 02);
    Enqueue(SEND_QUEUE, 32766);

    W1P1 = HIGH;
  }
  else if (W2P2 != HIGH) {//w2
    Enqueue(SEND_QUEUE, 32767);
    Enqueue(SEND_QUEUE, 32757);
    Enqueue(SEND_QUEUE, 03);
    Enqueue(SEND_QUEUE, 32766);

    W2P2 = HIGH;
  }
  else if (WHEEL_T != HIGH) {//wt
    Enqueue(SEND_QUEUE, 32767);
    Enqueue(SEND_QUEUE, 32759);
    //lastSpeedProcessMillis1 = lastSpeedProcessMillis / 1000;
    Enqueue(SEND_QUEUE, 04);
    Enqueue(SEND_QUEUE, 32766);

    WHEEL_T = HIGH;
  }
  else if (Ba1 != HIGH) {//ba
    Enqueue(SEND_QUEUE, 32767);
    Enqueue(SEND_QUEUE, 32765);
    Enqueue(SEND_QUEUE, 05);
    Enqueue(SEND_QUEUE, 32766);
    Ba1 = HIGH;
  }
}

void myWifi::wifiSend() {
  string = "";
  int data = 0;
  int  sendThis = Dequeue(SEND_QUEUE);
  string.concat(sendThis);
  sendThis = Dequeue(SEND_QUEUE);
  string.concat(sendThis);
  data = Dequeue(SEND_QUEUE);
  string.concat(data);
  sendThis = Dequeue(SEND_QUEUE);
  string.concat(sendThis);
  sendThis = Dequeue(SEND_QUEUE);
  string.concat(sendThis);
  stringLength = string.length() + 1;
}

void myWifi::sendTry() {
  if (stateSent == HIGH) {
    wifiGather();
    wifiSend();
    stateSent = LOW;
  } else {
    sendDataSend(stringLength, 100);
  }

}

void myWifi::sendDataSend(int stringLengthSend, int timeoutSend)
{
  timeglobal = timeoutSend;
  if (millis() > timeglobal + lastprocesstime) {

    if (stateSend == LOW) {
      Serial.print("AT+CIPSEND=0,");
      Serial.println(stringLengthSend);
      stateSend = HIGH;
    }
    else {
      Serial.print(string + "\r\n");
      Serial.println("AT+CIPSEND");
      stateSent = HIGH;
      stateSend = LOW;
    }
    lastprocesstime = millis();
  }

}

void myWifi::Enqueue(int queue_number, unsigned int data) {
  //Serial.println(data);
  if (q[queue_number].tail == QUEUE_SIZE) {
    return;
  }
  q[queue_number].queue[q[queue_number].tail] =  data;
  q[queue_number].tail++;
}
int myWifi::Dequeue(int queue_number) {
  int out = 0;
  if (q[queue_number].tail <= 0) {
    return -1;
  }
  out = q[queue_number].queue[head];
  for (int temp = 0; temp < (q[queue_number].tail - 1); temp++) {
    q[queue_number].queue[temp] = q[queue_number].queue[temp + 1];
  }
  q[queue_number].tail--;
  return out;
}

void myWifi::Queue_Init() {
  for (int temp = 0; temp < MAX_QUEUES; temp ++) {
    q[temp].tail = 0;
  }
}

long timeoutControl = 0l;