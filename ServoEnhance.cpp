#include "Arduino.h"
#include "ServoEnhance.h"
#include "PWMSoftware.h"

 

ServoEnhance::ServoEnhance(){

}

void ServoEnhance::attach(uint8_t pin){
	
	
_pin = pin;

switch(_pin){
//Timer 3
case 3:
	p.init(3,3);
	p.setPeriod(40000);
	 //Serial.println("JOSHUA POGI 3");
		break;
case 2:p.init(3,2);
		p.setPeriod(40000);
	//Serial.println("JOSHUA POGI 2");
		break;
case 5:p.init(3,1);
	p.setPeriod(40000);
		// Serial.println("JOSHUA POGI 5");
		break;
		//Timer 1
case 6:p.init(1,3);
	p.setPeriod(40000);
		 // Serial.println("JOSHUA POGI 6");
		break;
case 7:p.init(1,2);
	p.setPeriod(40000);
 // Serial.println("JOSHUA POGI 7");
		break;
case 9:p.init(1,1);
	p.setPeriod(40000);
		 // Serial.println("JOSHUA POGI 9");
		break;
default:
 // Serial.println("JOSHUA POGI 123");
	
	break;
}


}

void ServoEnhance::setAngle(uint32_t angle){
	uint32_t y;
	y = ((angle*380)/18) + 1000;
Serial.println(y);	
p.setPWM(y);
}



void ServoEnhance::detach(uint8_t dpin){
	
	
	
	
	
}

