#include "PedalManager.hpp"
#include "VL53L0XPedal.hpp"

PedalManager::PedalManager(const gpio_num_t *shutPins, const uint8_t pinCount)
{
  memset(this->pedals, 0, PEDAL_MANAGER_MIN_I2C_ADDRESS);
  for (uint8_t pinIndex(0U); pinIndex < min(pinCount, PEDAL_MANAGER_MIN_I2C_ADDRESS); pinIndex++)
    this->pedals[pinIndex] = new VL53L0XPedal(PEDAL_MANAGER_MIN_I2C_ADDRESS + pinIndex, shutPins[pinIndex]);
}

PedalManager::~PedalManager()
{
  for (uint8_t pedalIndex(0U); pedalIndex < PEDAL_MANAGER_MAX_PEDALS; pedalIndex++)
  {
    if (this->pedals[pedalIndex])
    {
      this->pedals[pedalIndex]->stop();
      delete this->pedals[pedalIndex];
      this->pedals[pedalIndex] = 0;
    }
  }
}

Pedal *PedalManager::getPedal(const uint8_t pedalIndex) const
{
  return this->pedals[pedalIndex];
}

void PedalManager::setup() const
{
  for (uint8_t pedalIndex(0U); pedalIndex < PEDAL_MANAGER_MAX_PEDALS; pedalIndex++)
    if (this->pedals[pedalIndex])
      this->pedals[pedalIndex]->start();
}

void PedalManager::update(const bool debug)
{
  for (uint8_t pedalIndex(0U); pedalIndex < PEDAL_MANAGER_MAX_PEDALS; pedalIndex++)
    if (this->pedals[pedalIndex])
      this->pedals[pedalIndex]->measure(debug);
}
