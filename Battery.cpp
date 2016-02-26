
#include "Arduino.h"
#include "Battery.h"

byte analog_num = 0x00;
struct adc{
  long adc_value = 0;
  int samples = 0;      //incase madaming pin na basahin
};
struct adc adc[5];


volatile uint8_t _pin;
 
 
void Battery::enable1(uint8_t pin)
{
  _pin = pin;
  DIDR0 = 0x3F;         //disable all digital pins
  ADMUX = 0x40;         //reference voltage is 5V
  ADCSRA = 0x8F;        //prescaler is 128

  ADMUX |= _pin;
  bitWrite(ADCSRA,6,1);   //enable conversion
} 


uint16_t Battery::getReading1(uint8_t pin)
{
  uint16_t voltage;
  voltage = (adc[_pin].adc_value/adc[_pin].samples);
  adc[analog_num].adc_value = 0;
  adc[analog_num].samples = 0; 


  return voltage;
}



/* ISR(ADC_vect) {
  adc[analog_num].adc_value += ADCL;        // store lower byte ADC
  adc[analog_num].adc_value += ADCH << 8;  // store higher bytes ADC
  adc[analog_num].samples++;           //increment samples, kaya isr,, may samples.

  analog_num++;
  ADCSRA = 0x8F;                            // Enable the ADC, Interrupt with 128 prescaler
  ADCSRA |=B01000000;                       //Restart the conversion
} */



//void convertToPercentage()
//{
//    int maximumVoltage = 5; 
//    double convertToVoltage;
//    int convertedPercentage;
//
//  convertToVoltage = ((voltage*maximumVoltage)/1023)*100;
//  convertedPercentage = (convertToVoltage/500)*100;
//  Serial.print(convertedPercentage);
//  Serial.println("%");
//}

