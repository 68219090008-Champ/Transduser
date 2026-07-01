#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Some LiquidCrystal_I2C variants require this include on older Arduino cores.
#ifndef LED_BUILTIN
  #define LED_BUILTIN 13
#endif

// จาก design.md
// KY-025: DO -> D7

// LCD 16x2 I2C: A4 -> SDA, A5 -> SCL, Address = 0x27

const int sensorPin = 7;       // ขา D0 ของ KY-025 ต่อกับ D7
const int ledPin = LED_BUILTIN;
const unsigned long readInterval = 300;

static LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);
  Serial.println("KY-025 Digital Test");
  Serial.println("DO -> Arduino D3");
  Serial.println("LCD I2C address -> 0x27");
  Serial.println("-------------------");

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("KY-025");
  lcd.setCursor(0, 1);
  lcd.print("Starting...");
}

void loop() {
  int sensorState = digitalRead(sensorPin);

  bool hasMagnet = (sensorState == HIGH);
  digitalWrite(ledPin, hasMagnet ? HIGH : LOW);

  const char* msg = hasMagnet ? "Magnet detected" : "No magnet";

  // Serial Monitor
  Serial.print("Digital = ");
  Serial.print(sensorState);
  Serial.print(" | Status = ");
  Serial.println(msg);

  // LCD 16x2
  lcd.setCursor(0, 0);
  lcd.print("KY-025         "); // clear line remnants

  lcd.setCursor(0, 1);
  lcd.print(msg);
  // กันข้อความสั้นกว่าบรรทัดเดิมค้างท้าย
  if (!hasMagnet) {
    lcd.print("       ");
  }

  delay(readInterval);
}

