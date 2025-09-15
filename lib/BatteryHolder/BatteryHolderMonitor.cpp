#include <Arduino.h>

#include "BatteryHolderMonitor.hpp"

BatteryHolder::Monitor::Monitor(uint8_t batteryPin) : batteryPin(batteryPin), lastPerc(0U), lastValue(0U), lastVoltage(0.0f) {}

float BatteryHolder::Monitor::getVoltage() const
{
  return this->lastVoltage;
}

uint16_t BatteryHolder::Monitor::getValue() const
{
  return this->lastValue;
}

uint8_t BatteryHolder::Monitor::getPerc() const
{
  return this->lastPerc;
}

void BatteryHolder::Monitor::setup() const
{
  pinMode(this->batteryPin, INPUT);
}

void BatteryHolder::Monitor::update(bool debug)
{
  this->lastValue = analogRead(this->batteryPin);
  this->lastVoltage = this->lastValue * BATTERY_MULTIPLIER / BATTERY_MAX_VALUE * BATTERY_VOLTAGE;

  float maxVal = BATTERY_VOLTAGE + 0.5f;
  float minVal = BATTERY_VOLTAGE - 1.0f;
  uint8_t perc = (uint16_t)((this->lastVoltage - minVal) / (maxVal - minVal) * 100U);
  this->lastPerc = min(max((uint8_t)0U, perc), (uint8_t)100U);

  if (debug)
  {
    Serial.print("ADC Value: ");
    Serial.print(this->lastValue);
    Serial.print(" | Battery Voltage: ");
    Serial.print(this->lastVoltage);
    Serial.print(" V");
    Serial.print(" | ");
    Serial.print(this->lastPerc);
    Serial.println(" %");
  }
}
