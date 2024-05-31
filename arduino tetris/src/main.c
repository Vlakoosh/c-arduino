#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <usart.h>
//library made by me
#include <ledmatrixlib.h>

//set pins for breadboard buttons
#define BUTTON_LEFT PB4
#define BUTTON_RIGHT PB5
#define BUTTON_UP PC0
#define BUTTON_DOWN PC1
#define BUTTON_A PC2
#define BUTTON_B PC3

void initButton() {
  DDRB &= ~(1 << BUTTON_LEFT);
  PORTB |= (1 << BUTTON_LEFT);

  DDRB &= ~(1 << BUTTON_RIGHT);
  PORTB |= (1 << BUTTON_RIGHT);
  
  DDRC &= ~(1 << BUTTON_UP);
  PORTC |= (1 << BUTTON_UP);
  
  DDRC &= ~(1 << BUTTON_DOWN);
  PORTC |= (1 << BUTTON_DOWN);
  
  DDRC &= ~(1 << BUTTON_A);
  PORTC |= (1 << BUTTON_A);
  
  DDRC &= ~(1 << BUTTON_B);
  PORTC |= (1 << BUTTON_B);
}

int main(){
  testDisplay();
}