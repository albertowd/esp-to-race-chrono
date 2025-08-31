#ifndef __PEDAL_HPP
#define __PEDAL_HPP

#include <cstdint>
#include <hal/gpio_types.h>

#include "PedalValues.hpp"

class Pedal
{
private:
  Pedal() = delete;
  Pedal(const Pedal &otherPedal) = delete;

protected:
  /**
   * Flag to indicate if it is ranging.
   */
  bool ranging;

  /**
   * Pin to shut the sensor.
   */
  gpio_num_t shutPin;

  /**
   * Last measurements.
   */
  PedalValues values;

  /**
   * Unique I2C address.
   */
  uint8_t i2CAddress;

public:
  Pedal(const uint8_t i2CAddress, const gpio_num_t shutPin);
  ~Pedal();

  bool isRanging() const;
  PedalValues getValues() const;
  virtual void measure(const bool debug = false) = 0;
  virtual void start(const bool debug = false) = 0;
  virtual void stop() = 0;
};

#endif // __PEDAL_HPP
