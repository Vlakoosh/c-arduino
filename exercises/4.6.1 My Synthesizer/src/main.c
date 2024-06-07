#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <usart.h>
#include <wpsh209buzzerlib.h>
#include <vellemanbuttons.h>
#include <wpsh209adclib.h>
#include <wpsh209displaylib.h>
//library for using booleans instead of int
#include <stdbool.h> 

void init();
ISR(PCINT1_vect);
bool playing = false;

int main()
{
    init();
    sei();

    while (!playing)
    {
        sei();
        readPotentiometer();
    }
    while (playing)
    {
        sei();
        int tone = readPotentiometerOnce();
        enableBuzzer();
        playTone(tone, 500);
        _delay_ms(500); 
    }
    
    return 0;
}

void init()
{
    initUSART();
    enableButton(1);
    initADC();
    initDisplay();
    enableAllButtonInterrupts();
}

ISR(PCINT1_vect) //interuprt at PORTC
{
    if (bit_is_clear(PINC, PC1)) //button pin, button 1
    {
        _delay_us(1000); //avoid bouncetime (debounce)
        if (bit_is_clear(PINC, PC1))
        {
            writeStringAndWait("helo",100);
            disableBuzzer();
            playing = !playing;
            main();
        }
    }
}