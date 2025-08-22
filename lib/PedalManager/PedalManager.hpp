#ifndef __PEDAL_MANAGER_HPP
#define __PEDAL_MANAGER_HPP

  #include "Adafruit_VL53L0X.h"

  #ifndef PEDAL_MANAGER_MIN_I2C_ADDRESS
  /**
   * First I2C address used by the Pedal Manager sensors.
   */
  #define PEDAL_MANAGER_MIN_I2C_ADDRESS (uint8_t)41U
  #endif

  /**
   * Manager to use one to three VL53L0X sensors
   * readings.
   */
  class PedalManager {
    private:
      /**
       * Sensor array.
       */
      Adafruit_VL53L0X* sensors;

      /**
       * Sensor pins (for each shut command, they must be digital).
       */
      uint8_t* pins;

      /**
       * How many sensors it is managing.
       */
      uint8_t sensorCount;

      /**
       * Privated constructor to avoid calling.
       */
      PedalManager(const PedalManager &pedalManager) {}

    public:
      /**
       * Default constructor.
       * @param shutA Pin for the first sensor shut down (default D5).
       * @param shutB Pin for the second sensor shut down (default D6).
       * @param shutC Pin for the third sensor shut down (default D7).
       */
      PedalManager(const uint8_t shutA = D5, const uint8_t shutB = 0, const uint8_t shutC = 0);

      /**
       * Default destructor.
       */
      ~PedalManager();

      /**
       * Returns the last measurement for the 
       * required sensor.
       * @param sensorIndex Sensor A = 0, B = 1 & C = 2
       * @param debug If it should debug measuremente informations.
       * @return The value of the last measurement.
       */
      uint16_t getMeasurement(const uint8_t sensorIndex, bool debug = false) const;

      /**
       * Method to setup all the sensors one at a time.
       */
      void setup() const;

      /**
       * Method to update the measurement, as needed.
       */
      void update(bool debug = false);
  };

#endif // __PEDAL_MANAGER_HPP
