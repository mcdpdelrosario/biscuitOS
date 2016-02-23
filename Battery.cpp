/*
	Battery Module (battery.cpp)
	

*/	


#include "Arduino.h"
#include "Battery.h"
#include <avr/interrupt.h>



struct adc{
  long adc_value = 0;
  int samples = 0;      //incase madaming pin na basahin
};
struct adc adc[5];

uint8_t _pin;
int _mode;
double voltage;
int maximumVoltage = 5; 
double convertToVoltage;
int convertedPercentage;


void Battery::enable(int pin)
{
  _pin = pin;
  DIDR0 = 0x3F;         //disable all digital pins
  ADMUX = 0x40;         //reference voltage is 5V
  ADCSRA = 0x8F;        //prescaler is 128
} 

void Battery::setMode(int mode)
{
  _mode = mode;

  if(_mode==0)
  {
    bitWrite(ADCSRA,6,0);
  }
 else if(_mode==1)
  {
  ADMUX |= _pin;
  bitWrite(ADCSRA,6,1);   //enable conversion
  SREG = SREG|0x80;       //enable interrupt
  }
 
}

int Battery::getReading(int _pin){
  voltage = (adc[_pin].adc_value/adc[_pin].samples);
  adc[_pin].adc_value = 0;
  adc[_pin].samples = 0; 


}

void Battery::convertToPercentage()
{
  convertToVoltage = ((voltage*maximumVoltage)/1023)*100;
  convertedPercentage = (convertToVoltage/500)*100;
  Serial.print(convertedPercentage);
  Serial.println("%");
}

ISR(ADC_vect) {
  adc[_pin].adc_value += ADCL;        // store lower byte ADC
  adc[_pin].adc_value += ADCH << 8;  // store higher bytes ADC
  adc[_pin].samples++;           //increment samples, kaya isr,, may samples.

  ADCSRA = 0x8F;                            // Enable the ADC, Interrupt with 128 prescaler
  ADCSRA |=B01000000;                       //Restart the conversion
}
