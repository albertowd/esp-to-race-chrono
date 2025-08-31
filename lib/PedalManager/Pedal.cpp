#include <Arduino.h>

#include "Pedal.hpp"

Pedal::Pedal(const uint8_t i2CAddress, const gpio_num_t shutPin) : i2CAddress(i2CAddress), ranging(false), shutPin(shutPin) {
  pinMode(this->shutPin, OUTPUT);
  digitalWrite(this->shutPin, LOW);
  delay(10);
}

Pedal::~Pedal()
{
  this->i2CAddress = 0U;
  this->shutPin = GPIO_NUM_NC;
  this->values = PedalValues();
}

bool Pedal::isRanging() const {
  return this->ranging;
}

PedalValues Pedal::getValues() const
{
  return this->values;
}
