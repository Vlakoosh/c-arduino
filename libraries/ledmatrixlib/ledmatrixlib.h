#include <avr/io.h>

// initialize all the pins for the library
void initMatrix();

// turn on all LEDs on the top half of the "screen"
void lightUpWholeTopMatrix();

// turn off all LEDs on the top half of the "screen"
void lightDownWholeTopMatrix();

// turn on all LEDs on the bottom half of the "screen"
void lightUpWholeBottomMatrix();

// turn off all LEDs on the bottom half of the "screen"
void lightDownWholeBottomMatrix();

// turn on all LEDs
void lightUpWholeMatrix();

// turn off all LEDs
void lightDownWholeMatrix();

// enable a specific row on the top matrix by setting its bit to HIGH and the other bits to LOW
void setRowOnTopMatrix(int row);

// enable a specific column on the top matrix by setting its bit to to LOW and the other bits to HIGH
void setColumnOnTopMatrix(int col);

// enable multiple columns at once on the top matrix by setting their bits to LOW and the other bits to HIGH
void setMultipleColumnsOnTopMatrix(uint8_t cols);

// enable a specific row on the bottom matrix by setting its bit to HIGH and the other bits to LOW
void setRowOnBottomMatrix(int row);

// enable a specific column on the bottom matrix by setting its bit to to LOW and the other bits to HIGH
void setColumnOnBottomMatrix(int col);

// enable multiple columns at once on the top matrix by setting their bits to LOW and the other bits to HIGH
void setMultipleColumnsOnBottomMatrix(uint8_t cols);

// enable ONE specific row and ONE or MORE columns at once. The method picks automatically between the top and bottom matrix
void displayRow(int row, uint8_t columns);

// hello world program for testing if the display is wired up correctly with the shift registers
void testDisplay();

// function to display an array of pixels on the matrix
void displayScreenArray(uint8_t *screenArray, int width, int height);