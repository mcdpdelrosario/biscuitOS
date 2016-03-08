#include <ADCv2.h>
#include <biscuitos.h>
#include <Motor.h>
#include <PWMSoftware.h>
#include <ServoEnhance.h>
#include <UARTv1.h>
#include <Wifi.h>





void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  /*for(uint8_t a=0;a<5;a++){
  adc1.enable(a);
  }*/
  rADC.enable(0);
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  /*for(uint8_t b=0;b<6;b++){
  Serial.print(adc1.getReading(b));
  Serial.print("\t");
  }
  Serial.print("\n");*/
  Serial.println(rADC.getReading(0));
}
