#include "Arduino.h"
#include "UARTv1.h"
#include <avr/interrupt.h>
#define RQ 0
#define SQ 1
#define QUEUE_SIZE 100
struct DataQ {
  char queue[QUEUE_SIZE];
  int8_t tail;
};
struct DataQ DataQ[2]; 
void Enqueue(uint8_t queue_number, char data);
char Dequeue(uint8_t queue_number);
uint8_t getLength(String str);
void UARTv1::start(uint32_t baudRate){

    UCSR0A = 0x02;
    UCSR0C = 0x06;
    UCSR0B = 0x98;
    uint32_t baud = (((16e6)/(8*baudRate)))-1;
    UBRR0 = baud;
    
}
uint8_t UARTv1::peek(){
  return DataQ[RQ].tail;
}
void UARTv1::print(String data){
  uint8_t temp;
  temp = getLength(data);
  for(uint8_t i=0;i<temp;i++){
   Enqueue(SQ, data[i]);
  }
  UCSR0B |= 0x20;
}
void UARTv1::println(String data){
  uint8_t temp;
  temp = getLength(data);
  for(uint8_t i=0;i<temp;i++){
   Enqueue(SQ, data[i]);
  }
  Enqueue(SQ, '\n');
  UCSR0B |= 0x20;
}
char UARTv1::receive(){
  return Dequeue(RQ);
}
uint8_t getLength(String str){
  uint8_t num;
  num=0;
  while(str[num]!=0x00){
    num++;
  }
  return num;
}
void Enqueue(uint8_t queue_number, char data){
  if(DataQ[queue_number].tail == QUEUE_SIZE){
    return;
  }
  DataQ[queue_number].queue[DataQ[queue_number].tail] =  data;
  DataQ[queue_number].tail++;
}
char Dequeue(uint8_t queue_number){
  if(DataQ[queue_number].tail==0){
    return 0x00;
  }
  char out;
  out=DataQ[queue_number].queue[0];
  DataQ[queue_number].tail--;
  for(uint8_t temp = 0; temp < (DataQ[queue_number].tail); temp++){
    DataQ[queue_number].queue[temp] = DataQ[queue_number].queue[temp+1];
  }
  return out;
}
ISR(USART0_RX_vect){
  Enqueue(RQ,UDR0);
  //UCSR0B |= 0x20; //enable ISR UART transmit
}
volatile uint8_t Qtemp;
ISR(USART0_UDRE_vect){
  
  Qtemp = Dequeue(SQ);
  if(Qtemp == 0x00)
    UCSR0B &= 0xDF;
  else
      UDR0 = Qtemp;
  //UCSR0B &= 0xDF; //disable ISR UART transmit
}
