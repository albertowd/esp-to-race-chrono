#include <Arduino.h>

#include <PedalManager.hpp>
#include <PerformanceManager.hpp>

// VL53L0X/TOF0200C @ 33Hz
PedalManager pedals(D5);

void loop();
void setup();

void loop() {
  digitalWrite(LED_BUILTIN, LOW);
  PerformanceManager::instance()->reset();

  Serial.printf("SensorA: %d mm\n", pedals.getMeasurement(0, false));

  digitalWrite(LED_BUILTIN, HIGH);
  PerformanceManager::instance()->measure();
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  PerformanceManager::instance()->reset();

  Serial.begin(115200);
  // Wait for 1 second to a USB instance
  unsigned long serialTimeout = millis() + 1000;
  while (!Serial && serialTimeout > millis()) { delay(1); }

  pedals.setup();

  delay(1000);

  PerformanceManager::instance()->measure(false);
  digitalWrite(LED_BUILTIN, HIGH);
}