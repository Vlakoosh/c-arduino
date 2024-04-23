void enableOneLed(int);
  /* parameters: lednumber */ 

void enableMultipleLeds(uint8_t); 
  /* parameters: byte of leds */ 

void enableAllLeds ();

void lightUpOneLed(int); 
  /* parameters: lednumber */ 

void lightUpMultipleLeds (uint8_t);
  /* parameters: byte of leds */ 

void lightUpAllLeds (); 

void lightDownOneLed(int); 
  /* parameters: lednumber */ 

void lightDownMultipleLeds (uint8_t);
  /* parameters: byte of leds */ 

void lightDownAllLeds (); 

void lightToggleOneLed(int);
  /* parameters: lednumber */ 

void dimLed(int, int, int);  
  /* parameters: lednumber, percentage, duration */ 

void fadeInLed(int, int);  
  /* parameters: lednumber, duration*/ 

void fadeOutLed(int, int);
  /* parameters: lednumber, duration */