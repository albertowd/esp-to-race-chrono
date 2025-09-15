#include <Arduino.h>

#include <BatteryHolderMonitor.hpp>

#ifndef DEBUG
#define DEBUG true
#endif

BatteryHolder::Monitor batteryMon;

void loop()
{
  batteryMon.update(DEBUG);
  delay(1000);
}

void setup()
{
  if (DEBUG)
  {
    Serial.begin(115200);
    // Wait for 1 second to a USB instance
    unsigned long serialTimeout = millis() + 1000;
    while (!Serial && serialTimeout > millis())
    {
      delay(1);
    }
  }
  batteryMon.setup();
}
