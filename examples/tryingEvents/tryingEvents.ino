#include <timedevent.h>
timedevent timeThis;
uint16_t a = 0; 
uint16_t b = 0; 
uint16_t c = 0; 
uint16_t d = 0; 
uint16_t t = 0; 
uint32_t lpt = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //timeThis.timeIn(1000,process1);
  //timeThis.timeIn(4000,process1);
  
  timeThis.timeIn(250,pA);
  timeThis.timeIn(1000,pB);
  timeThis.timeIn(3000,pC);
  timeThis.timeIn(4000,pD);
  timeThis.timeIn(990,printPs);
  Serial.print("\t");
  timeThis.printQueue();
  printC();
  timeThis.timeStart();
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
void printC(){
  Serial.println("t\ta\tb\tc\td");
}
void printPs(){
  //if(millis()>lpt+1000){
    t++;
    Serial.print(t);
    Serial.print("\t");
    Serial.print(a);
    Serial.print("\t");
    Serial.print(b);
    Serial.print("\t");
    Serial.print(c);
    Serial.print("\t");
    Serial.println(d);
    
    //lpt=millis();
  //}
}

void process1(){
  Serial.println("Marco");
}
void process2(){
  Serial.println("Polo");
}

void pA(){
  a++;
}
void pB(){
  b++;
}
void pC(){
  c++;
}
void pD(){
  d++;
}

