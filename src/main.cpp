#include <Arduino.h>

const int sensorPin = 3;       // ขา D0 ของ KY-025 ต่อกับ D3
const int ledPin = LED_BUILTIN;
const unsigned long readInterval = 300;

void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);
  Serial.println("KY-025 Digital Test");
  Serial.println("DO -> Arduino D3");
  Serial.println("-------------------");
}

void loop() {
  int sensorState = digitalRead(sensorPin);

  Serial.print("Digital = ");
  Serial.print(sensorState);
  Serial.print(" | Status = ");

  if (sensorState == HIGH) {
    digitalWrite(ledPin, HIGH);
    Serial.println("Magnet detected");
  } else {
    digitalWrite(ledPin, LOW);
    Serial.println("No magnet");
  }

  delay(readInterval);
}
