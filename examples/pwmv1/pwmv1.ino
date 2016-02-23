#include <PWMSoftware.h>

PWMSoftware p1(3,1);
PWMSoftware p2(3,2);
PWMSoftware p3(3,3);
PWMSoftware p11(1,1);
PWMSoftware p21(1,2);
PWMSoftware p31(1,3);


void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);

p1.setPeriod1(312);
p2.setPeriod1(312);
p3.setPeriod1(312);
p11.setPeriod1(312);
p21.setPeriod1(312);
p31.setPeriod1(312);

}

void loop() {
  // put your main code here, to run repeatedly:
p1.setPWM(9);
p2.setPWM(9);
p3.setPWM(9);
p11.setPWM(9);
p21.setPWM(9);
p31.setPWM(9);
delay(1000);
p1.setPWM(38);
p2.setPWM(38);
p3.setPWM(38);
p11.setPWM(38);
p21.setPWM(38);
p31.setPWM(38);
delay(1000);
}
