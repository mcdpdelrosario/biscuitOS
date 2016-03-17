#include "Arduino.h"
#include "biscuitos.h"
#include <avr/interrupt.h>
#define running 2;
#define ready 1;
#define stop 0;
typedef void (* FunctionPointer_t) ();
FunctionPointer_t _function;

typedef union {
  uint32_t varint;
  uint8_t varbyte[4];
} combo;

struct PCB {
	uint8_t ID;
	uint8_t state;
	uint8_t priority;
	combo timeTotal;
	FunctionPointer_t pFunc;
};	struct PCB PCB[20];
uint8_t _processNum;

struct PQ{
	combo rTime;
	uint8_t IDpt;
};	struct PQ PQ[20];
uint8_t _PQTail;

uint8_t IDprocessReady[10];
uint8_t _processReadyTail;
uint8_t cLimit;
void regStart();
void dequeueProcess();
void enqueueProcesses(uint8_t ID);
void biscuitos::initialize(){
	TCCR2A = 0x02;
	TCCR2B = 0x00;
	TIMSK2 = 0x02;
	_processReadyTail = 0;
	_processNum = 0;
	_PQTail = 0;
}

void biscuitos::addProcess(void (*pointF)(),uint16_t nextmS){
	uint32_t period;
	period = nextmS * 15.625;
	PCB[_processNum].ID = _processNum;
	PCB[_processNum].state = stop;
	PCB[_processNum].timeTotal.varint = period;
	PCB[_processNum].pFunc = pointF;
	enqueueProcesses(_processNum);
	_processNum++;
	
}
// void printAR(){
// 	for(uint8_t z = 0; z<_processNum;z++){
// 		Serial.print(PCB[z].ID);
// 		Serial.print("\t");
// 		Serial.print(PCB[z].timeTotal.varint);
// 		Serial.print("\t");
// 	} 
// 	Serial.print("\n");
// 	for(uint8_t z = 0; z<_PQTail;z++){
// 		Serial.print(PQ[z].IDpt);
// 		Serial.print("\t");
// 		Serial.print(PQ[z].rTime.varint);
// 		Serial.print("\t");
// 	}
// 	Serial.print("\n");
// }
void biscuitos::printQueue(){
	// printAR();
}
void biscuitos::start(){
	TCNT2 = 0;
	dequeueProcess();
	regStart();
}

void enqueueProcesses(uint8_t ID){
	for(uint8_t j = 0; j < _PQTail; j++){
		if(PQ[j].rTime.varint>= PCB[ID].timeTotal.varint){
			for(uint8_t k=_PQTail;k>j;k--){
				PQ[k].rTime.varint = PQ[k-1].rTime.varint;
				PQ[k].IDpt = PQ[k-1].IDpt;
			}
			PQ[j].rTime.varint = PCB[ID].timeTotal.varint;
			PQ[j].IDpt = ID;
			_PQTail++;
			return;
		}
	}
	PQ[_PQTail].rTime.varint = PCB[ID].timeTotal.varint;
	PQ[_PQTail].IDpt = ID;
	_PQTail++;
}

void reinitiateProcesses(){
	for(uint8_t i = _processReadyTail; i>0; i--){
		enqueueProcesses(IDprocessReady[i-1]);
	}
}

void runReadyProcesses(){
	
	for(uint8_t i = _processReadyTail; i>0; i--){
		PCB[IDprocessReady[i-1]].state = running;
		PCB[IDprocessReady[i-1]].pFunc();
		PCB[IDprocessReady[i-1]].state = stop;
	}
	
}
	
void dequeueProcess(){
	uint32_t tempTime;
	uint32_t tempTimeSub;
	//printAR();
	tempTime = TCNT2 + cLimit + PQ[0].rTime.varint;
	tempTimeSub = TCNT2 + cLimit;
	
	for(uint8_t y = 0; y<_PQTail; y++){
		if(PQ[y].rTime.varint <= tempTime){
			IDprocessReady[_processReadyTail]=PQ[y].IDpt;
			_processReadyTail++;
		}else{
			PQ[y].rTime.varint -= tempTimeSub;
		}
	}
	cLimit = PQ[0].rTime.varbyte[0];
	OCR2A = cLimit;
	_PQTail -= _processReadyTail;
	for(uint8_t y=0;y<_PQTail;y++){
		PQ[y].rTime.varint = PQ[y+_processReadyTail].rTime.varint;
		PQ[y].IDpt = PQ[y+_processReadyTail].IDpt;
	}
	
}

void regStart(){
	TCCR2B |= 0x07;
}
ISR(TIMER2_COMPA_vect){
	TCNT2 = 0;
	OCR2A = 255;
	TIMSK2 = 0x00;
	runReadyProcesses();
	reinitiateProcesses();
	_processReadyTail = 0;
	dequeueProcess();
	TIMSK2 = 0x02;
	TCNT2 = 0;
}
ISR(TIMER2_COMPB_vect){
}