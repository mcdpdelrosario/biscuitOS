#include <ADCv2.h>
#include <biscuitos.h>
#include <Motor.h>
#include <PWMSoftware.h>
#include <ServoEnhance.h>
#include <UARTv1.h>
#include <Wifi.h>



void setup() {
  // put your setup code here, to run once:
  Wifi.initialize(9600,"yshie","88888888"); //Wifi.initialize(baud,apName,password);
  Wifi.listen("8000","192.168.1.7"); //Wifi.listen(portNumber,ip address);
  rScheduler.initialize();
  rScheduler.addProcess(technicaldept,16);
//  rScheduler.addProcess(quickFix,8);
  rScheduler.start();
}

void loop() {
  // put your main code here, to run repeatedly:
  Wifi.receive();
}
void quickFix(){
  
}
void technicaldept(){
  
}
