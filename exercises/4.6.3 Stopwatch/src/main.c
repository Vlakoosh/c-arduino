#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <usart.h>

#include <wpsh209buzzerlib.h>
#include <vellemanbuttons.h>
#include <wpsh209displaylib.h>

#define MULTIPLE 250
// global var, trying.
uint16_t counter = 0;
uint8_t minutes = 0;
uint8_t seconds = 0;

// prototypes
void initTimer();
void startTimer();
void stopTimer();
void writeTime(uint8_t minutes, uint8_t seconds);
void tick();
void setup();
ISR(TIMER2_COMPA_vect);
ISR(PCINT1_vect);

int main()
{
    setup();

    initTimer();
    startTimer();

    sei();

    while (1)
    {
        // tick();
        // writeTime(minutes, seconds);
    }

    return 0;
}

void setup() // it continiously runs this?
{
    initUSART();
    initDisplay();
    enableAllButtons(3);
    // Enable interrupt for buttons
    PCICR |= _BV(PCIE1);
    PCMSK1 |= _BV(PC1) | _BV(PC2) | _BV(PC3);

    printf("Start the stopwatch by pressing button 1.\nStop by pressing button 2.\nReset timer with button 3.\n\n");
}

// 1st we pick the timer, timer 2: 8 bits, 255 TOP value.
// 2nd we setting mode of operation:

void initTimer() // example code
{
    // STEP 1: choose the WAVE FORM and by consequence the Mode of Operation

    // We choose a different mode with having 2 everywhere
    TCCR2A |= _BV(WGM21); // we put it to two here, meaning we are in a different mode.

    // STEP 2: *always* set a PRESCALER, otherwise the timer won't count
    // goes in start timer, ofc

    // STEP 3: enable INTERRUPTS

    // Enable interrupts for 2 cases: TCNT0 == TOP and TCNT0 == OCR0A
    // shouldn't be enabled //TIMSK2 |= _BV(TOIE2);  // enable overflow interrupt

    TIMSK2 |= _BV(OCIE2A); // enable OCRA interrupt

    // have to put value 249 in the OCR2A register. [OUTPUT COMPARE REGISTER]
    OCR2A = 250;

    sei();
}

void startTimer()
{
    counter = 0;
    // The counting speed is determined by the CPU clock (16 Mhz) divided by this factor
    TCCR2B |= _BV(CS22) | _BV(CS21); // 22 and 21 => 256 scaling factor :]
    sei();
}

void stopTimer()
{
    TCCR2B &= ~_BV(CS22) & ~_BV(CS21) & ~_BV(CS20); // 22,21,20 to 0 => timer doesn't count
} // stopping works

void tick()
{
    seconds++;
    printf("second");
    // printf("%d\n",seconds);
    if (seconds >= 60)
    {
        seconds = 0;
        minutes++;
    }
    
}

void writeTime(uint8_t minutes, uint8_t seconds)
{
    int number = ((int)minutes * 100) + (int)seconds;

    if (number > 9999)
    {
        writeStringAndWait("OFLOW", 100); // overflow.
    }
    writeNumber(number);

    // printf("%d\n", number); // testing
    //writeNumberAndWait(number, 1000); // putting this as a 1000 is a hack solution, doesn't actually let our timer work
}

// This ISR runs every 4 ms
ISR(TIMER2_COMPA_vect) // runs when TIMER interrupts are triggered.
{
    counter++;
    // printf("second2");
    // if (((counter + 1) % MULTIPLE) == 0)
    // {
    //     tick();
    // }
    //or

    if (counter + 1 >= MULTIPLE)
    {
        tick();
        counter = 0; // bruh
        // or you can use a modulo
    }
    writeTime(minutes,seconds);
    // PORTB &= ~( _BV( PB2 ) | _BV( PB3 ) | _BV( PB4 ) | _BV( PB5 ));
    // idk what this line does.
}

ISR(PCINT1_vect)
{
    _delay_us(1000);
    if (bit_is_clear(PINC, PC1))
    {
        startTimer();
        printf("\nTimer started\n");
    }
    if (bit_is_clear(PINC, PC2))
    {
        stopTimer();
        printf("\nTimer stopped\n");
    }
    if (bit_is_clear(PINC, PC3))
    {
        stopTimer();
        minutes = 0;
        seconds = 0;
        printf("Timer reset\n");
    }
}