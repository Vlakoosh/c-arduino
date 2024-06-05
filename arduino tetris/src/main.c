//avr programming and arduino C libraries
#include <avr/io.h>
#include <util/delay.h>
#include <usart.h>
#include <avr/interrupt.h>
//libraries made by me
#include <ledmatrixlib.h>
//libraries made for C
#include <stdlib.h>
#include <stdio.h>

//set pins for breadboard buttons
#define BUTTON_UP PC1
#define BUTTON_DOWN PC0
#define BUTTON_LEFT PB4
#define BUTTON_RIGHT PB5
#define BUTTON_A PC3
#define BUTTON_B PC2

#define DEBOUNCE_TIME 50

//game properties
#define FIELD_WIDTH 8
#define FIELD_HEIGHT 16

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

//game logic starts here: 

typedef struct {
  uint16_t bits;
} TETROMINO;

typedef struct {
  TETROMINO all[7];
} TETROMINOS;

//global variables:

int rotation = 0;
int currentX = 0;
int currentY = 0;

uint8_t field[FIELD_HEIGHT * FIELD_WIDTH] = {0}; 

TETROMINOS* pieces;

void makeTetrominos() {
  //allocate memory for tetrominos
  pieces = (TETROMINOS*) malloc(sizeof(TETROMINOS));

  //check if malloc worked, throw error in console if it didn't
  if (pieces == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
  }

  pieces->all[0].bits = 0b0010001000100010;
  pieces->all[1].bits = 0b0010011001000000;
  pieces->all[2].bits = 0b0100011000100000;
  pieces->all[3].bits = 0b0000011001100000;
  pieces->all[4].bits = 0b0010011000100000;
  pieces->all[5].bits = 0b0000011000100010;
  pieces->all[6].bits = 0b0000011001000100;
}

//fun debug method
void printPiece(uint16_t p) {
  printf("\n");
  for (int i = 15; i >= 0; i--)
  {
    printf("%c", (p & (1 << i)) ? '@' : ' ');
    if (i % 4 == 0)
    {
      printf("\n");
    }
  }
}


void clearPiece() {

}

void placePiece(){

}

void putTile(int x, int y, int rotation){

}

void timerUpdate() {
  putTile(0, 1, 0);
}

void movePiece(int x, int y) {
  putTile(x, y, 0);
}

void rotatePiece(int rotation) {
  putTile(0, 0, rotation);
}

//interrupt for buttons connected to PORTB
ISR( PCINT0_vect ){
  _delay_ms(DEBOUNCE_TIME);

  if (bit_is_clear(PINB, BUTTON_LEFT))
  {
    printf("button LEFT pressed\n");
    movePiece(-1,0);
  }
  if (bit_is_clear(PINB, BUTTON_RIGHT))
  {
    printf("button RIGHT pressed\n");
    movePiece(1,0);
  }
}

//interrupt for buttons connected to PORTC
ISR( PCINT1_vect ){
  _delay_ms(DEBOUNCE_TIME);

  if (bit_is_clear(PINC, BUTTON_UP))
  {
    printf("button UP pressed\n");
    //nothing happens when button UP is pressed
  }
  if (bit_is_clear(PINC, BUTTON_DOWN))
  {
    printf("button DOWN pressed\n");
    movePiece(0,1);
  }
  if (bit_is_clear(PINC, BUTTON_A))
  {
    printf("button A pressed\n");
    rotatePiece(-1);
  }
  if (bit_is_clear(PINC, BUTTON_B))
  {
    printf("button B pressed\n");
    rotatePiece(1);
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

  makeTetrominos();

  printPiece(pieces->all[0].bits);
  printPiece(pieces->all[1].bits);
  printPiece(pieces->all[2].bits);
  printPiece(pieces->all[3].bits);
  printPiece(pieces->all[4].bits);
  printPiece(pieces->all[5].bits);
  printPiece(pieces->all[6].bits);

  //enable global interrupts
  sei();

  field[0] = (uint8_t) 1;

  field[1] = (uint8_t) 1;
  field[88] = (uint8_t) 1;

  printArray(field, FIELD_WIDTH * FIELD_HEIGHT);

  while (1)
  {
    displayScreenArray(field, FIELD_WIDTH, FIELD_HEIGHT);
  }
  
}