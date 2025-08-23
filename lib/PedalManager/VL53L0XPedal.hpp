#ifndef __VL53L0X_PEDAL_HPP
#define __VL53L0X_PEDAL_HPP

#include <hal/gpio_types.h>

#include "Adafruit_VL53L0X.h"

#include "Pedal.hpp"

class VL53L0XPedal : public Pedal
{
private:
  Adafruit_VL53L0X sensor;
  VL53L0X_RangingMeasurementData_t lastMeasurement;

  VL53L0XPedal();
  VL53L0XPedal(const VL53L0XPedal &otherPedal) = delete;

public:
  VL53L0XPedal(const uint8_t i2CAddress, const gpio_num_t shutPin);
  ~VL53L0XPedal();

  void configure(const bool debug = false);
  void measure(const bool debug = false) override;
  void start(const bool debug = false) override;
  void stop() override;
};

#endif // __VL53L0X_PEDAL_HPP
