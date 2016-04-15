#include "Arduino.h"
#include "ServoEnhance.h"
#include "PWMSoftware.h"
#include "ImaginaryPWM.h"

 // 0 = hrdware
 //1 = pwm software
ServoEnhance::ServoEnhance(){

}
void ServoEnhance::attach(uint8_t pin){
_pin = pin;
switch(_pin){
//Timer 3
//ACCURATE PWM
case 3:
	p.init(3,3);
	p.setPeriod(40000);
	_flagServo = 1;
		break;
case 2:p.init(3,2); 
		p.setPeriod(40000);
		_flagServo = 1;
		break;
case 5:p.init(3,1);
 	   p.setPeriod(40000);
		_flagServo = 1;
		break;
		//Timer 1
case 7:p.init(1,3);
	   p.setPeriod(40000);
		_flagServo = 1;
		break;
case 6:p.init(1,2);
	   p.setPeriod(40000);
		_flagServo = 1;
		break;
case 9:p.init(1,1);
	   p.setPeriod(40000);
	   _flagServo = 1;
	break;

case 4:i.servoInit(4); //PG5
_flagServo =0;
		//DDRG | = 0x20;
		break;
case 8:i.servoInit(8); //PB4
		_flagServo =0;
		//DDRB | =0x10;
		break;
case 10:i.servoInit(10);
_flagServo =0;// PB0
		//DDRB| = 0x01;
		break;
case 11:i.servoInit(11);
_flagServo =0; // PB2
		//DDRB| =0x04;
		break;
case 12:i.servoInit(12); // PB3
		_flagServo =0;
		///DDRB| = 0x08;
		break;
case 13:i.servoInit(13); // PB1
		_flagServo =0;
		//DDRB =0x02;
		break;
default:

	break;
}
}

void ServoEnhance::setAngle(uint32_t angle){
	uint32_t y;
	_currentAngle = angle;
	if(_flagServo==1){
	y = ((angle*390)/18) + 1100;
	p.setPWM(y);
	}
	else{
	i.setAngle(angle);
	}
}



void ServoEnhance::detach(uint8_t pin){
	
	_pin = pin;
switch(_pin){
	case 3:
			p.detachPin(3,3);
		break;
	case 2:
			p.detachPin(3,2);
		break;
	case 5:
			p.detachPin(3,1);
		break;
	case 7:
			p.detachPin(1,3);
	break;
	case 6:
			p.detachPin(1,2);
		break;
	case 9:
			p.detachPin(1,1);
		break;
	case 4:  DDRG&=B11011111;
	break; 
	case 8:  DDRB&=B11101111;
	break;
	case 10: DDRB&=B11111110;
	break;
	case 11: DDRB&=B11111011;
	break;
	case 12: DDRB&=B11110111;
	break;
	case 13: DDRB&=B11111101;
	break;
	default:
	break;
}
	 
	
}

uint8_t ServoEnhance::getAngle(){
	
	return _currentAngle;
	
}


