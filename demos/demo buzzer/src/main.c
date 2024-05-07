#include <avr/io.h>
#include <usart.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>

//DURATION IS IN MILLISECONDS
#define DURATION 150

//FREQUENCIES OF THE NOTES
#define C5 523.250
#define D5 587.330
#define E5 659.250
#define F5 698.460
#define G5 783.990
#define A5 880.00
#define B5 987.770
#define C6 1046.500

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

int main()
{
initUSART();
float frequencies[] = { C5, D5, E5, F5, G5, A5, B5, C6 }; //do-re-mi...
enableBuzzer();
for ( int note = 0; note < 8; note++ )
 {
  playTone( frequencies[note], DURATION );
  printf( "Period: %d\n", (int) frequencies[ note ] );
  _delay_ms( DURATION ); 
 }
return 0;
}