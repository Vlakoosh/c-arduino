// avr programming and arduino C libraries
#include <avr/io.h>
#include <util/delay.h>
#include <usart.h>
#include <avr/interrupt.h>
// libraries made by me
#include <ledmatrixlib.h>
// libraries made for C
#include <stdlib.h>
#include <stdio.h>

// set pins for breadboard buttons
#define BUTTON_UP PC1
#define BUTTON_DOWN PC0
#define BUTTON_LEFT PB4
#define BUTTON_RIGHT PB5
#define BUTTON_A PC3
#define BUTTON_B PC2

#define BUZZER_PIN PC5

#define DEBOUNCE_TIME 100

// game properties
#define FIELD_WIDTH 8
#define FIELD_HEIGHT 16
#define ENABLE_SOUND 1

// initialize button pins and their registers with correct values
void initButton()
{
  // enable button pins as input
  DDRC &= ~_BV(BUTTON_UP);
  DDRC &= ~_BV(BUTTON_DOWN);
  DDRB &= ~_BV(BUTTON_LEFT);
  DDRB &= ~_BV(BUTTON_RIGHT);

  DDRC &= ~_BV(BUTTON_A);
  DDRC &= ~_BV(BUTTON_B);

  // set up pull-up resistors for button pins
  PORTC |= _BV(BUTTON_UP);
  PORTC |= _BV(BUTTON_DOWN);
  PORTB |= _BV(BUTTON_LEFT);
  PORTB |= _BV(BUTTON_RIGHT);

  PORTC |= _BV(BUTTON_A);
  PORTC |= _BV(BUTTON_B);
}

void initBuzzer() {
  DDRC |= _BV(BUZZER_PIN);
}

void beep(){
  if (ENABLE_SOUND)
  {
    PORTC |= _BV(BUZZER_PIN);
    _delay_ms(3);
    PORTC &= ~_BV(BUZZER_PIN);
  }
}

void initButtonInterrupts()
{
  PCICR |= _BV(PCIE0);
  PCICR |= _BV(PCIE1);
  PCMSK0 |= _BV(BUTTON_LEFT);
  PCMSK0 |= _BV(BUTTON_RIGHT);
  PCMSK1 |= _BV(BUTTON_UP);
  PCMSK1 |= _BV(BUTTON_DOWN);
  PCMSK1 |= _BV(BUTTON_A);
  PCMSK1 |= _BV(BUTTON_B);
}

// game logic starts here:

typedef struct
{
  uint16_t bits;
} TETROMINO;

typedef struct
{
  TETROMINO all[7];
} TETROMINOS;

// global variables:

int cr = 0; // the current rotation of the piece. each unit represents 90 degrees
int cx = 2; // the current x position of the moving tile
int cy = 4; // the current y position of the moving tile
int ci = 3; // the index of the current selected tetris piece in the "pieces" array

uint8_t field[FIELD_HEIGHT * FIELD_WIDTH] = {0};

TETROMINOS *pieces;

void makeTetrominos()
{
  // allocate memory for tetrominos
  pieces = (TETROMINOS *)malloc(sizeof(TETROMINOS));

  // check if malloc worked, throw error in console if it didn't
  if (pieces == NULL)
  {
    fprintf(stderr, "Memory allocation failed\n");
  }

  //preload all tetris pieces into the TETROMINOS struct
  pieces->all[0].bits = 0b0010001000100010;
  pieces->all[1].bits = 0b0010011001000000;
  pieces->all[2].bits = 0b0100011000100000;
  pieces->all[3].bits = 0b0000011001100000;
  pieces->all[4].bits = 0b0010011000100000;
  pieces->all[5].bits = 0b0000011000100010;
  pieces->all[6].bits = 0b0000011001000100;
}

// fun debug method
void printPiece(uint16_t p)
{
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

int getRotatedIndex(int px, int py, int rotation){
  switch (rotation % 4){
        case 0: return py * 4 + px;         //0 degrees
        case 1: return 12 + py - (px * 4);  //90 degrees
        case 2: return 15 - (py * 4) - px;  //180 degrees
        case 3: return 3 - py + (px * 4);   //270 degrees
    }
    return 0;
}

void clearPiece()
{
  for (int i = 0; i <= 15; i++)
  {
    // tx, ty   = "tile x" and "tile y" (on tile 4x4 grid)
    // tpi      = "tile pixel index"
    // pixel    = pixel value at this index of the selected tile
    // fi       = "field index" (position of the pixel on the game field)

    int tx = i % 4; 
    int ty = i / 4; 
    int tpi = getRotatedIndex(tx, ty, cr);

    int pixel = (pieces->all[ci].bits & (1 << (15-tpi))) ? 1 : 0;

    int fi = cx + tx + cy * FIELD_WIDTH + ty * FIELD_WIDTH;

    // if the pixel is on the game field and is set to 1, push it to the game field
    if (fi > 0 && field[fi]) field[fi] = 0;    
  }
}

void placePiece()
{
  for (int i = 0; i <= 15; i++)
  {
    // tx, ty   = "tile x" and "tile y" (on tile 4x4 grid)
    // tpi      = "tile pixel index"
    // pixel    = pixel value at this index of the selected tile
    // fi       = "field index" (position of the pixel on the game field)

    int tx = i % 4; 
    int ty = i / 4; 
    int tpi = getRotatedIndex(tx, ty, cr);

    int pixel = (pieces->all[ci].bits & (1 << (15-tpi))) ? 1 : 0;

    int fi = cx + tx + cy * FIELD_WIDTH + ty * FIELD_WIDTH;

    // if the pixel is on the game field and is set to 1, push it to the game field
    if (fi > 0 && pixel) field[fi] = pixel;    
  }
}

void putTile(int x, int y, int rotation)
{
  beep();
}

void timerUpdate()
{
  putTile(0, 1, 0);
}

void movePiece(int x, int y)
{
  putTile(x, y, 0);
}

void rotatePiece(int rotation)
{
  putTile(0, 0, rotation);
}

// interrupt for buttons connected to PORTB
ISR(PCINT0_vect)
{
  _delay_ms(DEBOUNCE_TIME);
  
  if (bit_is_clear(PINB, BUTTON_LEFT))
  {
    _delay_ms(DEBOUNCE_TIME);
    if (bit_is_clear(PINB, BUTTON_LEFT))
    {
      movePiece(-1, 0);
    }
  }
  if (bit_is_clear(PINB, BUTTON_RIGHT))
  {
    _delay_ms(DEBOUNCE_TIME);
    if (bit_is_clear(PINB, BUTTON_RIGHT))
    {
      movePiece(1, 0);
    }
  }
}

// interrupt for buttons connected to PORTC
ISR(PCINT1_vect)
{
  // I really wanted to avoid it, but I have to use double if statement to debounce
  // If I don't do that, the screen will flicker also every time the button is released, making game unpleasant to play

  if (bit_is_clear(PINC, BUTTON_UP))
  {
    // nothing happens when button UP is pressed
    _delay_ms(DEBOUNCE_TIME);
    if (bit_is_clear(PINC, BUTTON_UP))
    {

    }
  }
  if (bit_is_clear(PINC, BUTTON_DOWN))
  {
    _delay_ms(DEBOUNCE_TIME);
    if (bit_is_clear(PINC, BUTTON_DOWN))
    {
      movePiece(0, 1);
    }
  }
  if (bit_is_clear(PINC, BUTTON_A))
  {
    _delay_ms(DEBOUNCE_TIME);
    if (bit_is_clear(PINC, BUTTON_A))
    {
      rotatePiece(-1);
    }
  }
  if (bit_is_clear(PINC, BUTTON_B))
  {
    _delay_ms(DEBOUNCE_TIME);
    if (bit_is_clear(PINC, BUTTON_B))
    {
      rotatePiece(1);
    }
  }
}

int main()
{
  // enable button pins
  initButton();
  // enable Matrix pins
  initMatrix();
  // enable buzzer
  initBuzzer();
  // enable serial communication
  initUSART();

  // set button interrupt registers
  initButtonInterrupts();

  // enable global interrupts
  sei();

  makeTetrominos();

  

  // printArray(field, FIELD_WIDTH * FIELD_HEIGHT);

  while (1)
  {
    placePiece();
    for (int i = 0; i < 100; i++)
    {
      displayScreenArray(field, FIELD_WIDTH, FIELD_HEIGHT);
    }
    clearPiece();
    for (int i = 0; i < 100; i++)
    {
      displayScreenArray(field, FIELD_WIDTH, FIELD_HEIGHT);
    }
    
  }
}