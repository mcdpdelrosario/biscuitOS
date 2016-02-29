#include <ADCv2.h>
#include <biscuitos.h>
#include <myWifi.h>
#include <PWMSoftware.h>
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  rScheduler.initialize();
  rADC.enable(0);
  rScheduler.addProcess(technicaldept,16);
  rScheduler.addProcess(printADC0Reading,1000);
  rScheduler.start();
}

void loop() {
  // put your main code here, to run repeatedly:

}
void printADC0Reading(){
  Serial.println(rADC.getReading(0));
}
void technicaldept(){
  
}

