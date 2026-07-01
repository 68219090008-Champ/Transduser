#include <Arduino.h>
#include <Wire.h>

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }

  Wire.begin();
  Serial.println("Scanning I2C addresses...");
}

void loop() {
  byte error;
  byte address;
  int deviceCount = 0;

  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
      deviceCount++;
    } else if (error == 4) {
      Serial.print("Unknown error at 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }

  if (deviceCount == 0) {
    Serial.println("No I2C devices found");
  } else {
    Serial.println("Scan complete");
  }

  delay(5000);
}