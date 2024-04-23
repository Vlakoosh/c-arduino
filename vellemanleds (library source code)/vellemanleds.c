#include <util/delay.h>
#include <avr/io.h>
#include <usart.h>
#include <vellemanleds.h>

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

void dimLed(int led, int percentage, int duration){
    if (percentage <= 0 || percentage > 100 || led < 0 || led > 3){ return; }
    
    int offtime = 50 - 50 * percentage / 100;
    int ontime = 50 * percentage / 100;
    
    for(int i = 0; i < (duration*20); i++) {
        lightUpOneLed(led);
        _delay_ms(ontime);
        lightDownOneLed(led);
        _delay_ms(offtime);
    }

}

// _delay_ms time has to be constant or compiler throws error. 
//That's why this method is here
//This should be used in for loops where the delay can change 
//inbetween the iterations of the loop
void delayWithVariableTime(int ms)
{
    for (int i = 0; i < ms; i++) {
        _delay_ms(1);
    }
}

void fadeInLed(int led , int duration ){
    if (led < 0 || led > 3){ return; }
    
    int offtime = 100;
    int ontime = 1;
    int change = 100/(duration*10);

    for(int i = 0; i < (duration*10); i++) {
        lightDownOneLed(led);
        delayWithVariableTime(offtime);
        lightUpOneLed(led);
        delayWithVariableTime(ontime);
        offtime -= change;
        ontime += change;
    }
}

void fadeOutLed(int, int){
    if (led < 0 || led > 3){ return; }
    
    int offtime = 1;
    int ontime = 100;
    int change = 100/(duration*10);

    for(int i = 0; i < (duration*10); i++) {
        lightUpOneLed(led);
        delayWithVariableTime(ontime); 
        lightDownOneLed(led);
        delayWithVariableTime(offtime);
        offtime += change;
        ontime -= change;
    }
}
