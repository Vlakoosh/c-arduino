#include <stdlib.h>
#include <stdio.h>

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <usart.h>

#include <ledmatrixlib.h>
#include <gamesetup.h>

extern uint16_t interval_ms;
extern uint16_t count;

// global variables:

extern int cr;  // the current rotation of the piece. each unit represents 90 degrees
extern int cx;  // the current x position of the moving tile
extern int cy; // the current y position of the moving tile
extern int ci;  // the index of the current selected tetris piece in the "pieces" array

//structs
typedef struct
{
  uint16_t bits;
} TETROMINO;

typedef struct
{
  TETROMINO all[7];
} TETROMINOS;

//dynamic memory allocation
TETROMINOS *pieces;

// timer
void initGameLoopTimer(void);

//game logic
void makeTetrominos();
int getRotatedIndex(int px, int py, int rotation);

void moveTilesDownAboveRow(int row);
void deleteRowOfPixels(int row);
void checkTetris();

void addRotationWithClamp(int r);
void putTile(int x, int y, int r);
void timerUpdate();

void newPiece();
void clearPiece();
void placePiece();

void movePiece(int x, int y);
void rotatePiece(int rotation);
void updatePiece();

void playTetris();