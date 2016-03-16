#include <ADCv2.h>
#include <biscuitos.h>
#include <Motor.h>
#include <PWMSoftware.h>
#include <ServoEnhance.h>
#include <UARTv1.h>
#include <Wifi.h>


uint32_t lpt = 0;
uint32_t lpt2 = 0;
uint16_t resolution = 250;


void setup() {
Transceiver.start(9600);
motors.initialize(0,6,42,6.67);
motors.setPeriod(0,20);
motors.setTime(0,10);      
motors.setTarget(0,3);
motors.changeDirection(0,1);      //1 for forward
//digitalWrite(42,HIGH);
//tape wire = 44;
//if interchange, the direction print will be opposite

}

void loop() {

  if(millis()>lpt2+resolution)
  {
    motors.correctSpeed(0);
    motors.getDirection();
    lpt2 = millis();
  }
//  if(millis()>lpt2+resolution)
//  {
//    motors.setTarget(0,700);
//    //motors.setTarget(1,500);
//
//    lpt2 = millis();
//  }
   if (millis() > lpt + 1000)
  {

   Transceiver.println((String)motors.getSpeed(0));
   Transceiver.println("-");
   
   lpt = millis();
  }
  
  
}
