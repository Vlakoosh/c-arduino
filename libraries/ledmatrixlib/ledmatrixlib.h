#include <avr/io.h>
#include <util/delay.h>

//set pins for top LED matrix
#define DATA_PIN_ROW_1 PD6
#define PUSH_PIN_ROW_1 PD7
#define DATA_PIN_COLUMN_1 PD4
#define PUSH_PIN_COLUMN_1 PD5

//set pins for bottom LED matrix
#define DATA_PIN_ROW_2 PB0
#define PUSH_PIN_ROW_2 PB1
#define DATA_PIN_COLUMN_2 PB2
#define PUSH_PIN_COLUMN_2 PB3

//set pin for the shared update clock signal
#define CLOCK PD2

//set pins for breadboard buttons
#define BUTTON_LEFT PB4
#define BUTTON_RIGHT PB5
#define BUTTON_UP PC0
#define BUTTON_DOWN PC1
#define BUTTON_A PC2
#define BUTTON_B PC3

//initialize all the pins for the library
void init();

//turn on all LEDs on the top half of the "screen"
void lightUpWholeTopMatrix();

//turn off all LEDs on the top half of the "screen"
void lightDownWholeTopMatrix();

//turn on all LEDs on the bottom half of the "screen"
void lightUpWholeBottomMatrix();

//turn off all LEDs on the bottom half of the "screen"
void lightDownWholeBottomMatrix();

//turn on all LEDs
void lightUpWholeMatrix();

//turn off all LEDs
void lightDownWholeMatrix();

//enable a specific row on the top matrix by setting its bit to HIGH and the other bits to LOW
void setRowOnTopMatrix(int row);

//enable a specific column on the top matrix by setting its bit to to LOW and the other bits to HIGH
void setColumnOnTopMatrix(int col);

//enable multiple columns at once on the top matrix by setting their bits to LOW and the other bits to HIGH
void setMultipleColumnsOnTopMatrix(uint8_t cols);

//enable a specific row on the bottom matrix by setting its bit to HIGH and the other bits to LOW
void setRowOnBottomMatrix(int row);

//enable a specific column on the bottom matrix by setting its bit to to LOW and the other bits to HIGH
void setColumnOnBottomMatrix(int col);

//enable multiple columns at once on the top matrix by setting their bits to LOW and the other bits to HIGH
void setMultipleColumnsOnBottomMatrix(uint8_t cols);

//enable ONE specific row and ONE or MORE columns at once. The method picks automatically between the top and bottom matrix
void displayRow(int row, uint8_t columns);