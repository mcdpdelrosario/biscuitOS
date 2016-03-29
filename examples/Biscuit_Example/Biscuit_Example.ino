#include <ADCv2.h>
#include <biscuitos.h>
#include <DEBUGv1.h>
#include <Motor.h>
#include <PWMSoftware.h>
#include <ServoEnhance.h>
#include <UARTv1.h>
#include <Wifi.h>
uint16_t count = 0;
char myCommand;
uint8_t ServoFlag = 0;
uint8_t currentAngle = 0;
uint32_t timePassed = 0;
ServoEnhance ServoAuto,ServoWifi;
void setup() {
  // put your setup code here, to run once:
  Transceiver.start(9600);
  Transceiver.println("Initializing");
  delay(1000);
  //Wifi.initialize(9600,"PLDTHOMEDSL_YSHIE","88888888"); //Wifi.initialize(baud,apName,password);
  //Wifi.listen("8000","192.168.1.7"); //Wifi.listen(portNumber,ip address);
  //Wifi.commands(control);
  ServoAuto.attach(3);
  ServoWifi.attach(2);
  rADC.enable(4);
  rScheduler.initialize();
  rScheduler.addProcess(Counter,16);
  rScheduler.addProcess(changeServo,2000);
  rScheduler.addProcess(printBatteryReading,10000);
  rScheduler.addProcess(printSecondsPast,1000);
  rScheduler.start();
}

void loop() {
  // put your main code here, to run repeatedly:
  //Wifi.receive();
  UARTcontrol();
}
void printSecondsPast(){
  Transceiver.print((String)timePassed+"\t");
  timePassed++;
}
void printBatteryReading(){
  Transceiver.println((String)rADC.getReading(4));
}
void changeServo(){
  if(ServoFlag == 0){
  ServoAuto.setAngle(0);
  ServoFlag = 1;
  }
  else{
  ServoAuto.setAngle(180);
  ServoFlag = 0;
  }
}

void UARTcontrol(){
  switch(Transceiver.receive()){
    case 'R':
    currentAngle += 3;
    if(currentAngle>180){
      currentAngle = 180;
    }
    ServoWifi.setAngle(currentAngle);
    break;
    case 'F':
    currentAngle -= 3;
    if(currentAngle<5){
      currentAngle = 5;
    }
    ServoWifi.setAngle(currentAngle);
    break;
    case NULL:
    break;
    default:
    break;
  }
}

void control(char Command) {

  switch (Command) {
    case 'X':
      digitalWrite(42,LOW);
      digitalWrite(43,LOW);
      //motorLeft.setPWM(10);
      //motorRight.setPWM(10);
        Transceiver.println("X"); 
      break;
    case 'W':
      digitalWrite(42,LOW);
      digitalWrite(43,LOW);
      //motorLeft.setPWM(300);
      //motorRight.setPWM(300);
        Transceiver.print("W\n");
      break;
    case 'D':
      digitalWrite(42,LOW);
      digitalWrite(43,LOW);
      //motorLeft.setPWM(150);
      //motorRight.setPWM(300);
        Transceiver.print("D\n");
      break;
    case 'A':
      digitalWrite(42,LOW);
      digitalWrite(43,LOW);
      //motorLeft.setPWM(300);
      //motorRight.setPWM(150);
        Transceiver.print("A\n");
      break;
    case 'S':
      //digitalWrite(42,)
      digitalWrite(42,HIGH);
      digitalWrite(43,HIGH);
      //motorLeft.setPWM(300);
      //motorRight.setPWM(300);
        Transceiver.print("S\n");
      break;
    case 'R':
        currentAngle += 3;
        if(currentAngle>180){
          currentAngle = 180;
        }
        ServoWifi.setAngle(currentAngle);
        Transceiver.println("R\n");
      break;
    case 'F':
        currentAngle -= 3;
        if(currentAngle<5){
          currentAngle = 5;
        }
        ServoWifi.setAngle(currentAngle);
        Transceiver.println("F");
      break;
    default:
      break;
  }
}
void Counter(){
  
  count++;
}

