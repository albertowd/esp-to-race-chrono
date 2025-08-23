#ifndef __PEDAL_MANAGER_HPP
#define __PEDAL_MANAGER_HPP

#include <cstdint>
#include <hal/gpio_types.h>

#include "Pedal.hpp"

#ifndef PEDAL_MANAGER_MIN_I2C_ADDRESS
/**
 * First I2C address used by the Pedal Manager sensors.
 */
#define PEDAL_MANAGER_MIN_I2C_ADDRESS (uint8_t)41U
#endif

#ifndef PEDAL_MANAGER_MAX_PEDALS
/**
 * Define the max number of pedal sensors.
 */
#define PEDAL_MANAGER_MAX_PEDALS (uint8_t)3U
#endif

/**
 * Manager to use one to three VL53L0X sensors
 * readings.
 */
class PedalManager
{
private:
  /**
   * Pedals array.
   */
  Pedal *pedals[PEDAL_MANAGER_MAX_PEDALS];

  /**
   * Privated constructor to avoid calling.
   */
  PedalManager(const PedalManager &pedalManager) {}

public:
  /**
   * Constructor with sensor shut pins.
   * @param shutA Pin for the first sensor shut down (default GPIO_NUM_25).
   * @param shutB Pin for the second sensor shut down (default GPIO_NUM_NC).
   * @param shutC Pin for the third sensor shut down (default GPIO_NUM_NC).
   */
  PedalManager(const gpio_num_t* shutPins, const uint8_t pinCount);

  /**
   * Default destructor.
   */
  ~PedalManager();

  /**
   * Returns the info for the required pedal.
   * @param pedalIndex Sensor A = 0U, B = 1U & C = 2U
   * @return The Pedal pointer.
   */
  Pedal *getPedal(const uint8_t pedalIndex) const;

  /**
   * Method to setup all the sensors one at a time.
   */
  void setup() const;

  /**
   * Method to update the measurement, as needed.
   * @param debug If it should debug measuremente informations.
   */
  void update(const bool debug = false);
};

#endif // __PEDAL_MANAGER_HPP
