#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// กำหนดพิน
constexpr uint8_t KY025_DO_PIN = 7;  // KY-025 DO -> Arduino D7
constexpr uint8_t BUZZER_PIN   = 5;  // Buzzer + -> Arduino D5
constexpr unsigned long DEBOUNCE_MS = 50;

// ที่อยู่ I2C ของ LCD (เปลี่ยนเป็น 0x3F ถ้าไม่ขึ้น)
LiquidCrystal_I2C lcd(0x27, 16, 2);

bool stableDoorOpen = false;
bool lastRawDoorOpen = false;
unsigned long lastRawChangeMs = 0;

void showDoorStatus(bool doorOpen) {
  Serial.println(F("--------------------------------"));
  Serial.print(F("KY-025 DO (D7): "));
  Serial.println(doorOpen ? F("HIGH") : F("LOW"));
  Serial.print(F("Door status: "));
  Serial.println(doorOpen ? F("OPEN - WARNING") : F("CLOSED - SAFE"));
  Serial.print(F("Buzzer (D5): "));
  Serial.println(doorOpen ? F("ON") : F("OFF"));

  digitalWrite(BUZZER_PIN, doorOpen ? HIGH : LOW);

  // อัปเดตข้อความบน LCD โดยไม่เคลียร์ทั้งจอ (ลดการกะพริบ)
  lcd.setCursor(0, 0);
  if (doorOpen) {
    lcd.print("เปิดอยู่ (อันตราย) ");   // เติมช่องว่างลบข้อความเก่า
    lcd.setCursor(0, 1);
    lcd.print("Buzzer: ON        ");
  } else {
    lcd.print("ปิดอยู่ (ปลอดภัย) ");
    lcd.setCursor(0, 1);
    lcd.print("Buzzer: OFF       ");
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(KY025_DO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  lcd.init();
  lcd.backlight();

  // อ่านสถานะเริ่มต้น
  stableDoorOpen = (digitalRead(KY025_DO_PIN) == HIGH);
  lastRawDoorOpen = stableDoorOpen;
  lastRawChangeMs = millis();

  Serial.println();
  Serial.println(F("KY-025 Machine Door Monitor"));
  Serial.println(F("Serial Monitor speed: 9600 baud"));
  Serial.println(F("DO LOW = door closed, DO HIGH = door open"));
  showDoorStatus(stableDoorOpen);
}

void loop() {
  const bool rawDoorOpen = (digitalRead(KY025_DO_PIN) == HIGH);
  const unsigned long now = millis();

  if (rawDoorOpen != lastRawDoorOpen) {
    lastRawDoorOpen = rawDoorOpen;
    lastRawChangeMs = now;
  }

  // debounce
  if (rawDoorOpen != stableDoorOpen && now - lastRawChangeMs >= DEBOUNCE_MS) {
    stableDoorOpen = rawDoorOpen;
    showDoorStatus(stableDoorOpen);
  }
}
