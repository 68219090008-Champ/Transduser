#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Some LiquidCrystal_I2C variants require this include on older Arduino cores.
// Some Arduino cores may not define LED_BUILTIN
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

// ตรวจว่าอุปกรณ์ I2C ที่กำหนดมีอยู่จริงหรือไม่
static bool i2cDeviceExists(uint8_t address) {
  Wire.beginTransmission(address);
  // 0 = ACK received
  return (Wire.endTransmission() == 0);
}
const uint8_t ledPin = LED_BUILTIN;
const unsigned long blinkIntervalMs = 500; // 500ms ON / 500ms OFF

void setup() {

  pinMode(sensorPin, INPUT);
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);
  Serial.println("KY-025 Digital Test");
  Serial.println("DO -> Arduino D7");

  Serial.println("LCD I2C address -> 0x27");
  Serial.println("-------------------");

  // เริ่ม I2C bus เพื่อเช็คอุปกรณ์
  Wire.begin();

  // เช็ค LCD ที่ address 0x27 ว่าต่ออยู่หรือไม่
  const bool lcdFound = i2cDeviceExists(0x27);
  Serial.print("I2C device @ 0x27 -> ");
  Serial.println(lcdFound ? "FOUND" : "NOT FOUND");

  lcd.init();
  lcd.backlight();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(lcdFound ? "LCD FOUND" : "LCD NOT FOUND");
  lcd.setCursor(0, 1);
  lcd.print("KY-025 ready");

  delay(1000);

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
  Serial.print("Digital=");
  Serial.print(sensorState);
  Serial.print(" | Magnet=");
  Serial.println(hasMagnet ? "YES" : "NO");
  digitalWrite(ledPin, HIGH);
  delay(blinkIntervalMs);


  // LCD 16x2
  lcd.setCursor(0, 0);
  lcd.print("I2C 0x27 KY-025");

  lcd.setCursor(0, 1);
  lcd.print("Magnet:");
  lcd.print(hasMagnet ? "YES" : "NO ");


  delay(readInterval);
  digitalWrite(ledPin, LOW);
  delay(blinkIntervalMs);
}
