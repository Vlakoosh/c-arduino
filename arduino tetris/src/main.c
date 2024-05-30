#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <usart.h>
#include <ledmatrixlib.h>

// void displayMatrix(int matrix[]){

// }

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

  lightDownWholeTopMatrix();
  lightUpWholeBottomMatrix();
  initUSART();
  // _delay_ms(1000);
  // setColumnOnBottomMatrix(3);
  // _delay_ms(1000);
  // setRowOnBottomMatrix(5);

  // _delay_ms(500);
  while (1)
  {
    for (int i = 0; i < 50; i++)
    {
      displayRow( 1, 0b00000000);
      displayRow( 2, 0b00000000);
      displayRow( 3, 0b00000000);
      displayRow( 4, 0b00000000);
      
      displayRow( 5, 0b00000000);
      displayRow( 6, 0b00000000);
      displayRow( 7, 0b00000000);
      displayRow( 8, 0b11110011);
      
      displayRow( 9, 0b11111011);
      displayRow(10, 0b11101111);
      displayRow(11, 0b01111111);
      displayRow(12, 0b01111111);
      
      displayRow(13, 0b11101111);
      displayRow(14, 0b11110101);
      displayRow(15, 0b00111111);
      displayRow(16, 0b10111111);
      
    }

    for (int i = 0; i < 50; i++)
    {
      displayRow( 1, 0b00000100);
      displayRow( 2, 0b00000000);
      displayRow( 3, 0b00000000);
      displayRow( 4, 0b00000000);
      
      displayRow( 5, 0b00000000);
      displayRow( 6, 0b00000000);
      displayRow( 7, 0b00000000);
      displayRow( 8, 0b11110011);
      
      displayRow( 9, 0b11111011);
      displayRow(10, 0b11101111);
      displayRow(11, 0b01111111);
      displayRow(12, 0b01111111);
      
      displayRow(13, 0b11101111);
      displayRow(14, 0b11110101);
      displayRow(15, 0b00111111);
      displayRow(16, 0b10111111);
      
    }

    for (int i = 0; i < 50; i++)
    {
      displayRow( 1, 0b00001100);
      displayRow( 2, 0b00000100);
      displayRow( 3, 0b00000000);
      displayRow( 4, 0b00000000);
      
      displayRow( 5, 0b00000000);
      displayRow( 6, 0b00000000);
      displayRow( 7, 0b00000000);
      displayRow( 8, 0b11110011);
      
      displayRow( 9, 0b11111011);
      displayRow(10, 0b11101111);
      displayRow(11, 0b01111111);
      displayRow(12, 0b01111111);
      
      displayRow(13, 0b11101111);
      displayRow(14, 0b11110101);
      displayRow(15, 0b00111111);
      displayRow(16, 0b10111111);
      
    }
    
    for (int i = 0; i < 50; i++)
    {
      displayRow( 1, 0b00000100);
      displayRow( 2, 0b00001100);
      displayRow( 3, 0b00000100);
      displayRow( 4, 0b00000000);
      
      displayRow( 5, 0b00000000);
      displayRow( 6, 0b00000000);
      displayRow( 7, 0b00000000);
      displayRow( 8, 0b11110011);
      
      displayRow( 9, 0b11111011);
      displayRow(10, 0b11101111);
      displayRow(11, 0b01111111);
      displayRow(12, 0b01111111);
      
      displayRow(13, 0b11101111);
      displayRow(14, 0b11110101);
      displayRow(15, 0b00111111);
      displayRow(16, 0b10111111);
      
    }

    for (int i = 0; i < 50; i++)
    {
      displayRow( 1, 0b00000000);
      displayRow( 2, 0b00000100);
      displayRow( 3, 0b00001100);
      displayRow( 4, 0b00000100);
      
      displayRow( 5, 0b00000000);
      displayRow( 6, 0b00000000);
      displayRow( 7, 0b00000000);
      displayRow( 8, 0b11110011);
      
      displayRow( 9, 0b11111011);
      displayRow(10, 0b11101111);
      displayRow(11, 0b01111111);
      displayRow(12, 0b01111111);
      
      displayRow(13, 0b11101111);
      displayRow(14, 0b11110101);
      displayRow(15, 0b00111111);
      displayRow(16, 0b10111111);
      
    }
    for (int i = 0; i < 50; i++)
    {
      displayRow( 1, 0b00000000);
      displayRow( 2, 0b00000000);
      displayRow( 3, 0b00000100);
      displayRow( 4, 0b00001100);
      
      displayRow( 5, 0b00000100);
      displayRow( 6, 0b00000000);
      displayRow( 7, 0b00000000);
      displayRow( 8, 0b11110011);
      
      displayRow( 9, 0b11111011);
      displayRow(10, 0b11101111);
      displayRow(11, 0b01111111);
      displayRow(12, 0b01111111);
      
      displayRow(13, 0b11101111);
      displayRow(14, 0b11110101);
      displayRow(15, 0b00111111);
      displayRow(16, 0b10111111);
      
    }

    for (int i = 0; i < 50; i++)
    {
      displayRow( 1, 0b00000000);
      displayRow( 2, 0b00000000);
      displayRow( 3, 0b00000000);
      displayRow( 4, 0b00000100);
      
      displayRow( 5, 0b00001100);
      displayRow( 6, 0b00000100);
      displayRow( 7, 0b00000000);
      displayRow( 8, 0b11110011);
      
      displayRow( 9, 0b11111011);
      displayRow(10, 0b11101111);
      displayRow(11, 0b01111111);
      displayRow(12, 0b01111111);
      
      displayRow(13, 0b11101111);
      displayRow(14, 0b11110101);
      displayRow(15, 0b00111111);
      displayRow(16, 0b10111111);
      
    }

    for (int i = 0; i < 50; i++)
    {
      displayRow( 1, 0b00000000);
      displayRow( 2, 0b00000000);
      displayRow( 3, 0b00000000);
      displayRow( 4, 0b00000000);
      
      displayRow( 5, 0b00000100);
      displayRow( 6, 0b00001100);
      displayRow( 7, 0b00000100);
      displayRow( 8, 0b11110011);
      
      displayRow( 9, 0b11111011);
      displayRow(10, 0b11101111);
      displayRow(11, 0b01111111);
      displayRow(12, 0b01111111);
      
      displayRow(13, 0b11101111);
      displayRow(14, 0b11110101);
      displayRow(15, 0b00111111);
      displayRow(16, 0b10111111);
      
    }

    for (int i = 0; i < 50; i++)
    {
      displayRow( 1, 0b00000000);
      displayRow( 2, 0b00000000);
      displayRow( 3, 0b00000000);
      displayRow( 4, 0b00000000);
      
      displayRow( 5, 0b00000000);
      displayRow( 6, 0b00000100);
      displayRow( 7, 0b00001100);
      displayRow( 8, 0b11110111);
      
      displayRow( 9, 0b11111011);
      displayRow(10, 0b11101111);
      displayRow(11, 0b01111111);
      displayRow(12, 0b01111111);
      
      displayRow(13, 0b11101111);
      displayRow(14, 0b11110101);
      displayRow(15, 0b00111111);
      displayRow(16, 0b10111111);
      
    }

    while(1)
    {
      displayRow( 1, 0b00000000);
      displayRow( 2, 0b00000000);
      displayRow( 3, 0b00000000);
      displayRow( 4, 0b00000000);
      
      displayRow( 5, 0b00000000);
      displayRow( 6, 0b00000000);
      displayRow( 7, 0b00000100);
      displayRow( 8, 0b11111111);
      
      displayRow( 9, 0b11111111);
      displayRow(10, 0b11101111);
      displayRow(11, 0b01111111);
      displayRow(12, 0b01111111);
      
      displayRow(13, 0b11101111);
      displayRow(14, 0b11110101);
      displayRow(15, 0b00111111);
      displayRow(16, 0b10111111);
      
    }
    
  }
}