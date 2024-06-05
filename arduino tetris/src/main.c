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
#define RANDOM_SEED_ANALOG_PIN PC4

#define DEBOUNCE_TIME 10

// game properties
#define FIELD_WIDTH 8
#define FIELD_HEIGHT 16
#define ENABLE_SOUND 1

uint16_t interval_ms = 350;
uint16_t count = 0;

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

void initBuzzer()
{
  DDRC |= _BV(BUZZER_PIN);
}

void beep()
{
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

void initADC(void)
{
  // AREF = AVcc
  ADMUX = (1 << REFS0);

  // ADC Enable and prescaler of 128
  // 16000000/128 = 125000
  ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t readADC(uint8_t ch)
{
  // Select ADC channel ch must be 0-7
  ch &= 0b00000111;
  ADMUX = (ADMUX & 0xF8) | ch;

  // Start single conversion
  ADCSRA |= (1 << ADSC);

  // Wait for conversion to complete
  while (ADCSRA & (1 << ADSC))
    ;

  return (ADC);
}

int getRandomNumber(int max)
{
  // get the random seed from pin A4 (channel 4)
  uint16_t seed = readADC(4);
  srand(seed);

  return rand() % (max + 1);
}

void set_timer1_interval(uint16_t interval)
{
  interval_ms = interval;

  // Calculate the compare value based on the interval
  // OCR1A = (F_CPU / (prescaler * 1000)) * interval - 1
  OCR1A = (F_CPU / 64 / 1000) * interval_ms * 2 - 1;
}

void initGameLoopTimer(void)
{
  // Set CTC mode
  TCCR1B |= (1 << WGM12);
  
  // Set compare value for 1ms interval
  OCR1A = (F_CPU / 64 / 1000) - 1; // 16,000,000 / 64 / 1000 - 1 = 249
  
  // Enable Output Compare A Match Interrupt
  TIMSK1 |= (1 << OCIE1A);
  
  // Start timer with prescaler 64
  TCCR1B |= (1 << CS11) | (1 << CS10);
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
int cy = -3; // the current y position of the moving tile
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

  // preload all tetris pieces into the TETROMINOS struct
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

int getRotatedIndex(int px, int py, int rotation)
{
  switch (rotation % 4)
  {
  case 0:
    return py * 4 + px; // 0 degrees
  case 1:
    return 12 + py - (px * 4); // 90 degrees
  case 2:
    return 15 - (py * 4) - px; // 180 degrees
  case 3:
    return 3 - py + (px * 4); // 270 degrees
  }
  return 0;
}

void deleteRow(int row)
{
  for (int column = 0; column < FIELD_WIDTH; column++)
  {
    field[row * FIELD_WIDTH + column] = 0;
  }
}

void movePiecesDown(int row)
{
  for (int y = row; y > 0; y--)
  {
    for (int x = 0; x < FIELD_WIDTH; x++)
    {
      int index = y * FIELD_WIDTH + x;
      int nextIndex = index - FIELD_WIDTH;
      field[index] = field[nextIndex];
    }
  }
}

void beepTetris() {
  for (int i = 0; i < 3; i++)
  {
    beep();
    _delay_ms(100);
  }
}

void checkTetris()
{
  for (int row = 0; row < FIELD_HEIGHT; row++)
  {
    int tetris = 1;
    for (int column = 0; column < FIELD_WIDTH; column++)
    {
      if (field[row * FIELD_WIDTH + column] == 0)
      {
        tetris = 0;
        break;
      }
    }
    if (tetris)
    {
      deleteRow(row);
      movePiecesDown(row);
      beepTetris();
    }
  }
}

void newPiece()
{
  cx = 2;
  cy = -3;
  ci = getRandomNumber(6);
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

    int pixel = (pieces->all[ci].bits & (1 << (15 - tpi))) ? 1 : 0;

    int fi = cx + tx + cy * FIELD_WIDTH + ty * FIELD_WIDTH;

    // if the pixel is on the game field and is set to 1, push it to the game field
    if (fi > 0 && field[fi] && pixel)
      field[fi] = 0;
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

    int pixel = (pieces->all[ci].bits & (1 << (15 - tpi))) ? 1 : 0;

    int fi = cx + tx + cy * FIELD_WIDTH + ty * FIELD_WIDTH;

    // if the pixel is on the game field and is set to 1, push it to the game field
    if (fi > 0 && pixel)
      field[fi] = pixel;
  }
}

// make sure that rotation doesn't go negative while changing its value
void addRotationWithClamp(int r)
{
  cr += r;
  while (cr < 0)
  {
    cr = 4 + cr;
  }
}

void putTile(int x, int y, int r)
{
  clearPiece();
  cx += x;
  cy += y;
  addRotationWithClamp(r);

  // scan
  for (int i = 0; i <= 15; i++)
  {
    // tx, ty   = "tile x" and "tile y" (on tile 4x4 grid)
    // tpi      = "tile pixel index"
    // pixel    = pixel value at this index of the selected tile
    // fi       = "field index" (position of the pixel on the game field)
    // mxfi     = "max field index" (maximum position of pixel)
    // mnfi     = "min field index" (minimum position of pixel)

    int tx = i % 4;
    int ty = i / 4;
    int tpi = getRotatedIndex(tx, ty, cr);

    int pixel = (pieces->all[ci].bits & (1 << (15 - tpi))) ? 1 : 0;

    int fi = cx + tx + cy * FIELD_WIDTH + ty * FIELD_WIDTH;
    int mxfi = cy*FIELD_WIDTH + FIELD_WIDTH + ty*FIELD_WIDTH - 1;
    int mnfi = cy*FIELD_WIDTH + ty*FIELD_WIDTH;

    if ((fi > 0 && pixel && field[fi]) || (fi > (FIELD_HEIGHT * FIELD_WIDTH) && pixel) || ((fi > mxfi || fi < mnfi) && pixel) )
    {
      cx -= x;
      cy -= y;
      cr -= r;

      placePiece();
      
      if (y > 0)
      {
        newPiece();
        checkTetris();
      }
      return;
    }
  }

  placePiece();
}

void timerUpdate()
{
  putTile(0, 1, 0);
}

void movePiece(int x, int y)
{
  beep();
  putTile(x, y, 0);
}

void rotatePiece(int rotation)
{
  beep();
  putTile(0, 0, rotation);
}

void updatePiece()
{
  putTile(0, 1, 0);
}

// interrupt for buttons connected to PORTB
ISR(PCINT0_vect)
{

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

// Interrupt Service Routine for Timer1 Compare Match A
ISR(TIMER1_COMPA_vect)
{
  count++;
  if (count >= interval_ms)
  {
    updatePiece();
    count = 0;
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

  initADC();

  // enable timer 1 interrupts and game loop
  initGameLoopTimer();

  // enable global interrupts
  sei();

  // initialize the "pieces" array with values of tetrominos (tetris pieces)
  makeTetrominos();

  // printArray(field, FIELD_WIDTH * FIELD_HEIGHT);

  while (1)
  {
    displayScreenArray(field, FIELD_WIDTH, FIELD_HEIGHT);
  }
}