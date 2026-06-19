#include <Arduino.h>

const int ledPin = LED_BUILTIN;
const unsigned long blinkDelay = 1000;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH);
  delay(blinkDelay);

  digitalWrite(ledPin, LOW);
  delay(blinkDelay);
}