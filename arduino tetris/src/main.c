#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <usart.h>

#define DATA_PIN_1 PD0
#define DATA_PIN_2 PD3
#define CLOCK_INTERNAL_1 PD1
#define CLOCK_INTERNAL_2 PD4
#define CLOCK_1 PD2
#define CLOCK_2 PD5

// void cleanDisplay(){

// }
void lightUpWholeDisplay(){
  PORTD &= ~(1 << CLOCK_2);
  printf("turning off the master clock\n");
  _delay_ms(50);
  PORTD &= ~(1 << CLOCK_INTERNAL_2);
  _delay_ms(50);
  

  PORTD |= (1 << DATA_PIN_2);
  _delay_ms(50);
  PORTD |= (1 << DATA_PIN_2);
  _delay_ms(50);

  for (int i = 0; i < 8; i++)
  {
    printf("internal clock pulse #%d\n", i);
    PORTD |= (1 << CLOCK_INTERNAL_2);
    _delay_ms(200);
    PORTD &= ~(1 << CLOCK_INTERNAL_2);
    _delay_ms(200);
  }
  _delay_ms(50);
  PORTD |= (1 << CLOCK_2);
  
  
  printf("turning back on the master clock\n");

  
}



// void displayMatrix(int matrix[][]){

// }


int main(){
  // int screen[8][8] = {
  // {0,0,0,0,0,0,0,0},
  // {0,0,0,0,0,0,0,0},
  // {0,0,0,0,0,0,0,0},
  // {0,0,0,0,0,0,0,0},
  // {0,0,0,0,0,0,0,0},
  // {0,0,0,0,0,0,0,0},
  // {0,0,0,0,0,0,0,0},
  // {0,0,0,0,0,0,0,0}};

  DDRD |= (1 << DATA_PIN_1);
  DDRD |= (1 << DATA_PIN_2);
  DDRD |= (1 << CLOCK_1);
  DDRD |= (1 << CLOCK_2);
  DDRD |= (1 << CLOCK_INTERNAL_1);
  DDRD |= (1 << CLOCK_INTERNAL_2);

  PORTD &= ~(1 << CLOCK_INTERNAL_1);
  PORTD &= ~(1 << CLOCK_INTERNAL_2);

  initUSART();

  lightUpWholeDisplay();
}