//avr programming and arduino C libraries
#include <avr/io.h>
#include <util/delay.h>
#include <usart.h>
#include <avr/interrupt.h>
//libraries made by me
#include <ledmatrixlib.h>
//libraries made for C

//set pins for breadboard buttons
#define BUTTON_UP PC1
#define BUTTON_DOWN PC0
#define BUTTON_LEFT PB4
#define BUTTON_RIGHT PB5
#define BUTTON_A PC3
#define BUTTON_B PC2

//initialize button pins and their registers with correct values
void initButton() {
  //enable button pins as input
  DDRC &= ~_BV(BUTTON_UP);
  DDRC &= ~_BV(BUTTON_DOWN);
  DDRB &= ~_BV(BUTTON_LEFT);
  DDRB &= ~_BV(BUTTON_RIGHT);

  DDRC &= ~_BV(BUTTON_A);
  DDRC &= ~_BV(BUTTON_B);

  //set up pull-up resistors for button pins
  PORTC |= _BV(BUTTON_UP);
  PORTC |= _BV(BUTTON_DOWN);
  PORTB |= _BV(BUTTON_LEFT);
  PORTB |= _BV(BUTTON_RIGHT);

  PORTC |= _BV(BUTTON_A);
  PORTC |= _BV(BUTTON_B);
}

void initButtonInterrupts() {
  PCICR |= _BV(PCIE0);
  PCICR |= _BV(PCIE1);
  PCMSK0 |= _BV(BUTTON_LEFT);
  PCMSK0 |= _BV(BUTTON_RIGHT);
  PCMSK1 |= _BV(BUTTON_UP);
  PCMSK1 |= _BV(BUTTON_DOWN);
  PCMSK1 |= _BV(BUTTON_A);
  PCMSK1 |= _BV(BUTTON_B);
}

//interrupt for buttons connected to PORTB
ISR( PCINT0_vect ){
  printf("port b interrupt");
  if (bit_is_clear(PINB, BUTTON_LEFT))
  {
    printf("button LEFT pressed\n");
  }
  if (bit_is_clear(PINB, BUTTON_RIGHT))
  {
    printf("button RIGHT pressed\n");
  }
}

//interrupt for buttons connected to PORTC
ISR( PCINT1_vect ){
  printf("port c interrupt");
  if (bit_is_clear(PINC, BUTTON_UP))
  {
    printf("button UP pressed\n");
  }
  if (bit_is_clear(PINC, BUTTON_DOWN))
  {
    printf("button DOWN pressed\n");
  }
  if (bit_is_clear(PINC, BUTTON_A))
  {
    printf("button A pressed\n");
    lightUpWholeBottomMatrix();
  }
  if (bit_is_clear(PINC, BUTTON_B))
  {
    lightDownWholeBottomMatrix();
    printf("button B pressed\n");
  }
}

int main(){
  //enable button pins
  initButton();
  //set button interrupt registers
  initButtonInterrupts();
  //enable Matrix pins
  initMatrix();
  //enable serial communication
  initUSART();

  //enable global interrupts
  sei();
  printf("start!");


  while (0)
  {
    if (bit_is_clear(PINC, BUTTON_UP))
    {
      printf("button UP pressed\n");
    }
    if (bit_is_clear(PINC, BUTTON_DOWN))
    {
      printf("button DOWN pressed\n");
    }
    if (bit_is_clear(PINC, BUTTON_A))
    {
      printf("button A pressed\n");
      lightUpWholeBottomMatrix();
    }
    if (bit_is_clear(PINC, BUTTON_B))
    {
      lightDownWholeBottomMatrix();
      printf("button B pressed\n");
    }
    if (bit_is_clear(PINB, BUTTON_LEFT))
    {
      printf("button LEFT pressed\n");
    }
    if (bit_is_clear(PINB, BUTTON_RIGHT))
    {
      printf("button RIGHT pressed\n");
    }
  }
  while(1){
    _delay_ms(100);
  }
  
}