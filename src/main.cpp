#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

// Wiring from test/KY-025.md
constexpr uint8_t KY025_DO_PIN = 7;  // KY-025 DO -> Arduino D7
constexpr uint8_t BUZZER_PIN = 8;    // Buzzer + -> Arduino D8
constexpr unsigned long DEBOUNCE_MS = 50;

// Typical I2C address for a 16x2 LCD.  Change to 0x3F if required.
LiquidCrystal_I2C lcd(0x27, 16, 2);

bool stableDoorOpen = false;
bool lastRawDoorOpen = false;
unsigned long lastRawChangeMs = 0;

void showDoorStatus(bool doorOpen) {
  // The KY-025 document specifies: LOW = magnet near / door closed,
  // HIGH = magnet away / door open.
  Serial.println(F("--------------------------------"));
  Serial.print(F("KY-025 DO (D7): "));
  Serial.println(doorOpen ? F("HIGH") : F("LOW"));
  Serial.print(F("Door status: "));
  Serial.println(doorOpen ? F("OPEN - WARNING") : F("CLOSED - SAFE"));
  Serial.print(F("Buzzer (D8): "));
  Serial.println(doorOpen ? F("ON") : F("OFF"));

  digitalWrite(BUZZER_PIN, doorOpen ? HIGH : LOW);

  lcd.clear();
  lcd.setCursor(0, 0);
  // Display Thai messages: เปิดอยู่ (Open) or ปิดอยู่ (Closed)
  if (doorOpen) {
    lcd.print("Door: OPEN");
    lcd.setCursor(0, 1);
    lcd.print("Buzzer: ON");
  } else {
    lcd.print("Door: CLOSED");
    lcd.setCursor(0, 1);
    lcd.print("Buzzer: OFF");
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(KY025_DO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  lcd.init();
  lcd.backlight();

  // Read and report the real initial state, so the Serial Monitor is useful
  // immediately after reset.
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

  // Reed switches can briefly bounce when the magnet moves.
  if (rawDoorOpen != stableDoorOpen && now - lastRawChangeMs >= DEBOUNCE_MS) {
    stableDoorOpen = rawDoorOpen;
    showDoorStatus(stableDoorOpen);
  }
}