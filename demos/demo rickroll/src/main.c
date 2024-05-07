#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>

//All notes and music logic comes from https://github.com/robsoncouto/arduino-songs/blob/master/nevergonnagiveyouup/nevergonnagiveyouup.ino
//I added the buzzer logic for C and the Multi-Functional Shield

#define B0  31
#define C1  33
#define CS1 35
#define D1  37
#define DS1 39
#define E1  41
#define F1  44
#define FS1 46
#define G1  49
#define GS1 52
#define A1  55
#define AS1 58
#define B1  62
#define C2  65
#define CS2 69
#define D2  73
#define DS2 78
#define E2  82
#define F2  87
#define FS2 93
#define G2  98
#define GS2 104
#define A2  110
#define AS2 117
#define B2  123
#define C3  131
#define CS3 139
#define D3  147
#define DS3 156
#define E3  165
#define F3  175
#define FS3 185
#define G3  196
#define GS3 208
#define A3  220
#define AS3 233
#define B3  247
#define C4  262
#define CS4 277
#define D4  294
#define DS4 311
#define E4  330
#define F4  349
#define FS4 370
#define G4  392
#define GS4 415
#define A4  440
#define AS4 466
#define B4  494
#define C5  523
#define CS5 554
#define D5  587
#define DS5 622
#define E5  659
#define F5  698
#define FS5 740
#define G5  784
#define GS5 831
#define A5  880
#define AS5 932
#define B5  988
#define C6  1047
#define CS6 1109
#define D6  1175
#define DS6 1245
#define E6  1319
#define F6  1397
#define FS6 1480
#define G6  1568
#define GS6 1661
#define A6  1760
#define AS6 1865
#define B6  1976
#define C7  2093
#define CS7 2217
#define D7  2349
#define DS7 2489
#define E7  2637
#define F7  2794
#define FS7 2960
#define G7  3136
#define GS7 3322
#define A7  3520
#define AS7 3729
#define B7  3951
#define C8  4186
#define CS8 4435
#define D8  4699
#define DS8 4978
#define REST    0

void enableBuzzer()
{
   DDRD |= ( 1 << PD3 ); //Buzzer is connected to PD3
}

void playTone( float frequency, uint32_t duration )
{
   uint32_t periodInMicro = ( uint32_t ) ( 1000000 / frequency ); //Calculate the period in microsecs from the freq
   uint32_t durationInMicro = duration * 1000; //We express duration in microsecs
   for ( uint32_t time = 0; time < durationInMicro; time += periodInMicro ) //See tutorial on Music for more info!
    {
    PORTD &= ~( 1 << PD3 ); //turn the buzzer on
    _delay_us( periodInMicro / 2 ); //Wait for the half of the period
    PORTD |= ( 1 << PD3 ); //Turn the buzzer off
    _delay_us( periodInMicro / 2 ); //Wait again for half of the period
    }
}

void noTone(){
  PORTD |= ( 1 << PD3 );
}

// change this to whichever pin you want to use
int buzzer = 11;

// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melody[] = {

  // Never Gonna Give You Up - Rick Astley
  // Score available at https://musescore.com/chlorondria_5/never-gonna-give-you-up_alto-sax
  // Arranged by Chlorondria

  D5,-4, E5,-4, A4,4, //1
  E5,-4, FS5,-4, A5,16, G5,16, FS5,8,
  D5,-4, E5,-4, A4,2,
  A4,16, A4,16, B4,16, D5,8, D5,16,
  D5,-4, E5,-4, A4,4, //repeat from 1
  E5,-4, FS5,-4, A5,16, G5,16, FS5,8,
  D5,-4, E5,-4, A4,2,
  A4,16, A4,16, B4,16, D5,8, D5,16,
  REST,4, B4,8, CS5,8, D5,8, D5,8, E5,8, CS5,-8,
  B4,16, A4,2, REST,4, 

  REST,8, B4,8, B4,8, CS5,8, D5,8, B4,4, A4,8, //7
  A5,8, REST,8, A5,8, E5,-4, REST,4, 
  B4,8, B4,8, CS5,8, D5,8, B4,8, D5,8, E5,8, REST,8,
  REST,8, CS5,8, B4,8, A4,-4, REST,4,
  REST,8, B4,8, B4,8, CS5,8, D5,8, B4,8, A4,4,
  E5,8, E5,8, E5,8, FS5,8, E5,4, REST,4,
   
  D5,2, E5,8, FS5,8, D5,8, //13
  E5,8, E5,8, E5,8, FS5,8, E5,4, A4,4,
  REST,2, B4,8, CS5,8, D5,8, B4,8,
  REST,8, E5,8, FS5,8, E5,-4, A4,16, B4,16, D5,16, B4,16,
  FS5,-8, FS5,-8, E5,-4, A4,16, B4,16, D5,16, B4,16,

  E5,-8, E5,-8, D5,-8, CS5,16, B4,-8, A4,16, B4,16, D5,16, B4,16, //18
  D5,4, E5,8, CS5,-8, B4,16, A4,8, A4,8, A4,8, 
  E5,4, D5,2, A4,16, B4,16, D5,16, B4,16,
  FS5,-8, FS5,-8, E5,-4, A4,16, B4,16, D5,16, B4,16,
  A5,4, CS5,8, D5,-8, CS5,16, B4,8, A4,16, B4,16, D5,16, B4,16,

  D5,4, E5,8, CS5,-8, B4,16, A4,4, A4,8,  //23
  E5,4, D5,2, REST,4,
  REST,8, B4,8, D5,8, B4,8, D5,8, E5,4, REST,8,
  REST,8, CS5,8, B4,8, A4,-4, REST,4,
  REST,8, B4,8, B4,8, CS5,8, D5,8, B4,8, A4,4,
  REST,8, A5,8, A5,8, E5,8, FS5,8, E5,8, D5,8,
  
  REST,8, A4,8, B4,8, CS5,8, D5,8, B4,8, //29
  REST,8, CS5,8, B4,8, A4,-4, REST,4,
  B4,8, B4,8, CS5,8, D5,8, B4,8, A4,4, REST,8,
  REST,8, E5,8, E5,8, FS5,4, E5,-4, 
  D5,2, D5,8, E5,8, FS5,8, E5,4, 
  E5,8, E5,8, FS5,8, E5,8, A4,8, A4,4,

  REST,-4, A4,8, B4,8, CS5,8, D5,8, B4,8, //35
  REST,8, E5,8, FS5,8, E5,-4, A4,16, B4,16, D5,16, B4,16,
  FS5,-8, FS5,-8, E5,-4, A4,16, B4,16, D5,16, B4,16,
  E5,-8, E5,-8, D5,-8, CS5,16, B4,8, A4,16, B4,16, D5,16, B4,16,
  D5,4, E5,8, CS5,-8, B4,16, A4,4, A4,8, 

   E5,4, D5,2, A4,16, B4,16, D5,16, B4,16, //40
  FS5,-8, FS5,-8, E5,-4, A4,16, B4,16, D5,16, B4,16,
  A5,4, CS5,8, D5,-8, CS5,16, B4,8, A4,16, B4,16, D5,16, B4,16,
  D5,4, E5,8, CS5,-8, B4,16, A4,4, A4,8,  
  E5,4, D5,2, A4,16, B4,16, D5,16, B4,16,
   
  FS5,-8, FS5,-8, E5,-4, A4,16, B4,16, D5,16, B4,16, //45
  A5,4, CS5,8, D5,-8, CS5,16, B4,8, A4,16, B4,16, D5,16, B4,16,
  D5,4, E5,8, CS5,-8, B4,16, A4,4, A4,8,  
  E5,4, D5,2, A4,16, B4,16, D5,16, B4,16,
  FS5,-8, FS5,-8, E5,-4, A4,16, B4,16, D5,16, B4,16, //45
  
  A5,4, CS5,8, D5,-8, CS5,16, B4,8, A4,16, B4,16, D5,16, B4,16,
  D5,4, E5,8, CS5,-8, B4,16, A4,4, A4,8, 

  E5,4, D5,2, REST,4
};

// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notes = sizeof(melody) / 2;

// this calculates the duration of a whole note in ms

int tempo = 114;
int wholenote = (60000 * 4) / 114;  //(60000 * 4) / tempo

int divider = 0, noteDuration = 0;

int main() {
    enableBuzzer();
    noTone();
  // iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2 - 1; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    playTone(melody[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    _delay_ms(noteDuration*0.1);

    // stop the waveform generation before the next note.
    noTone(buzzer);
  }
  return 0;
}