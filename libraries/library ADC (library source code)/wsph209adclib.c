#include "wsph209adclib.h"

#include <avr/io.h>
#include <avr/interrupt.h>

void initADC() {
  ADMUX |= (1 << REFS0);                                // Set up the reference voltage. We choose 5V as the reference.
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Determine the sample rate by setting the division factor to 1028.
}

void readSensorAndWait(int pin) {
  ADMUX = 64+pin;                                       //Set MUX0-3 to read analog input from the sensor
  ADCSRA |= (1 << ADEN);                                // Enable the ADC 
  ADCSRA |= (1 << ADSC);                                // Start the analog-to-digital conversion
  while (bit_is_set(ADCSRA, ADSC));                     // Wait till reading is done
}

void disableADC() {
}

void getSensorData(int pin, int* value){
    readSensorAndWait(pin);
    *value = ADC;
    disableADC();
}