#include <stdlib.h>
#include <stdio.h>

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <usart.h>

#include <ledmatrixlib.h>
#include <gamesetup.h>

// this interval is the amount of time between tetris "updates" (piece moves down by 1 square)
uint16_t interval_ms = 350;
uint16_t count = 0;

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

int cr = 0;  // the current rotation of the piece. each unit represents 90 degrees
int cx = 2;  // the current x position of the moving tile
int cy = -3; // the current y position of the moving tile
int ci = 3;  // the index of the current selected tetris piece in the "pieces" array

int score = 0;
int tetrisCount = 0;
int pieceCount = 0;

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

// get the index of a tetromino pixel based on the rotation of the 16bit array
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

void deleteRowOfPixels(int row)
{
  for (int column = 0; column < FIELD_WIDTH; column++)
  {
    field[row * FIELD_WIDTH + column] = 0;
  }
}

void moveTilesDownAboveRow(int row)
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

// check if there are full rows
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
      tetrisCount++;
      score += 1000;
      deleteRowOfPixels(row);
      moveTilesDownAboveRow(row);
      goodBeep();
    }
  }
}

void newPiece()
{
  cx = 2;
  cy = -3;
  ci = getRandomNumber(6);
  pieceCount++;
  score += 100;
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

void printScore()
{
  printf("\n\nYou lose!\n");
  printf("Your final score is: %d", score);
  printf("\ntotal rows completed: %d", tetrisCount);
  printf("\ntotal pieces placed: %d", pieceCount);
}

void lose()
{
  badBeep();
  printScore();
  while (1)
  {
    // stop any code execution. Just display the field
    displayScreenArray(field, FIELD_WIDTH, FIELD_HEIGHT);
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
    int mxfi = cy * FIELD_WIDTH + FIELD_WIDTH + ty * FIELD_WIDTH - 1;
    int mnfi = cy * FIELD_WIDTH + ty * FIELD_WIDTH;

    if ((fi > 0 && pixel && field[fi]) || (fi > (FIELD_HEIGHT * FIELD_WIDTH) && pixel) || ((fi > mxfi || fi < mnfi) && pixel))
    {
      cx -= x;
      cy -= y;
      cr -= r;

      placePiece();

      if (y > 0)
      {
        if (cy < -1)
        {
          lose();
        }
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

void playTetris()
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