#include <Battery.h>

Battery a;
void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);
a.enable(2);
}

void loop() {
  // put your main code here, to run repeatedly:

Serial.println(a.getReading(2));
}
