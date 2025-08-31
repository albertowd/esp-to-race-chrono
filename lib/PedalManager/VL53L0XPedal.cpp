#include "VL53L0XPedal.hpp"

VL53L0XPedal::VL53L0XPedal(const uint8_t i2CAddress, const gpio_num_t shutPin) : Pedal(i2CAddress, shutPin) {
  this->values.currentValue = 0U;
  this->values.maxValue = 0U;
  this->values.minValue = 2000U;
  this->values.percValue = 0U;
}

VL53L0XPedal::~VL53L0XPedal() {
  this->stop();
}

void VL53L0XPedal::configure(const bool debug) {
  Serial.printf("Configuring pedal %X\n", this->i2CAddress);
  digitalWrite(this->shutPin, HIGH);
  delay(500);
  if (!this->sensor.begin(this->i2CAddress, debug, &Wire, Adafruit_VL53L0X::VL53L0X_Sense_config_t::VL53L0X_SENSE_HIGH_SPEED))
    Serial.printf("Error initializing VL53L0X sensor on I2C address %d \n", this->i2CAddress);
  delay(500);
}

void VL53L0XPedal::measure(const bool debug)
{
  if (!this->sensor.getRangingMeasurement(&this->lastMeasurement, false) && this->lastMeasurement.RangeMilliMeter < 2000U)
  {
    this->values.currentValue = this->lastMeasurement.RangeMilliMeter;
    this->values.maxValue = max(this->values.maxValue, this->values.currentValue);
    this->values.minValue = min(this->values.minValue, this->values.currentValue);
    if (this->values.maxValue - this->values.minValue != 0U)
      this->values.percValue = (this->values.currentValue - this->values.minValue) * 100U / (this->values.maxValue - this->values.minValue);
    
    if (debug)
      Serial.printf("Pedal %X value: %umm (min: %u max: %u) %u%%\n", this->i2CAddress, this->values.currentValue, this->values.minValue, this->values.maxValue, this->values.percValue);
  }
}

void VL53L0XPedal::start(const bool debug)
{
  if (!this->ranging) {
    this->configure(debug);
    this->sensor.startRangeContinuous(30U);
    this->ranging = true;
  }
}

void VL53L0XPedal::stop()
{
  if (this->ranging) {
    this->ranging = false;
    this->sensor.stopRangeContinuous();
    digitalWrite(this->shutPin, LOW);
  }
}
