#include <Arduino.h>

#define BUTTON_PIN 2
#define LED_PIN 3


//przycisk podłaczasz do pina z jednej strony
//z drugiej strony przycisk podłączasz do GND (0v)

void setup() {

  pinMode(LED_PIN, OUTPUT);

  //TAK USTAW PRZYCISK PRZED UŻYCIEM!!!
  //ustaw pin przycisku jako INPUT (wejście)
  pinMode(BUTTON_PIN, INPUT);
  //ustaw pin przycisku na HIGH używając digitalWrite
  digitalWrite(BUTTON_PIN, HIGH);
  //HIGH = NIE naciśnięty, LOW = naciśnięty
}

void loop() {
  //TAK CZYTAJ WARTOŚĆ PRZYCISKU

  //zapisz stan pin'u jako int
  int buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == LOW) {
    //przycisk jest naciśnięty kiedy pin jest LOW
    digitalWrite(LED_PIN, HIGH);
  }
  else{
    //przycisk nie jest naciśnięty kiedy pin jest HIGH
    digitalWrite(LED_PIN, LOW);
  }
}