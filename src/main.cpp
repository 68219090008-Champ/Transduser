#include <Arduino.h>

const int ledPin1 = 13;
const int ledPin2 = 12;
const unsigned long blinkDelay = 1000;

void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
}

void loop() {
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, LOW);
  delay(blinkDelay);

  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, HIGH);
  delay(blinkDelay);
}
