#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <usart.h>

#define DATA_PIN_1 PD4
#define DATA_PIN_2 PD6
#define PUSH_CLOCK_1 PD5
#define PUSH_CLOCK_2 PD7
#define CLOCK PD2

#define BUTTON_LEFT PB4
#define BUTTON_RIGHT PB5
#define BUTTON_UP PC0
#define BUTTON_DOWN PC1
#define BUTTON_A PC2
#define BUTTON_B PC3

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

void lightUpWholeMatrix(){
  //light down the clocks
  PORTD &= ~(1 << CLOCK);

  PORTD &= ~(1 << PUSH_CLOCK_1);
  PORTD &= ~(1 << PUSH_CLOCK_2);

  PORTD &= ~(1 << DATA_PIN_1);
  PORTD |= (1 << DATA_PIN_2);
  
  for (int i = 0; i < 8; i++)
  {
    //push LOW bits for columns, and HIGH bits for rows
    PORTD |= (1 << PUSH_CLOCK_1);
    PORTD |= (1 << PUSH_CLOCK_2);

    PORTD &= ~(1 << PUSH_CLOCK_1);
    PORTD &= ~(1 << PUSH_CLOCK_2);
  }
  //update the output
  PORTD |= (1 << CLOCK);
}

void lightDownWholeMatrix(){
  //light down the clocks
  PORTD &= ~(1 << CLOCK);

  PORTD &= ~(1 << PUSH_CLOCK_1);
  PORTD &= ~(1 << PUSH_CLOCK_2);

  PORTD |= (1 << DATA_PIN_1);
  PORTD &= ~(1 << DATA_PIN_2);
  
  for (int i = 0; i < 8; i++)
  {
    //push LOW bits for columns, and HIGH bits for rows
    PORTD |= (1 << PUSH_CLOCK_1);
    PORTD |= (1 << PUSH_CLOCK_2);

    PORTD &= ~(1 << PUSH_CLOCK_1);
    PORTD &= ~(1 << PUSH_CLOCK_2);
  }
  //update the output
  PORTD |= (1 << CLOCK);
}

void setRow(int row){
  if (row < 1 || row > 8) return;
  row = row-1;
  
  //light down the clocks
  PORTD &= ~_BV(CLOCK);

  PORTD &= ~_BV(PUSH_CLOCK_2);

  PORTD |= _BV(DATA_PIN_2);

  for (int i = 0; i < 8; i++)
  {
    if (row == i)
    {
      PORTD |= _BV(DATA_PIN_2);
    }
    else PORTD &= ~_BV(DATA_PIN_2);
    PORTD |= _BV(PUSH_CLOCK_2);
    PORTD &= ~_BV(PUSH_CLOCK_2);
  }
  PORTD |= _BV(CLOCK);
  
}

void setColumn(int col){
  if (col < 1 || col > 8) return;
  col = col-1;
  
  //light down the clocks
  PORTD &= ~_BV(CLOCK);

  PORTD &= ~_BV(PUSH_CLOCK_1);

  PORTD |= _BV(DATA_PIN_1);

  for (int i = 0; i < 8; i++)
  {
    if (col == i)
    {
      PORTD &= ~_BV(DATA_PIN_1);
    }
    else PORTD |= _BV(DATA_PIN_1);
    PORTD |= _BV(PUSH_CLOCK_1);
    PORTD &= ~_BV(PUSH_CLOCK_1);
  }
  PORTD |= _BV(CLOCK);
}

void setMultipleColumns(uint8_t cols){
  //light down the clocks
  PORTD &= ~_BV(CLOCK);

  PORTD &= ~_BV(PUSH_CLOCK_1);

  PORTD |= _BV(DATA_PIN_1);

  for (int i = 0; i < 8; i++)
  {
    if (cols & (1<<i))
    {
      PORTD &= ~_BV(DATA_PIN_1);
    }
    else PORTD |= _BV(DATA_PIN_1);
    PORTD |= _BV(PUSH_CLOCK_1);
    PORTD &= ~_BV(PUSH_CLOCK_1);
  }
  PORTD |= _BV(CLOCK);
  _delay_ms(1);
}

void displayRow(int row, uint8_t columns){
  setRow(row);
  setMultipleColumns(columns);
}

// void displayMatrix(int matrix[][]){

// }


int main(){

  DDRD |= (1 << DATA_PIN_1);
  DDRD |= (1 << DATA_PIN_2);
  DDRD |= (1 << CLOCK);
  DDRD |= (1 << CLOCK);
  DDRD |= (1 << PUSH_CLOCK_1);
  DDRD |= (1 << PUSH_CLOCK_2);

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

  PORTD &= ~(1 << PUSH_CLOCK_1);
  PORTD &= ~(1 << PUSH_CLOCK_2);

  lightDownWholeMatrix();
  initUSART();
  while (1)
  {
    // lightDownWholeMatrix();
    // _delay_ms(500);
    // lightUpWholeMatrix();
    // _delay_ms(500);
    setRow(1);
    setMultipleColumns((uint8_t) 0b00011000);
    setRow(2);
    setMultipleColumns((uint8_t) 0b00111100);
    setRow(3);
    setMultipleColumns((uint8_t) 0b01111110);
    setRow(4);
    setMultipleColumns((uint8_t) 0b11011011);
    setRow(5);
    setMultipleColumns((uint8_t) 0b11111111);
    setRow(6);
    setMultipleColumns((uint8_t) 0b00111100);
    setRow(7);
    setMultipleColumns((uint8_t) 0b01111110);
    setRow(8);
    setMultipleColumns((uint8_t) 0b10100101);
    
    
    

    
    
    
  }
}