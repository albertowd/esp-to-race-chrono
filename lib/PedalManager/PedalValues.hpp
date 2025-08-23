#ifndef __PEDAL_VALUES_HPP
#define __PEDAL_VALUES_HPP

#include <cstdint>

struct PedalValues
{
public:
  uint16_t currentValue;
  uint16_t maxValue;
  uint16_t minValue;
  uint16_t percValue;
};

#endif // __PEDAL_VALUES_HPP
