#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include <vellemanleds.h>

int main(){
  enableAllLeds();
  _delay_ms(500);
  lightDownAllLeds();
  _delay_ms(500);
  lightUpAllLeds();
  lightDownOneLed(2);
  dimLed(1, 90, 5);
  fadeInLed(2, 5);
  while (1)
  {
    
  }

  return 0;
}
