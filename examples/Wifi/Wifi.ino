#include <ADCv2.h>
#include <biscuitos.h>
#include <Motor.h>
#include <PWMSoftware.h>
#include <ServoEnhance.h>
#include <UARTv1.h>
#include <Wifi.h>

void setup() {
  Transceiver.start(9600);
  // put your setup code here, to run once:
  Wifi.initialize(9600,"PLDTHOMEDSL_YSHIE","88888888"); //Wifi.initialize(baud,apName,password);
  Wifi.listen("8000","192.168.1.7"); //Wifi.listen(portNumber,ip address);
  Wifi.commands(control);
  rScheduler.initialize();
  rScheduler.addProcess(technicaldept,16);
//  rScheduler.addProcess(quickFix,8);
  rScheduler.start();
}

void loop() {
  // put your main code here, to run repeatedly:
  Wifi.receive();
}
char myCommand;

void control(char Command) {

  switch (Command) {
    case 'X':
      digitalWrite(42,LOW);
      digitalWrite(43,LOW);
      //motorLeft.setPWM(10);
      //motorRight.setPWM(10);
        Transceiver.print("S\n");
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
    case 'F':
        Transceiver.print("F\n");
      break;
    default:
      break;
  }
}
void technicaldept(){
  
}
