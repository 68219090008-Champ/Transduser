#include <Arduino.h>
#include <DHT.h>

const uint8_t DHT_PIN = 4;
const uint8_t DHT_TYPE = DHT11;
const unsigned long READ_INTERVAL_MS = 2000;

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();

  Serial.println("DHT11 temperature and humidity reader");
  Serial.println("Data pin: Arduino UNO D4");
}

void loop() {
  const float humidity = dht.readHumidity();
  const float temperatureC = dht.readTemperature();

  if (isnan(humidity) || isnan(temperatureC)) {
    Serial.println("Failed to read from DHT11 sensor");
  } else {
    Serial.print("Temperature: ");
    Serial.print(temperatureC);
    Serial.print(" C  Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  }

  delay(READ_INTERVAL_MS);
}