#include <Battery.h>

Battery b;


void setup() {
  Serial.begin(9600);
  b.enable(0);
  b.setMode(1);
}
void loop() {

  b.getReading(0);
  b.convertToPercentage();
}


