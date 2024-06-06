#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#define LED1 2
#define LED2 3
#define LED3 4
#define BUTTON1 PC1

ISR (PCINT1_vect) {
  //check if button 1 is pressed (pin of button is 0 in PORTC)
  if(bit_is_clear(PINC, BUTTON1)){
    //turn on led 2 and 3
    PORTB &= ~(1 << LED2);
    PORTB &= ~(1 << LED3);
    _delay_ms(5000);
    //turn off led 2 and 3
    PORTB |= (1 << LED2);
    PORTB |= (1 << LED3);
    _delay_ms(5000);
  }
}

int main(){

  //enable button 1 pin as input (set it to 0 in data direction register)
  DDRC &= ~(1 << BUTTON1);

  //enable led 1-3 pins as output (set it to 1 in data direction register)
  DDRB |= (1 << LED1);
  DDRB |= (1 << LED2);
  DDRB |= (1 << LED3);

  //light down all the enabled LEDs
  PORTB |= (1 << LED1);
  PORTB |= (1 << LED2);
  PORTB |= (1 << LED3);

  //enable listening for interrupts in PORTC (0-B, 1-C, 2-D)
  PCICR |= (1 << PCIE1);
  //enable listening to button 1 in portC (0-B, 1-C, 2-D)
  PCMSK1 |= (1 << BUTTON1);

  //enable interrupts
  sei();

  //infinite loop that turns LED 1 on and off
  while(1){
    PORTB ^= (1 << LED1);
    _delay_ms(2000);
    PORTB ^= (1 << LED1);
    _delay_ms(2000);
  }
}