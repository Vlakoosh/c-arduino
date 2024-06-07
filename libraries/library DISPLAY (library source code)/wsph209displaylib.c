#include "wsph209displaylib.h"

#include <avr/io.h>
#include <util/delay.h>

/* Segment byte maps for numbers 0 to 9 */
const uint8_t SEGMENT_MAP[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99,
                               0x92, 0x82, 0xF8, 0X80, 0X90};

/* Byte maps to select digit 1 to 4 */
const uint8_t SEGMENT_SELECT[] = {0xF1, 0xF2, 0xF4, 0xF8};

void initDisplay() {
  sbi(DDRD, LATCH_DIO);
  sbi(DDRD, CLK_DIO);
  sbi(DDRB, DATA_DIO);
}

// loop through seven segments of LED display and shift the correct bits in the
// data register
void shift(uint8_t val, uint8_t bitorder) {
  uint8_t bit;

  for (uint8_t i = 0; i < NUMBER_OF_SEGMENTS; i++) {
    if (bitorder == LSBFIRST) {
      bit = !!(val & (1 << i));
    } else {
      bit = !!(val & (1 << (7 - i)));
    }
    // write bit to register
    if (bit == HIGH)
      sbi(PORTB, DATA_DIO);
    else
      cbi(PORTB, DATA_DIO);

    // Trigger the clock pin so the display updates
    sbi(PORTD, CLK_DIO);
    cbi(PORTD, CLK_DIO);
  }
}

//Writes a digit to a certain segment. Segment 0 is the leftmost.
void writeNumberToSegment(uint8_t segment, uint8_t value) {
  cbi(PORTD, LATCH_DIO);
  shift(SEGMENT_MAP[value], MSBFIRST);
  shift(SEGMENT_SELECT[segment], MSBFIRST);
  sbi(PORTD, LATCH_DIO);
}

//Writes a nuber between 0 and 9999 to the display. To be used in a loop...
void writeNumber(int number) {
  if (number < 0 || number > 9999) return;
  writeNumberToSegment(0, number / 1000);
  writeNumberToSegment(1, (number / 100) % 10);
  writeNumberToSegment(2, (number / 10) % 10);
  writeNumberToSegment(3, number % 10);
}

//Writes a number between 0 and 9999 to the display and makes sure that it stays there a certain number of millisecs.
//Note: the timing is approximate; the amount of time writeNumberToSegment takes is not accounted for...
void writeNumberAndWait(int number, int delay) {
  if (number < 0 || number > 9999) return;
  for (int i = 0; i < delay / 20; i++) {
    writeNumberToSegment(0, number / 1000);
    _delay_ms(5);
    writeNumberToSegment(1, (number / 100) % 10);
    _delay_ms(5);
    writeNumberToSegment(2, (number / 10) % 10);
    _delay_ms(5);
    writeNumberToSegment(3, number % 10);
    _delay_ms(5);
  }
}

const uint8_t ALPHABET_MAP[] = {0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E, 0xC2,
                                0x89, 0xCF, 0xE1, 0x8A, 0xC7, 0xEA, 0xC8,
                                0xC0, 0x8C, 0x4A, 0xCC, 0x92, 0x87, 0xC1,
                                0xC1, 0xD5, 0x89, 0x91, 0xA4, 0xFF};

void writeCharToSegment(uint8_t segment, char character){
int valueOfCharacter=0xFF;
  if((int)character>=65 && (int)character<=90){
      valueOfCharacter = ((int)character-65);   
  }else if ((int)character>=97 &&(int)character<=122){
     valueOfCharacter = ((int)character-97);
    
  }else {
    valueOfCharacter=26;
  }
  cbi(PORTD, LATCH_DIO);
  shift(ALPHABET_MAP[valueOfCharacter], MSBFIRST);
  shift(SEGMENT_SELECT[segment], MSBFIRST);
  sbi(PORTD, LATCH_DIO);
};

void writeString(char* str){
  writeCharToSegment(0,str[0]);
  writeCharToSegment(1,str[1]);
  writeCharToSegment(2,str[2]);
  writeCharToSegment(3,str[3]);
}

void blankSegment(uint8_t segment)
{
  cbi(PORTD, LATCH_DIO);
  shift(0xFF, MSBFIRST);
  shift(SEGMENT_SELECT[segment], MSBFIRST);
  sbi(PORTD, LATCH_DIO);
}

void clearDisplay() {
  blankSegment(0);
  blankSegment(1);
  blankSegment(2);
  blankSegment(3);
}

void displayArray(int array[]){
  if (array[0]<0)
  {
    if (array[0]==-1)
    {
      writeCharToSegment(0,'T');
    }else if (array[0]==-2)
    {
      writeCharToSegment(0,'H');
    }
    
  }else{  
  writeNumberToSegment(0,array[0]);
  }
  if (array[0]<0)
  {
    blankSegment(1);
    
  }else{  
  writeDotNumberToSegment(1,array[1]);
  }
  writeNumberToSegment(2,array[2]);
  writeNumberToSegment(3,array[3]);
  blankSegment(3);
}

void writeDotNumberToSegment(uint8_t segment, uint8_t value)
{
int dotValue = SEGMENT_MAP[value] - 0x80;
  cbi(PORTD, LATCH_DIO);
  shift(dotValue, MSBFIRST);
  shift(SEGMENT_SELECT[segment], MSBFIRST);
  sbi(PORTD, LATCH_DIO);
}

void writeDotToSegment(uint8_t segment)
{
  cbi(PORTD, LATCH_DIO);
  shift(0x7F, MSBFIRST);
  shift(SEGMENT_SELECT[segment], MSBFIRST);
  sbi(PORTD, LATCH_DIO);
}