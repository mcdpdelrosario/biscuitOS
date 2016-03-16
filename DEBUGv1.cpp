#include "Arduino.h"
#include "DEBUGv1.h"
#include <avr/interrupt.h>
#define RQ 0
#define SQ 1
#define QUEUE_SIZE 100
struct DataQZ {
  char queue[QUEUE_SIZE];
  int8_t tail;
};
struct DataQZ DataQZ[2]; 
void EnqueueZ(uint8_t queue_number, char data);
char DequeueZ(uint8_t queue_number);
uint8_t getLengthZ(String str);
void DEBUGv1::initialize(uint16_t baudRate){

  UCSR0A = 0x02;
  UCSR0C = 0x06;
  UBRR0 = 207;
  UCSR0B = 0x98;
}
uint8_t DEBUGv1::peek(){
  return DataQZ[RQ].tail;
}
void DEBUGv1::send(String data){
  uint8_t temp;
  temp = getLengthZ(data);
  for(uint8_t i=0;i<temp;i++){
   EnqueueZ(SQ, data[i]);
  }
  UCSR0B |= 0x20;
}
char DEBUGv1::receive(){
  return DequeueZ(RQ);

}
uint8_t getLengthZ(String str){
  uint8_t num;
  num=0;
  while(str[num]!=0x00){
    num++;
  }
  return num;
}
void EnqueueZ(uint8_t queue_number, char data){
  if(DataQZ[queue_number].tail == QUEUE_SIZE){
    return;
  }
  DataQZ[queue_number].queue[DataQZ[queue_number].tail] =  data;
  DataQZ[queue_number].tail++;
}
char DequeueZ(uint8_t queue_number){
  if(DataQZ[queue_number].tail==0){
    return 0x00;
  }
  char out;
  out=DataQZ[queue_number].queue[0];
  DataQZ[queue_number].tail--;
  for(uint8_t temp = 0; temp < (DataQZ[queue_number].tail); temp++){
    DataQZ[queue_number].queue[temp] = DataQZ[queue_number].queue[temp+1];
  }
  return out;
}
ISR(USART1_RX_vect){
  EnqueueZ(RQ,UDR0);
  //UCSR0B |= 0x20; //enable ISR UART transmit
}
volatile uint8_t QtempZ;
ISR(USART1_UDRE_vect){
  
  QtempZ= DequeueZ(SQ);
  if(QtempZ== 0x00)
    UCSR0B &= 0xDF;
  else
      UDR0 = QtempZ;
  //UCSR0B &= 0xDF; //disable ISR UART transmit
}
