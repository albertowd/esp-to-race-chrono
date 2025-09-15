#include <Arduino.h>
#include <Wire.h>

#include <I2CScanner.hpp>

#ifndef DEBUG
#define DEBUG true
#endif

void loop()
{
  I2CScanner::probe();
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
  Wire.begin();
}
