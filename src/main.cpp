#include <Arduino.h>

const int digitalPin = 3;
const int analogPin = A0;
const int ledPin = LED_BUILTIN;
const unsigned long readInterval = 300;

void setup() {
  pinMode(digitalPin, INPUT);
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);
  Serial.println("KY-025 Sensor Test");
  Serial.println("D0 -> Arduino D3, A0 -> Arduino A0");
  Serial.println("Move a magnet near the sensor.");
  Serial.println("--------------------------------");
}

void loop() {
  int digitalValue = digitalRead(digitalPin);
  int analogValue = analogRead(analogPin);

  digitalWrite(ledPin, digitalValue);

  Serial.print("Digital = ");
  Serial.print(digitalValue);
  Serial.print(" | Analog = ");
  Serial.print(analogValue);
  Serial.print(" | Status = ");

  if (digitalValue == HIGH) {
    Serial.println("Magnet detected");
  } else {
    Serial.println("No magnet");
  }

  delay(readInterval);
}
