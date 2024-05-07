#include <avr/io.h>
#include <usart.h>
#include <util/delay.h>



int main(){
  DDRC &= ~(1 << PC1);
  PORTC |= (1 << PC1);

  DDRB |= (1 << 2);
  PORTB |= (1 << 2);

  initUSART();

  while(1){
    if (bit_is_clear(PINC, PC1)) {
      PORTB ^= (1 << 2);
      _delay_ms(100);
    }
  }

}