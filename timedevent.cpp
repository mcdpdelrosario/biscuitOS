#include "Arduino.h"
#include "timedevent.h"
#include <avr/interrupt.h>
void (*_function)();
typedef void (* FunctionPointer_t) ();
struct PCB {
  uint8_t id;
  uint8_t state;
  uint8_t priority;
  uint16_t rTime;
  uint16_t mTime;
  FunctionPointer_t pFunc;
};
struct PCB PCB[20];

struct pNext{
	FunctionPointer_t pFunc;
};
struct pNext pNext[5];
uint8_t _processTail;
void _enQueue(uint16_t _data,void (*pointF)());
void emptyQueue();
void queueProcess();
void adjustTime();
void pause();
void start();
void stop();
void disableTIMSK();
void restart();
void errorMsg();
uint8_t _timeTail;
void reinitiateProcess();
uint16_t _timeRedo;
uint16_t sICR;

timedevent::timedevent(){
	emptyQueue();
}

void timedevent::timeIn(uint16_t nextmS,void (*pointF)()){
	uint16_t temp;
	temp = nextmS*15.625;//limit is 65536 counts... or 4194 mS (4.2 Seconds)
	_enQueue(temp,pointF);
}

void _enQueue(uint16_t _data,void (*pointF)()){
	for(uint8_t i=0;i<_timeTail;i++){
		if(PCB[i].rTime>=_data){
			for(uint8_t j=_timeTail;j>i;j--){
				PCB[j].mTime = PCB[j-1].mTime;
				PCB[j].rTime = PCB[j-1].rTime;
				PCB[j].pFunc = PCB[j-1].pFunc;
				
			}
			PCB[i].mTime =_data;
			PCB[i].rTime=_data;
			PCB[i].pFunc = pointF;
			_timeTail++;
			return;
		}
	}
	PCB[_timeTail].rTime = _data;
	PCB[_timeTail].mTime =_data;
	PCB[_timeTail].pFunc = pointF;
	_timeTail++; 
}

void emptyQueue(){
	_timeTail = 0;
	_processTail = 0;
}
void timedevent::printQueue(){
	for(uint8_t i=0;i<_timeTail;i++){
	Serial.print(PCB[i].rTime);
	Serial.print("\t");
	}
	Serial.print("\n");
}
void timedevent::timeStart(){
	TCCR1A = 0x02;
	TCCR1B = 0x18;
	
	queueProcess();
	start();
}

void queueProcess(){
	if(_timeTail>0){
		
		sICR = PCB[0].rTime;
		ICR1 = sICR;
		_function = PCB[0].pFunc;
		_timeRedo = PCB[0].mTime;
		
		
		for(uint8_t i=0;i<_timeTail;i++){
			PCB[i].rTime = PCB[i+1].rTime;
			PCB[i].mTime = PCB[i+1].mTime;
			PCB[i].pFunc = PCB[i+1].pFunc;
		}
		_timeTail--;
		
	}else{
		errorMsg();
	}
}

void adjustTime(){
	for(uint8_t i=0;i<_timeTail;i++){
			PCB[i].rTime -= sICR;
	}
}

void reinitiateProcess(){
	_enQueue(_timeRedo,_function);
}

ISR(TIMER1_OVF_vect){
	disableTIMSK();
/* 	for(uint8_t i = 0; i<_processTail; i++){
		pNext[i].pFunc();
	} */
	_function();
	adjustTime();
	reinitiateProcess();
	queueProcess();
	restart();
}

void start(){
	TCCR1B |= 0x05;
	TIMSK1 = 0x01;
}
void pause(){
	TCCR1B &= 0xFA;
}
void stop(){
	TCCR1B &= 0xFA;
	TCNT1 = 0;
}
void disableTIMSK(){
	TIMSK1 = 0x00;
	ICR1 = 0xFFFF;
}
void restart(){
	TCNT1 = 0;
	TIMSK1 |= 0x01;
	TCCR1B |= 0x05;
}
void errorMsg(){
	Serial.println("UnderQueue");
}

