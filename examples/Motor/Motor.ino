#include <ADCv2.h>
#include <Battery.h>
#include <biscuitos.h>
#include <Motor.h>
#include <myWifi.h>
#include <PWMSoftware.h>



uint32_t lpt = 0;
uint32_t lpt2 = 0;
uint16_t resolution = 500;

Motor motors;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
motors.initialize(0,6,44,6.67);
motors.initialize(1,7,45,6.67);
motors.setPeriod(0,20);
motors.setPeriod(1,20);
motors.setTime(0,70);    
motors.setTime(1,70);     

}

void loop() {

//  if(millis()>lpt2+resolution)
//  {
//    motors.setTarget(0,700);
//    //motors.setTarget(1,500);
//
//    lpt2 = millis();
//  }
   if (millis() > lpt + 500)
  {
   Serial.println(motors.getSpeed(0));
   Serial.println(motors.getSpeed(1));
   Serial.println("-");
   
    lpt = millis();
  }
  
  
}
