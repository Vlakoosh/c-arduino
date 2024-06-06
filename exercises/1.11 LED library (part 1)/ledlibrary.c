#include <util/delay.h>
#include <avr/io.h>
#include <usart.h>
#include <ledlibrary.h>

void enableOneLed(int led){
    if ( led < 0 || led > 3 ) return;
    DDRB |= (1 << (led+2));
}

void enableMultipleLeds(uint8_t leds){
    DDRB |= leds;
}

void enableAllLeds(){
    DDRB = 0b11111111;
}

void lightUpOneLed(int led){
    if ( led < 0 || led > 3 ) return;
    PORTB &= ~(1 << (led+2));
}

void lightUpMultipleLeds (uint8_t leds){
    PORTB &= leds;
}

void lightUpAllLeds (){
    PORTB &= 0b11000011;
}

void lightDownOneLed(int led){
    if ( led < 0 || led > 3 ) return;
    PORTB |= (1 << (led+2));
}

void lightDownMultipleLeds (uint8_t leds){
    PORTB |= leds;
}

void lightDownAllLeds (){
    PORTB ^= 0b00111100;
}

void lightToggleOneLed(int led){
    PORTB ^= (0 << (led+2));
}