#include <ADCv2.h>
#include <biscuitos.h>
#include <Motor.h>
#include <PWMSoftware.h>
#include <ServoEnhance.h>
#include <UARTv1.h>
#include <Wifi.h>

//7 is A, 18(with tape) and 19
uint8_t cangle = 90;
uint32_t lpt = 0;
uint32_t lpt2 = 0;
uint16_t resolution = 250;
uint8_t flagServo = 0;
uint32_t c = 0;
int x=0;
int y=0;
ServoEnhance servo1;
void setup() {
rScheduler.initialize();                                                  //Initialize the scheduler and all the registers inside needed
Transceiver.start(9600);                                                  //Set baud rate and initialize UART
//Transceiver.println("loading");
//Wifi.initialize(9600,"yshie","88888888"); //Wifi.initialize(baud,apName,password);
//Wifi.listen("8000","192.168.1.7"); //Wifi.listen(portNumber,ip address);
motors.initialize(0,6,42,45);                                           //Initialize num for struct as identifier of the motor, PWMPin, Direction Pin and diameter
motors.initialize(1,7,43,45);
motors.setPeriod(0,20);                                                   //Sets the total period. 20 = 20mS
motors.setPeriod(1,20);
servo1.attach(3);
rADC.enable(0);                                   //Sets the direction. 1 means forward, 0 means backward
servo1.setAngle(180);
//motors.setTime(0,500);
motors.setTarget(0, 150);//digitalWrite(42,HIGH);if 0 = means forward
motors.setTarget(1, 150);
//10000/50 = targetSpeed                                              
rScheduler.addProcess(loopMotor,250);                                     //Loop motor function will run for every 250mS rScheduler.addProcess(printSpeed,1000);                                   //printSpeed will run every 1 second
//rScheduler.addProcess(turnSpeed,4000);                                    //turnSpeed will run every 3 seconds
//rScheduler.addProcess(moveServo,2000);
//rScheduler.addProcess(printSpeed,1000);
rScheduler.addProcess(check,500);
//rScheduler.addProcess(printReading,1000);
rScheduler.addProcess(counter,16);                                  
rScheduler.start();                                                       //Starts all processes

}

void printReading(){
  Transceiver.println((String)rADC.getReading(0));
  Transceiver.println("-");
}
char tempSpeed = 0;
void loop() {
  //Wifi.receive();
  if(Transceiver.peek()>0){
    tempSpeed = Transceiver.receive();
    motors.setTarget(0,tempSpeed);//digitalWrite(42,HIGH);if 0 = means forward
    motors.setTarget(1,tempSpeed);
  }
}
char myCommand;
void loopMotor()
{
   motors.correctSpeed(0);                                                //Corrects the speed of the motor based on the number of ticks set by the user every 250mS
   motors.correctSpeed(1);
   Transceiver.println("");
}

void check()
{
//  motors.checkPresentTime(0);
}

void printSpeed()
{

//Transceiver.println((String)motors.printPID(0));
                                                                           //Prints speed every 1second
// motors.getDirection(0);
//   Transceiver.println((String)motors.targetTime(0));
//   Transceiver.println((String)motors.presentTime(0));
//   Transceiver.println((String)motors.pastTime(0));
//Transceiver.println((String)motors.actualTime(0));
//   Transceiver.println((String)motors.pastError(0));
Transceiver.print(((String)motors.currentError(0))+ "\t");
Transceiver.println((String)motors.currentError(1));
 //Transceiver.println((String)motors.sumError(0));
//  Transceiver.println((String)motors.getSpeed(1));
 //  Transceiver.println("--------------");
  //motors.resetFlags();
   //int 2 ay 19, int 6 ay 44
   
}

void counter()
{
  c++;
}
void moveServo(){
  if(flagServo == 0){
    servo1.setAngle(0);
    flagServo = 1;
  }
  else{
    servo1.setAngle(180);
    flagServo = 0;
  }
}
uint8_t angel=0;
void turnSpeed()     {                                                 //Function that changes the target ticks for every n seconds;

  if(angel==0)
  {
    //motors.changeDirection(0,0); 
    //motors.changeDirection(1,0); 
    motors.setTarget(0,2);
    motors.setTarget(1,2);
    angel = 1;  
    //Transceiver.println("A");
  }else {
      //motors.changeDirection(0,1);
      //motors.changeDirection(1,1);  
      motors.setTarget(0,2);
      motors.setTarget(1,2);
      angel = 0;
      //Transceiver.println("B");
    }
}

void control(char Command) {

  switch (Command) {
    case 'X':
      motors.changeDirection(0,1);  //low is backward therefore 1
      motors.changeDirection(1,1);
      motors.setTarget(0,3);
      motors.setTarget(1,3);
        Transceiver.print("X\n");
      break;
    case 'W':
      motors.changeDirection(0,1);
      motors.changeDirection(1,1);
      motors.setTarget(0,3);
      motors.setTarget(1,3);
        Transceiver.print("W\n");
      break;
    case 'D':
      motors.changeDirection(0,1);
      motors.changeDirection(1,1);
       motors.setTarget(0,3);     
      motors.setTarget(1,1);
        Transceiver.print("D\n");
      break;
    case 'A':
      motors.changeDirection(0,1);
      motors.changeDirection(1,1);      
       motors.setTarget(0,1);
      motors.setTarget(1,3);
      
        Transceiver.print("A\n");
      break;

    case 'S':
      //digitalWrite(42,)
      motors.changeDirection(0,0);
      motors.changeDirection(0,0);
      //motorLeft.setPWM(300);
      //motorRight.setPWM(300);
        Transceiver.print("S\n");
      break;
    case 'F':
        cangle -=3;
        if(cangle<4){
          cangle = 4;
        }
        servo1.setAngle(cangle);  
        Transceiver.print("F\n");
      break;
    case 'R':
        cangle +=3;
        if(cangle>180){
          cangle = 180;
        }
        servo1.setAngle(cangle);  
        Transceiver.print("R\n");
      break;

    default:
      break;
  }
}
