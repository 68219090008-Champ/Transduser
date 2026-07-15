#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

const uint8_t DHT_PIN = 4;
const uint8_t DHT_TYPE = DHT11;
const unsigned long READ_INTERVAL_MS = 2000;
const uint8_t LCD_ADDRESS = 0x27;
const uint8_t LCD_COLUMNS = 16;
const uint8_t LCD_ROWS = 2;

DHT dht(DHT_PIN, DHT_TYPE);
LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  lcd.begin(LCD_COLUMNS, LCD_ROWS);
  lcd.backlight();
  dht.begin();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DHT11 Reader");
  lcd.setCursor(0, 1);
  lcd.print("Waiting...");

  Serial.println("DHT11 temperature and humidity reader");
  Serial.println("Data pin: Arduino UNO D4");
  Serial.println("LCD I2C address: 0x27");
  delay(1000);
}

void loop() {
  const float humidity = dht.readHumidity();
  const float temperatureC = dht.readTemperature();

  if (isnan(humidity) || isnan(temperatureC)) {
    Serial.println("Failed to read from DHT11 sensor");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor error");
    lcd.setCursor(0, 1);
    lcd.print("Check wiring");
  } else {
    Serial.print("Temperature: ");
    Serial.print(temperatureC);
    Serial.print(" C  Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperatureC, 1);
    lcd.print("C");

    lcd.setCursor(0, 1);
    lcd.print("Hum: ");
    lcd.print(humidity, 1);
    lcd.print("%");
  }

  delay(READ_INTERVAL_MS);
}