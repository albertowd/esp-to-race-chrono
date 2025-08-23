#include <Arduino.h>

#include "Pedal.hpp"

Pedal::Pedal(const uint8_t i2CAddress, const gpio_num_t shutPin) : i2CAddress(i2CAddress), shutPin(shutPin) {
  pinMode(this->shutPin, OUTPUT);
  digitalWrite(this->shutPin, LOW);
}

Pedal::~Pedal()
{
  this->i2CAddress = 0U;
  this->shutPin = GPIO_NUM_NC;
  this->values = PedalValues();
}

PedalValues Pedal::getValues() const
{
  return this->values;
}
