#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// KY-025 magnetic reed switch
const int KY025_PIN = 7;
// Buzzer output pin
const int BUZZER_PIN = 8;

// I2C LCD address may vary. 0x27 is common for many 16x2 modules.
LiquidCrystal_I2C lcd(0x27, 16, 2);

bool doorOpen = false;
bool previousState = false;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }

  pinMode(KY025_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  lcd.init();
  lcd.backlight();

  Serial.println("เริ่มต้นระบบ KY-025 \u2601");
  Serial.println("อ่านสถานะประตูและแสดงผลทาง Serial Monitor");
  Serial.println();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("KY-025 Door Guard");
  lcd.setCursor(0, 1);
  lcd.print("Waiting...");
  delay(1000);
}

void updateDisplay(bool openState) {
  lcd.clear();
  if (openState) {
    lcd.setCursor(0, 0);
    lcd.print("เปิดอยู่");
    lcd.setCursor(0, 1);
    lcd.print("(อันตราย)");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("ปิดอยู่");
    lcd.setCursor(0, 1);
    lcd.print("(ปลอดภัย)");
  }
}

void updateBuzzer(bool openState) {
  if (openState) {
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }
}

void loop() {
  int sensorValue = digitalRead(KY025_PIN);
  doorOpen = (sensorValue == HIGH);

  if (doorOpen != previousState) {
    if (doorOpen) {
      Serial.println("สถานะ: ประตูเปิดอยู่ (อันตราย)");
      Serial.println("LCD: เปิดอยู่ (อันตราย)");
      Serial.println("Buzzer: ON");
    } else {
      Serial.println("สถานะ: ประตูปิดอยู่ (ปลอดภัย)");
      Serial.println("LCD: ปิดอยู่ (ปลอดภัย)");
      Serial.println("Buzzer: OFF");
    }
    Serial.println();

    updateDisplay(doorOpen);
    updateBuzzer(doorOpen);
    previousState = doorOpen;
  }

  delay(200);
}

