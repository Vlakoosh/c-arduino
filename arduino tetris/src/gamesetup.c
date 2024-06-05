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

uint8_t field[FIELD_HEIGHT * FIELD_WIDTH] = {0};


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

// initialize buzzer pin as output
void initBuzzer()
{
  DDRC |= _BV(BUZZER_PIN);
}

// make a quiet 3ms beep when called
void beep()
{
  if (ENABLE_SOUND)
  {
    PORTC |= _BV(BUZZER_PIN);
    _delay_ms(3);
    PORTC &= ~_BV(BUZZER_PIN);
  }
}

// quick triple beep
void tripleBeep()
{
  for (int i = 0; i < 3; i++)
  {
    beep();
    _delay_ms(100);
  }
}

void initButtonInterrupts()
{
  /*
  // PCICR -> register for enabling interrupts on PORT B, C, and D
  // PCIE0 -> PORT B
  // PCIE1 -> PORT C
  */

  PCICR |= _BV(PCIE0) | _BV(PCIE1);

  /*
  // PCMSK* -> register for enabling interrupts on specific pins on PORT B, C, and D
  // PCMSK0 -> PORT B
  // PCMSK1 -> PORT C
  */

  PCMSK0 |= _BV(BUTTON_LEFT) | _BV(BUTTON_RIGHT);
  PCMSK1 |= _BV(BUTTON_UP) | _BV(BUTTON_DOWN) | _BV(BUTTON_A) | _BV(BUTTON_B);
}

void initADC(void)
{
  /*
  !!! AI CONTENT WARNING !!!
  this function was written by me, but values of registers were picked by AI
  comments were written by me to clearly understand the code


  // ADMUX -> ADC Multiplexer Selection Register. configures the reference voltage and the input channel for the ADC.

  // AREF  -> Analog REFerence voltage - "top" voltage reference value for analog-digital-conversion
  // AVcc  -> operating voltage of microcontroler (5v)

  // AREF = AVcc
  */

  ADMUX = (1 << REFS0);

  /*
  // ADCSRA              -> ADC Control and Status Register A - sets prescaler and enables the ADC
  // ADEN = 1            -> enables the ADC
  // ADPS0, ADPS1, ADPS2 -> sets the prescales to 128 (predetermined value of the 3 bits)

  // ADC Enable and prescaler of 128
  // 16000000/128 = 125000
  */

  ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t readADC(uint8_t ch)
{
  /*
  !!! AI CONTENT WARNING !!!
  this function was written by me, but values of registers were picked by AI
  comments were written by me to clearly understand the code


  // ADMUX -> ADC Multiplexer Selection Register. configures the reference voltage and the input channel for the ADC.
  // three least significant bits represent the used channel in binary

  // Select ADC channel ch must be 0-7 (in binary last 3 bits)
  // 0xF8 -> 11111000 in binary, meaning last 3 bits of ADMUX will be set to 0 and replaced by value in "ch"
  */

  ch &= 0b00000111;
  ADMUX = (ADMUX & 0xF8) | ch;

  // Start single conversion
  ADCSRA |= (1 << ADSC);

  // Wait for conversion to complete
  while (ADCSRA & (1 << ADSC))
    ;

  return (ADC);
}

// return a random number between 0 and max (inclusive)
int getRandomNumber(int max)
{
  /*
  // get the random seed from pin A4 (channel 4) (binary .............100)
  // set the seed in random generator "rand"
  // rand generates a random integer. modulo it to get a range from 0 to modulo#
  */

  uint16_t seed = readADC(4);
  srand(seed);

  return rand() % (max + 1);
}

void initGameLoopTimer(void)
{
  /*
  !!! AI CONTENT WARNING !!!
  this function was written by me, but values of TCCR1B and OCR1A were picked by AI
  comments were written by me to clearly understand the code

  // CTC mode    -> Clear Timer on Compare mode
  // TCCR1B      -> Timer/Counter Control Register B (for Timer1)
  // WGM12 = 1   -> this bit sets timer 1 to CTC mode (counter = 0 when OCR1A triggers)

  // OCR1A       -> register holding the value to which the timer counts to
  // (F_CPU / 64 / 1000) - 1    ->    16,000,000 / 64 / 1000 - 1 = 249

  // TIMSK1      -> register for enabling timer 1 interrupts
  // OCIE1A = 1  -> bit to enable OCR1A compare interrupt

  */

  // Set CTC mode
  TCCR1B |= (1 << WGM12);

  // Set compare value for 1ms interval
  OCR1A = (F_CPU / 64 / 1000) - 1; //

  // Enable Output Compare A Match Interrupt (OCR1A)
  TIMSK1 |= (1 << OCIE1A);

  // Start timer with prescaler 64
  TCCR1B |= (1 << CS11) | (1 << CS10);
}