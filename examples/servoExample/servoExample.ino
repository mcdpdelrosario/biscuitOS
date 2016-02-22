#include <ServoV1.h>
ServoV1 servo1,servo2,servo3,servo4;

void setup() {
  // put your setup code here, to run once:
  servo1.attachServo(3);
  servo2.attachServo(9);
  servo3.attachServo(10);
  servo4.attachServo(11);
  

  
}


void loop() {
  // put your main code here, to run repeatedly:
  servo1.setAngle(0);
  servo2.setAngle(0);
  servo3.setAngle(0);
  servo4.setAngle(0);
  delay(1000);
  servo1.setAngle(180);
  servo2.setAngle(180);
  servo3.setAngle(180);
  servo4.setAngle(180);
  delay(1000);

  if(millis()>10000){
    servo1.detachServo();
  }
}
