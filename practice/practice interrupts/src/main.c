#include <avr/io.h>
#include <avr/interrupt.h>
#include <usart.h>
#include <util/delay.h>

#define BUTTON1 PC1
#define BUTTON2 PC2


ISR( PCINT1_vect ) {

    if (bit_is_clear(PINC, BUTTON1)){
        PORTB |= (1 << 3);
    }

    if (bit_is_clear(PINC, BUTTON2)){
        PORTB &= ~(1 << 3);
    }
    
}

int main() {
    //set button pin as input
    DDRC &= ~(1 << BUTTON1);
    //set button pull-up resistor to high
    PORTC |= (1 << BUTTON1);

    //set button pin as input
    DDRC &= ~(1 << BUTTON2);
    //set button pull-up resistor to high
    PORTC |= (1 << BUTTON2);



    //set LED pin as output
    DDRB |= (1 << 2);
    //light down LED
    PORTB |= (1 << 2);

    //set LED pin as output
    DDRB |= (1 << 3);
    //light down LED
    PORTB |= (1 << 3);

    //enable port c as interrupt (listen for changes in PORTC)
    PCICR |= (1 << PCIE1);
    //z
    PCMSK1 |= (1 << BUTTON1);
    PCMSK1 |= (1 << BUTTON2);

    initUSART();
    sei();

    while(1){
        PORTB ^= (1 << 2);
        _delay_ms(200);
    }
}