#include <util/delay.h>
#include <avr/io.h>
#include <usart.h>
#include <buttonlibrary.h>

void enableButton( int button ){
    DDRC &= ~( 1 << button ); /* Button 'button' is connected to Cbutton.
                             * We set the corresponding bit in the Data Direction Register to 0. */
    PORTC |= ( 1 << button ); /* Activate the Pull-up of C1: PINC will be set to high */
}

int buttonPushed( int button ){
    return ( PINC & ( 1 << button )) == 0;   /* This way we can test whether the 'button' bit
                                             * of PINC is set to 0 (button is pressed) */
}

int buttonReleased( int button ){
    return ( PINC & ( 1 << button )) != 0;    /* This way we can test whether the 'button' bit
                                             * of PINC is NOT set to 0 (button is NOT pressed) */
} 