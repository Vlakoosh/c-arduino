#include <avr/io.h>
#define __DELAY_BACKWARD_COMPATIBLE__ 
#include <util/delay.h>
#include <stdio.h>

void enableBuzzer(){
    DDRD |= 0b00001000;
}

void buzzerOn(){
    PORTD &= ~(1 << PD3);
}

void buzzerOff(){
    PORTD |= (1 << PD3);
}

void fadeBuzzer(int beginPercentage, int endPercentage, long duration)
{
    if (duration <= 0) return;
    if (beginPercentage < 0) beginPercentage = 0;
    if (beginPercentage > 100) beginPercentage = 100;
    if (endPercentage < 0) endPercentage = 0;
    if (endPercentage > 100) endPercentage = 100;
    duration *= 10;
    int p = beginPercentage;
    int diff = endPercentage - beginPercentage;
    int suppl = (diff > 0 ? 1 : -1);
    long stepTime = duration / diff * suppl;
    for (long i = 0; i < duration; i++) {
        if (i%stepTime == 0){
            p += suppl;
        }
        if (i%100 <= p){
            buzzerOn();
        }else{
            buzzerOff();
        }
        _delay_us(1);
    }
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

void toggleBuzzer() {
  PORTD ^= ( 1 << PD3 );
}

void disableBuzzer()
{
   DDRD &= ~( 1 << PD3 ); //Buzzer is connected to PD3
}