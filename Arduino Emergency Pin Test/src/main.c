#include <avr/io.h>
#include <util/delay.h>

int main() {

  DDRD = 0b11111111;
  DDRB = 0b11111100;

  while (1)
  {
    PORTD = 0b11111111;
    PORTB = 0b11111111;
    _delay_ms(500);
    PORTD = 0b00000000;
    PORTB = 0b00000000;
    _delay_ms(500);
  }
  
}