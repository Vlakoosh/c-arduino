//Use the #include lines to import the C libraries to your code
//We'll write our own libraries as much as possible, but a number of existing libraries are indispensable.
#include <util/delay.h> //This library includes the function named _delay_ms(..) which pauses the execution of the program.
#include <avr/io.h> //Use this library to name the various registers of the ATmega328P microcontroller, like eg DDRB
 
int main() //Start of the program
{
    DDRB = 0b00111100; //Write a binary number to the Data Direction Register B. Pin 5 of port B is enabled for writing with this setting.
    //DDRB |= 0b00100000; //We could also do a bitwise OR, so that we don't erase ones on other positions of DDRB
    //DDRB |= (1 << 5); //We could also use the << bitshift operator.
    //DDRB |= (1 << (PB2 + 3)); //Here we use the port names from io.h to make the code more readable.

    while (1)
    {
        PORTB = (0 << (PB2 + 3)); //We write a 0 to PB2+3 to let the connected LED light up.
        _delay_ms(1000); //We use the _delay_ms(..) function from delay.h to pause the execution during 1000 milliseconds (1 sec).
        PORTB = (1 << (PB2 + 3)); //We write a 1 to PB2+3 to let the connected LED go dark.
        _delay_ms(1000);
    }
    return 0;
}