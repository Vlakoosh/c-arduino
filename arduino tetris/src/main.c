#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <usart.h>

#define DATA_PIN_COLUMN_1 PD4
#define DATA_PIN_ROW_1 PD6
#define PUSH_PIN_COLUMN_1 PD5
#define PUSH_PIN_ROW_1 PD7

#define DATA_PIN_COLUMN_2 PB2
#define DATA_PIN_ROW_2 PB0
#define PUSH_PIN_COLUMN_2 PB1
#define PUSH_PIN_ROW_2 PB3

#define CLOCK PD2

#define BUTTON_LEFT PB4
#define BUTTON_RIGHT PB5
#define BUTTON_UP PC0
#define BUTTON_DOWN PC1
#define BUTTON_A PC2
#define BUTTON_B PC3

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

void lightUpWholeTopMatrix(){
  //light down the clocks
  PORTD &= ~(1 << CLOCK);

  PORTD &= ~(1 << PUSH_PIN_COLUMN_1);
  PORTD &= ~(1 << PUSH_PIN_ROW_1);

  PORTD &= ~(1 << DATA_PIN_COLUMN_1
);
  PORTD |= (1 << DATA_PIN_ROW_1);
  
  for (int i = 0; i < 8; i++)
  {
    //push LOW bits for columns, and HIGH bits for rows
    PORTD |= (1 << PUSH_PIN_COLUMN_1);
    PORTD |= (1 << PUSH_PIN_ROW_1);

    PORTD &= ~(1 << PUSH_PIN_COLUMN_1);
    PORTD &= ~(1 << PUSH_PIN_ROW_1);
  }
  //update the output
  PORTD |= (1 << CLOCK);
}

void lightDownWholeTopMatrix(){
  //light down the clocks
  PORTD &= ~(1 << CLOCK);

  PORTD &= ~(1 << PUSH_PIN_COLUMN_1);
  PORTD &= ~(1 << PUSH_PIN_ROW_1);

  PORTD |= (1 << DATA_PIN_COLUMN_1);
  PORTD &= ~(1 << DATA_PIN_ROW_1);
  
  for (int i = 0; i < 8; i++)
  {
    //push LOW bits for columns, and HIGH bits for rows
    PORTD |= (1 << PUSH_PIN_COLUMN_1);
    PORTD |= (1 << PUSH_PIN_ROW_1);

    PORTD &= ~(1 << PUSH_PIN_COLUMN_1);
    PORTD &= ~(1 << PUSH_PIN_ROW_1);
  }
  //update the output
  PORTD |= (1 << CLOCK);
}

void lightUpWholeBottomMatrix(){
  //light down the clocks
  PORTD &= ~(1 << CLOCK);

  PORTB &= ~(1 << PUSH_PIN_COLUMN_2);
  PORTB &= ~(1 << PUSH_PIN_ROW_2);

  PORTB &= ~(1 << DATA_PIN_COLUMN_2
);
  PORTB |= (1 << DATA_PIN_ROW_2);
  
  for (int i = 0; i < 8; i++)
  {
    //push LOW bits for columns, and HIGH bits for rows
    PORTB |= (1 << PUSH_PIN_COLUMN_2);
    PORTB |= (1 << PUSH_PIN_ROW_2);

    PORTB &= ~(1 << PUSH_PIN_COLUMN_2);
    PORTB &= ~(1 << PUSH_PIN_ROW_2);
  }
  //update the output
  PORTD |= (1 << CLOCK);
}

void lightDownWholeBottomMatrix(){
  //light down the clocks
  PORTD &= ~(1 << CLOCK);

  PORTB &= ~(1 << PUSH_PIN_COLUMN_2);
  PORTB &= ~(1 << PUSH_PIN_ROW_2);

  PORTB |= (1 << DATA_PIN_COLUMN_2);
  PORTB &= ~(1 << DATA_PIN_ROW_2);
  
  for (int i = 0; i < 8; i++)
  {
    //push LOW bits for columns, and HIGH bits for rows
    PORTB |= (1 << PUSH_PIN_COLUMN_2);
    PORTB |= (1 << PUSH_PIN_ROW_2);

    PORTB &= ~(1 << PUSH_PIN_COLUMN_2);
    PORTB &= ~(1 << PUSH_PIN_ROW_2);
  }
  //update the output
  PORTD |= (1 << CLOCK);
}

void setRow(int row){
  if (row < 1 || row > 16) return;
  if (row <= 8)
  {
    row = row-1;
    
    //light down the clocks
    PORTD &= ~_BV(CLOCK);

    PORTD &= ~_BV(PUSH_PIN_ROW_1);

    for (int i = 0; i < 8; i++)
    {
      if (row == i)
      {
        PORTD |= _BV(DATA_PIN_ROW_1);
      }
      else PORTD &= ~_BV(DATA_PIN_ROW_1);
      PORTD |= _BV(PUSH_PIN_ROW_1);
      PORTD &= ~_BV(PUSH_PIN_ROW_1);
    }
    PORTD |= _BV(CLOCK);
  }
  if (row > 8){
    row = row-1;
    
    //light down the clocks
    PORTD &= ~_BV(CLOCK);

    PORTB &= ~_BV(PUSH_PIN_ROW_2);

    for (int i = 0; i < 8; i++)
    {
      if (row == i)
      {
        PORTB |= _BV(DATA_PIN_ROW_2);
      }
      else PORTB &= ~_BV(DATA_PIN_ROW_2);
      PORTB |= _BV(PUSH_PIN_ROW_2);
      PORTB &= ~_BV(PUSH_PIN_ROW_2);
    }
    PORTD |= _BV(CLOCK);
  }
}

void setColumn(int col){
  if (col < 1 || col > 8) return;
  col = col-1;
  
  //light down the clocks
  PORTD &= ~_BV(CLOCK);

  PORTD &= ~_BV(PUSH_PIN_COLUMN_1);

  PORTD |= _BV(DATA_PIN_COLUMN_1
);

  for (int i = 0; i < 8; i++)
  {
    if (col == i)
    {
      PORTD &= ~_BV(DATA_PIN_COLUMN_1
    );
    }
    else PORTD |= _BV(DATA_PIN_COLUMN_1
  );
    PORTD |= _BV(PUSH_PIN_COLUMN_1);
    PORTD &= ~_BV(PUSH_PIN_COLUMN_1);
  }
  PORTD |= _BV(CLOCK);
}

void setMultipleColumns(uint8_t cols){
  //light down the clocks
  PORTD &= ~_BV(CLOCK);

  PORTD &= ~_BV(PUSH_PIN_COLUMN_1);

  PORTD |= _BV(DATA_PIN_COLUMN_1
);

  for (int i = 0; i < 8; i++)
  {
    if (cols & (1<<i))
    {
      PORTD &= ~_BV(DATA_PIN_COLUMN_1
    );
    }
    else PORTD |= _BV(DATA_PIN_COLUMN_1
  );
    PORTD |= _BV(PUSH_PIN_COLUMN_1);
    PORTD &= ~_BV(PUSH_PIN_COLUMN_1);
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

  DDRD |= (1 << DATA_PIN_COLUMN_1);
  DDRD |= (1 << DATA_PIN_ROW_1);
  DDRD |= (1 << CLOCK);
  DDRD |= (1 << CLOCK);
  DDRD |= (1 << PUSH_PIN_COLUMN_1);
  DDRD |= (1 << PUSH_PIN_ROW_1);

  DDRB |= (1 << DATA_PIN_ROW_2);
  DDRB |= (1 << CLOCK);
  DDRB |= (1 << CLOCK);
  DDRB |= (1 << PUSH_PIN_COLUMN_2);
  DDRB |= (1 << PUSH_PIN_ROW_2);

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

  PORTD &= ~(1 << PUSH_PIN_COLUMN_1);
  PORTD &= ~(1 << PUSH_PIN_ROW_1);
  PORTB &= ~(1 << PUSH_PIN_COLUMN_2);
  PORTB &= ~(1 << PUSH_PIN_ROW_2);

  lightDownWholeTopMatrix();
  lightDownWholeBottomMatrix();
  initUSART();
  while (1)
  {
    lightUpWholeTopMatrix();
    _delay_ms(500);
    lightUpWholeBottomMatrix();
    _delay_ms(500);
    lightDownWholeTopMatrix();
    _delay_ms(500);
    lightDownWholeBottomMatrix();
    _delay_ms(500);
  }
}