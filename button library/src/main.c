#include <util/delay.h>
#include <avr/io.h>
#include <usart.h>
#include <vellemanbuttons.h>

int main()
{
    initUSART();
    enableButton(2);  
    printf( "DDRC: " );
    printBinaryByte( DDRC );
      
    printf( "\nPORTC: " );
    printBinaryByte( PORTC );
    while ( 1 )
    {
        printf( "\nPINC: " );
        printBinaryByte( PINC );
        if (buttonPushed(2))
        {
            printf( " - Button 0 pressed!" );
        }
        if (buttonReleased(2))
        {
            printf( " - Button 0 released!\n" );
        }
        _delay_ms( 1000 );
    }
    return 0;
}

