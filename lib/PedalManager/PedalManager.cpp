#include "PedalManager.hpp"

PedalManager::PedalManager(const uint8_t shutA, const uint8_t shutB, const uint8_t shutC) {
  this->sensorCount = (shutA != 0 ? 1 : 0) + (shutB != 0 ? 1 : 0) + (shutC != 0 ? 1 : 0);
  this->measurements = new VL53L0X_RangingMeasurementData_t[sensorCount];
  this->pins = new uint8[sensorCount];
  this->sensors = new Adafruit_VL53L0X[sensorCount];
}

PedalManager::~PedalManager() {
  this->sensorCount = 0;
  delete[] this->measurements;
  delete[] this->pins;
  delete[] this->sensors;
}

uint16_t PedalManager::getMeasurement(const uint8 pedalIndex) const {
  return this->measurements[pedalIndex].RangeMilliMeter;
}

void PedalManager::setup() const {
  Serial.println("[PM] Setting up PedalManager...");

  for (uint8_t sensorIndex(0); sensorIndex < this->sensorCount; sensorIndex++) {
    Serial.printf("[PM] Cofiguting sensor %d...\n", this->pins[sensorIndex]);
    pinMode(this->pins[sensorIndex], OUTPUT);
  }
  
  Serial.println("[PM] Resetting all sensors...");
  for (uint8_t sensorIndex(0); sensorIndex < this->sensorCount; sensorIndex++) {
    digitalWrite(this->pins[sensorIndex], LOW);
  }
  delay(10);

  for (uint8_t sensorIndex(0); sensorIndex < this->sensorCount; sensorIndex++) {
    Serial.printf("[PM] Initializing sensor %d...\n", this->pins[sensorIndex]);
    digitalWrite(this->pins[sensorIndex], HIGH);
    uint8_t sensorAddress = PEDAL_MANAGER_MIN_I2C_ADDRESS + sensorIndex;
    if (!this->sensors[sensorIndex].begin(sensorAddress)) {
      Serial.printf("[PM] Error initializing sensor %d on I2C address %d \n", this->pins[sensorIndex], sensorAddress);
    }
    delay(10);
  }

  Serial.println("Pedal manager ready to be in the loop!");
}

void PedalManager::update(bool debug) {
  for (uint8_t sensorIndex(0); sensorIndex < this->sensorCount; sensorIndex++) {
    Serial.printf("[PM] Ranging test for sensor %d...\n", this->pins[sensorIndex]);
    this->sensors[sensorIndex].rangingTest(&this->measurements[sensorIndex], debug);
  }
}
