#include <ADCv2.h>
#include <biscuitos.h>
#include <Motor.h>
#include <PWMSoftware.h>
#include <ServoEnhance.h>
#include <UARTv1.h>
#include <Wifi.h>




void setup() {
  // put your setup code here, to run once:
  rScheduler.initialize();
  rADC.enable(0);
  Transceiver.start(8576);
  rScheduler.addProcess(technicaldept,16);
  rScheduler.addProcess(printADC0Reading,1000);
  rScheduler.start();
}

void loop() {
  // put your main code here, to run repeatedly:

}
void printADC0Reading(){
 Transceiver.println((String)rADC.getReading(0));
}
void technicaldept(){
  
}

