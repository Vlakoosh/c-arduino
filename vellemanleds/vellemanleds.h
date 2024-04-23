#include <util/delay.h>
#include <avr/io.h>
#include <usart.h>

void enableOneLed(int);

void enableMultipleLeds(uint8_t); 

void enableAllLeds ();

void lightUpOneLed(int); 

void lightUpMultipleLeds (uint8_t);

void lightUpAllLeds (); 

void lightDownOneLed(int); 

void lightDownMultipleLeds (uint8_t);

void lightDownAllLeds (); 

void lightToggleOneLed(int);

void dimLed(int, int, int);  
  /* parameters: lednumber, percentage, duration */ 

void fadeInLed(int, int);  
  /* parameters: lednumber, duration*/ 

//void fadeOutLed(int, int);
  /* parameters: lednumber, duration */