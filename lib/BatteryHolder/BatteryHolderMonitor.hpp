#ifndef __BATTERY_HOLDER_MONITOR_HPP
#define __BATTERY_HOLDER_MONITOR_HPP

#include <cstdint>

namespace BatteryHolder
{
#define BATTERY_HOLDER_PIN (uint8_t)3U
#define BATTERY_MAX_VALUE 4096U
#define BATTERY_VOLTAGE 3.7f
#define BATTERY_MULTIPLIER 2.0f

  class Monitor
  {
  private:
    float lastVoltage;
    uint16_t lastValue;
    uint8_t batteryPin;

  public:
    Monitor(uint8_t batteryPin = BATTERY_HOLDER_PIN);

    float getVoltage() const;
    uint16_t getValue() const;
    void setup() const;
    void update(bool debug = false);
  };
}

#endif
