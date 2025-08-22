#include "PedalManager.hpp"

PedalManager::PedalManager(const uint8_t shutA, const uint8_t shutB, const uint8_t shutC) {
  this->sensorCount = (shutA != 0U ? 1U : 0U) + (shutB != 0U ? 1U : 0U) + (shutC != 0U ? 1U : 0U);
  this->maxValues = new uint16_t[this->sensorCount];
  this->pins = new uint8_t[this->sensorCount];
  this->sensors = new Adafruit_VL53L0X[this->sensorCount];
  this->values = new uint16_t[this->sensorCount];

  // Clear default values
  for (uint8_t sensorIndex(0U); sensorIndex < this->sensorCount; sensorIndex++) {
    this->values[sensorIndex] = 0U;
    this->maxValues[sensorIndex] = 1U;
  }
}

PedalManager::~PedalManager() {
  this->sensorCount = 0U;
  delete[] this->pins;
  delete[] this->maxValues;
  delete[] this->sensors;
  delete[] this->values;
}

uint16_t PedalManager::getPedalDistance(const uint8_t sensorIndex) const {
  return this->values[sensorIndex];
}

uint16_t PedalManager::getPedalPosition(const uint8_t sensorIndex) const {
  return this->values[sensorIndex] * 100U / this->maxValues[sensorIndex];
}

void PedalManager::setup() const {
  Serial.println("[PM] Setting up PedalManager...");

  for (uint8_t sensorIndex(0U); sensorIndex < this->sensorCount; sensorIndex++) {
    Serial.printf("[PM] Cofiguting sensor %d...\n", this->pins[sensorIndex]);
    pinMode(this->pins[sensorIndex], OUTPUT);
  }
  
  Serial.println("[PM] Resetting all sensors...");
  for (uint8_t sensorIndex(0U); sensorIndex < this->sensorCount; sensorIndex++) {
    digitalWrite(this->pins[sensorIndex], LOW);
  }
  delay(10);

  for (uint8_t sensorIndex(0U); sensorIndex < this->sensorCount; sensorIndex++) {
    Serial.printf("[PM] Initializing sensor %d...\n", this->pins[sensorIndex]);
    digitalWrite(this->pins[sensorIndex], HIGH);
    uint8_t sensorAddress = PEDAL_MANAGER_MIN_I2C_ADDRESS + sensorIndex;
    if (!this->sensors[sensorIndex].begin(sensorAddress, true, &Wire, Adafruit_VL53L0X::VL53L0X_Sense_config_t::VL53L0X_SENSE_HIGH_SPEED)) {
      Serial.printf("[PM] Error initializing sensor %d on I2C address %d \n", this->pins[sensorIndex], sensorAddress);
    }
    this->sensors[sensorIndex].startRangeContinuous(30);
    delay(10);
  }

  Serial.println("Pedal manager ready to be in the loop!");
}

void PedalManager::update(const bool debug) {
  VL53L0X_RangingMeasurementData_t measurement;
  for (uint8_t sensorIndex(0U); sensorIndex < this->sensorCount; sensorIndex++) {
    if (!this->sensors[sensorIndex].getRangingMeasurement(&measurement, debug)) {
      this->maxValues[sensorIndex] = max(this->maxValues[sensorIndex], measurement.RangeMilliMeter);
      this->values[sensorIndex] = measurement.RangeMilliMeter;
    }
  }
}
