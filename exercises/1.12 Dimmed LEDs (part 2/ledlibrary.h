void enableOneLed(int);
  /* parameters: lednumber */ 

void enableMultipleLeds(uint8_t); 
  /* parameters: byte of leds */ 

void enableAllLeds ();

void dimLed(int, int, int);  
  /* parameters: lednumber, percentage, duration */ 

void fadeInLed(int, int);  
  /* parameters: lednumber, duration*/ 

void fadeOutLed(int, int);
  /* parameters: lednumber, duration */