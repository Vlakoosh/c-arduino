#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

// set pins for breadboard buttons
#define BUTTON_UP PC1
#define BUTTON_DOWN PC0
#define BUTTON_LEFT PB4
#define BUTTON_RIGHT PB5
#define BUTTON_A PC3
#define BUTTON_B PC2

// miscellanous pins
#define BUZZER_PIN PC5
#define RANDOM_SEED_ANALOG_PIN PC4

// time in ms for debouncing buttons
#define DEBOUNCE_TIME 10

// game properties
#define FIELD_WIDTH 8
#define FIELD_HEIGHT 16

// setting this to 1 enables beeps and 0 turns them off
#define ENABLE_SOUND 1

//arrays
extern uint8_t field[FIELD_HEIGHT * FIELD_WIDTH];

// button inputs
void initButton();
void initButtonInterrupts();

// ADC / random numbers
void initADC(void);
int getRandomNumber(int max);
uint16_t readADC(uint8_t ch);

// sound / buzzer
void initBuzzer();
void tripleBeep();
void goodBeep();
void badBeep();
void beep();