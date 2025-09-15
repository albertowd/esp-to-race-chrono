#include <Arduino.h>

#include "BatteryHolderMonitor.hpp"

BatteryHolder::Monitor::Monitor(uint8_t batteryPin): batteryPin(batteryPin), lastValue(0U), lastVoltage(0.0f) {}

float BatteryHolder::Monitor::getVoltage() const {
  return this->lastVoltage;
}

uint16_t BatteryHolder::Monitor::getValue() const {
  return this->lastValue;
}

void BatteryHolder::Monitor::setup() const {
  pinMode(this->batteryPin, INPUT);
}

void BatteryHolder::Monitor::update(bool debug) {
  this->lastValue = analogRead(this->batteryPin);

  // Convert ADC value to voltage (adjust these values based on your board and battery)
  // This is a simplified conversion, you may need a more complex calculation
  // or voltage divider to get an accurate battery voltage reading.
  this->lastVoltage = this->lastValue * (5.0 / 4095.0); // For ESP32, 4095 is the max ADC value

  if (debug) {
    Serial.print("ADC Value: ");
    Serial.print(this->lastValue);
    Serial.print(" | Battery Voltage: ");
    Serial.print(this->lastVoltage);
    Serial.println(" V");
  }
}
