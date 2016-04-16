#include <ADCv2.h>
#include <biscuitos.h>
#include <DEBUGv1.h>
#include <ImaginaryPWM.h>
#include <Motor.h>
#include <PWMSoftware.h>
#include <ServoEnhance.h>
#include <UARTv1.h>
#include <Wifi.h>


ServoEnhance servoA,servoB,servoC,servoD,servoE,servoF,servoX,servoY,servoZ;


void setup() {
  // put your setup code here, to run once:
  Transceiver.start(9600);
servoX.attach(4);
servoY.attach(8);
servoZ.attach(11);
servoF.attach(2);
servoA.attach(3);
servoB.attach(5);
servoC.attach(6);
servoD.attach(7);
servoE.attach(9);
rScheduler.initialize();
rScheduler.addProcess(nagaraya,50);
rScheduler.start();
}
 uint8_t angle = 0;
void loop() {
  // put your main code here, to run repeatedly:
servoA.setAngle(180);
servoB.setAngle(180);
servoC.setAngle(180);
servoD.setAngle(180);
servoE.setAngle(180);
servoF.setAngle(180);
servoX.setAngle(180);
servoY.setAngle(180);
servoZ.setAngle(180);
angle = servoA.getAngle();
Transceiver.println((String)angle);
angle = servoB.getAngle();
Transceiver.println((String)angle);
angle = servoC.getAngle();
Transceiver.println((String)angle);

delay(1000);
servoA.setAngle(90);
servoB.setAngle(90);
servoC.setAngle(90);
servoD.setAngle(90);
servoE.setAngle(90);
servoF.setAngle(90);
servoX.setAngle(90);
servoY.setAngle(90);
servoZ.setAngle(90);
angle = servoA.getAngle();
Transceiver.println((String)angle);
angle = servoB.getAngle();
Transceiver.println((String)angle);
angle = servoC.getAngle();
Transceiver.println((String)angle);

delay(1000);
servoA.setAngle(0);
servoB.setAngle(0);
servoC.setAngle(0);
servoD.setAngle(0);
servoE.setAngle(0);
servoF.setAngle(0);
servoX.setAngle(0);
servoY.setAngle(0);
servoZ.setAngle(0);

angle = servoA.getAngle();
Transceiver.println((String)angle);
angle = servoB.getAngle();
Transceiver.println((String)angle);
angle = servoC.getAngle();
Transceiver.println((String)angle);

}
void nagaraya(){
 // Transceiver.print((String)5);
  PowerRanger.servoUpdate();
  
  }

