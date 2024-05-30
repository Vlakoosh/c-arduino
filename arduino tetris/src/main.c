#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <usart.h>
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

  init();
  initButton();

  lightUpWholeTopMatrix();
  lightUpWholeBottomMatrix();
  initUSART();
  // _delay_ms(1000);
  // setColumnOnBottomMatrix(3);
  // _delay_ms(1000);
  // setRowOnBottomMatrix(5);

  _delay_ms(500);
  // while (1)
  {

    while(1)
    {
      
      for (int i = 1; i <= 16; i++)
      {
        if (i == 1)
        {
          setMultipleColumnsOnBottomMatrix(0b00000000);
        }
        if (i == 9)
        {
          setMultipleColumnsOnTopMatrix(0b00000000);
        }
        
        for (int x = 0; x < 8; x++)
        {
          uint8_t cols;
          if (i % 2)
          {
            cols = _BV(x);          
          }
          else {
            cols = cols = _BV(7-x);  
          }
          displayRow(i, cols);
          _delay_ms(50);          
        }
        
      }
      
    }
    
  }
}