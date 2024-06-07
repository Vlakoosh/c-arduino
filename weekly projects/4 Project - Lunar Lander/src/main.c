#include <avr/io.h>
#include <avr/interrupt.h>
#include <usart.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <vellemanbuttons.h>
#include <vellemanleds.h>
#include <wpsh209displaylib.h>
#include <stdlib.h>
#include <wpsh209buzzerlib.h>

typedef struct
{
  int distance;
  int currentSpeed;
  int burst;
  int fuelReserve;
}dataLog;

volatile float currentSpeed = 100; // speed in m/s (meters per second)
const float gravity = 1.622; // acceleration in m/s²
volatile int distance = 9999; // distance to the lunar surface in meters - m
volatile int fuelReserve = 1500; // liter
volatile int burst = 0;
volatile int ledCounter = 0;
volatile int leds = 0;
volatile int flashSpeed = 1;
dataLog *logs[500];
volatile int logIndex = 0;

void initTimer0() {
  // STEP 1: choose the WAVE FORM and by consequence the Mode of Operation
  // We choose FAST PWM; TCNT0 counts to 255
  TCCR0A |= _BV(WGM00); // WGM00 = 1 --> Phase Correct PWM Mode
  TCCR0B |= _BV(WGM02); // WGM02 = 1 --> With OCRA top

  // STEP 2: *always* set a PRESCALER, otherwise the timer won't count
  // The counting speed is determined by the CPU clock (16 Mhz) divided by this factor
  TCCR0B |= _BV(CS02) | _BV(CS00); // CS00 and CS01 = 1 --> prescaler, factor is now 64
  // STEP 3: enable INTERRUPTS
  OCR0A = 156;
  // Enable interrupts for overflow: TCNT0 == TOP
  TIMSK0 |= _BV(TOIE0); // enable overflow interrupt
}

void initTimer1() {
  // STEP 1: choose the WAVE FORM and by consequence the Mode of Operation
  // We choose Phase Correct PWM; TCNT counts to 16635
  TCCR1A |= _BV(WGM10) | _BV(WGM11); // WGM10 & WGM11 = 1 --> Fast PWM Mode
  TCCR1B |= _BV(WGM12) | _BV(WGM13); // WGM12 & WGM13 = 1 --> Fast PWM Mode
  // STEP 2: *always* set a PRESCALER, otherwise the timer won't count
  // The counting speed is determined by the CPU clock (16 Mhz) divided by this factor
  TCCR1B |= _BV(CS12); // CS12 = 1 --> prescaler, factor is now 256
  // STEP 3: enable INTERRUPTS
  OCR1A = 62500; //set top value to 1s
  // Enable interrupts for overflow: TCNT1 == TOP
  TIMSK1 |= _BV(TOIE1); // enable overflow interrupt
}

void showParameter() {
  writeNumber(distance);
}

ISR(TIMER1_OVF_vect) {
  currentSpeed += gravity - burst / 5;
  distance -= (int) currentSpeed;
  fuelReserve -= burst;

  logs[logIndex] = malloc(sizeof(dataLog));
  if (logs[logIndex]) {
    logs[logIndex]->distance = distance;
    logs[logIndex]->currentSpeed = currentSpeed;
    logs[logIndex]->fuelReserve = fuelReserve;
    logs[logIndex]->burst = burst;
    logIndex++;
  }
  flashSpeed = fuelReserve%375/18;
  leds = fuelReserve/375;
  burst = 0;
}

ISR(TIMER0_OVF_vect) {
  ledCounter++;
  if (ledCounter >= flashSpeed)
  {
      lightToggleOneLed(leds+1);
      ledCounter = 0;
      lightDownOneLed(leds+2);
  }
  
  if (buttonPushed(1) && (fuelReserve - burst > 0))
  {
    if (burst <= 50) burst++;
  } else if (fuelReserve <= 0){
    lightDownAllLeds();
    TCCR0B &=  ~_BV(CS00) & ~_BV(CS01) & ~_BV(CS02); // CS12, CS11 and CS10 = 0 --> prescaler, factor is now 0, timer is stopped
    playTone( NOTE_C5, 90);
    noTone();
    _delay_ms(10);
    playTone( NOTE_G5, 90);
    noTone();
    _delay_ms(10);
    playTone( NOTE_C5, 90);
    noTone();
    _delay_ms(10);
    playTone( NOTE_C5, 90);
    noTone();
      
    }
}

int main() {
  initUSART();
  enableButton(1);
  initTimer0();
  initTimer1();
  sei();
  enableAllLeds();
  initDisplay();
  lightUpAllLeds();
  enableBuzzer();
  noTone();
  while (!((distance <= 0) || ((distance <= 3) && (currentSpeed <= 5))))
  {
    showParameter();
  }
  TCCR1B &=  ~_BV(CS10) & ~_BV(CS11) & ~_BV(CS12); // CS12, CS11 and CS10 = 0 --> prescaler, factor is now 0, timer is stopped
  TCCR0B |= _BV(CS02) | _BV(CS00); // CS00, CS01 and CS02 = 0 --> prescaler, factor is now 0, timer is stopped
  clearDisplay();
  for (int i = 0; i < logIndex; i++)
  {
    printf("%d: Distance: %d, Speed: %d, Fuel: %d, Burts: %d\n", i, logs[i]->distance, logs[i]->currentSpeed, logs[i]->fuelReserve, logs[i]->burst);
    free(logs[i]);
  }
  
  if (currentSpeed <= 5){
    playTone( NOTE_C5, 90);
    noTone();
    _delay_ms(10);
    playTone( NOTE_E5, 90);
    noTone();
    _delay_ms(10);
    playTone( NOTE_G5, 90);
    noTone();
    while(1){
      writeString(" WIN");
    }
  }else{
    playTone( NOTE_G5, 90);
    noTone();
    _delay_ms(10);
    playTone( NOTE_E5, 90);
    noTone();
    _delay_ms(10);
    playTone( NOTE_C5, 90);
    noTone();
    while(1){
      writeString("LOSE");
    }
  }


  
}