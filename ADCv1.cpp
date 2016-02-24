#include "Arduino.h"
#include "ADCv1.h"
#include <avr/interrupt.h>
#define disabledADC 0;
#define enabledADC 1;
typedef union{
  uint16_t mixVar;
  uint8_t byteVar[2];
}combo;
struct adcStruct{
  uint8_t pin;
  combo adc_value;  
}; struct adcStruct adcStruct[8];
uint8_t _adcTail;
uint8_t current;
ADCv1::ADCv1(){
	_adcTail = 0;
	current = 0;
}
void ADCv1::enable(uint8_t pin){
	adcStruct[_adcTail].pin = pin;
	_adcTail++;
	DIDR0 = 0x01 << pin;
}

void ADCv1::setMode(uint8_t mode){
	ADMUX = 0x40 + adcStruct[current].pin;
	ADCSRA = 0x8F;
	ADCSRA |=0x40;
}

uint16_t ADCv1::getReading(uint8_t pin){
	for(uint8_t k=0; k<_adcTail; k++){
		if(adcStruct[k].pin == pin){
			return adcStruct[k].adc_value.mixVar;
		}
	}
	return 0;
}
ISR(ADC_vect){
  adcStruct[current].adc_value.byteVar[0] = ADCL;
  adcStruct[current].adc_value.byteVar[1] = ADCH;
  current++;
  if(current==_adcTail){
    current=0;
  }
  ADMUX = 0x40 + adcStruct[current].pin;
  ADCSRA |= 0x40;
}