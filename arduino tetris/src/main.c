#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <usart.h>

#define DATA_PIN_1 PD2
#define DATA_PIN_2 PD5
#define PUSH_CLOCK_1 PD3
#define PUSH_CLOCK_2 PD6
#define UPDATE_CLOCK_1 PD4
#define UPDATE_CLOCK_2 PD7

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

void lightUpWholeMatrix(){
  //light down the clocks
  PORTD &= ~(1 << UPDATE_CLOCK_1);
  PORTD &= ~(1 << UPDATE_CLOCK_2);

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
  PORTD |= (1 << UPDATE_CLOCK_1);
  PORTD |= (1 << UPDATE_CLOCK_2);
}

void lightDownWholeMatrix(){
  //light down the clocks
  PORTD &= ~(1 << UPDATE_CLOCK_1);
  PORTD &= ~(1 << UPDATE_CLOCK_2);

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
  PORTD |= (1 << UPDATE_CLOCK_1);
  PORTD |= (1 << UPDATE_CLOCK_2);
}

void setRow(int row){
  if (row < 1 || row > 8) return;
  row = row-1;
  
  //light down the clocks
  PORTD &= ~_BV(UPDATE_CLOCK_2);

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
  PORTD |= _BV(UPDATE_CLOCK_2);
  
}

void setColumn(int col){
  if (col < 1 || col > 8) return;
  col = col-1;
  
  //light down the clocks
  PORTD &= ~_BV(UPDATE_CLOCK_1);

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
  PORTD |= _BV(UPDATE_CLOCK_1);
}

void setMultipleColumns(uint8_t cols){
  //light down the clocks
  PORTD &= ~_BV(UPDATE_CLOCK_1);

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
  PORTD |= _BV(UPDATE_CLOCK_1);
  _delay_ms(1);
}

void displayRow(int row, uint8_t columns){
  setRow(row);
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
  DDRD |= (1 << UPDATE_CLOCK_1);
  DDRD |= (1 << UPDATE_CLOCK_2);
  DDRD |= (1 << PUSH_CLOCK_1);
  DDRD |= (1 << PUSH_CLOCK_2);

  PORTD &= ~(1 << PUSH_CLOCK_1);
  PORTD &= ~(1 << PUSH_CLOCK_2);

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