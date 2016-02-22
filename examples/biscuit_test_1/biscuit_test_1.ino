#include <biscuitos.h>

biscuitos sched1;
uint16_t a[10];

uint16_t lpt = 0;
uint8_t t = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Starting...");
  delay(1000);
  
  sched1.initialize();
  
  for(uint8_t i = 0; i<10;i++){
    a[i]=0;
  }
  sched1.addProcess(p0,500);
  sched1.addProcess(p1,9);
  sched1.addProcess(p2,100);
  sched1.addProcess(p3,100);
  sched1.addProcess(p4,100);
  sched1.addProcess(p5,100);
  sched1.addProcess(p6,250);
  sched1.addProcess(p7,500);
  sched1.addProcess(p8,250);
  sched1.addProcess(p9,1000);
  //sched1.printQueue();
  sched1.start();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(millis()>lpt + 1000){
    Serial.print(t);
    
    for(uint8_t i = 0; i<10;i++){
      Serial.print("\t");
      Serial.print(a[i]);
    }
    Serial.print("\n");
    for(uint8_t i = 0; i<10;i++){
      a[i]=0;
    }
    t++;
    lpt = millis();
  }
}

void p0(){
  a[0]++;
}
void p1(){
  a[1]++;
}
void p2(){
  a[2]++;
}
void p3(){
  a[3]++;
}
void p4(){
  a[4]++;
}
void p5(){
  a[5]++;
}
void p6(){
  a[6]++;
}
void p7(){
  a[7]++;
}
void p8(){
  a[8]++;
}
void p9(){
  a[9]++;
}
