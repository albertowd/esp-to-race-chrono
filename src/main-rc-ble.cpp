#include <Arduino.h>

#include <RaceChrono.h>

#include "CANFrame.hpp"

#ifndef DEBUG
#define DEBUG true
#endif

class IgnoreRaceChronoCommands : public RaceChronoBleCanHandler {
  void allowAllPids(uint16_t updateIntervalMs) {}
  void denyAllPids() {}
  void allowPid(uint32_t pid, uint16_t updateIntervalMs) {}
} raceChronoHandler;

void waitForConnection() {
  uint32_t iteration = 0;
  bool lastLineHadNewline = false;

  Serial.print("Waiting for BLE connection...");
  while (!RaceChronoBle.waitForConnection(1000)) {
    Serial.print(".");
    if ((++iteration) % 10 == 0) {
      lastLineHadNewline = true;
      Serial.println();
    } else {
      lastLineHadNewline = false;
    }
  }

  if (!lastLineHadNewline) {
    Serial.println();
  }

  Serial.println("Connected.");
}

void loop()
{
   if (!RaceChronoBle.isConnected()) {
    Serial.println("RaceChrono disconnected!");
    waitForConnection();
  }

  /**
   * For this random example, use the below channels:
   * Clutch % = ID 1, bytestouint(0, 1) * 100 / 255
   * Brake % = ID 1, bytestouint(1, 1) * 100 / 255
   * Accelerator % = ID 1, bytestouint(2, 1) * 100 / 255
   */
  
  CAN::Frame frame(1U);
  frame.setUint8((uint8_t)rand(), 0);
  frame.setUint8((uint8_t)rand(), 1);
  frame.setUint8((uint8_t)rand(), 2);
  Serial.printf("Sending to BLE: %s\n", frame.c_str());
  RaceChronoBle.sendCanData(frame.getId(), frame.c_data() + 4, 3);

  delay(5000);
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

  delay(500);
  RaceChronoBle.setUp("ESP TO RC", &raceChronoHandler);
  RaceChronoBle.startAdvertising();

  Serial.println("BLE is set up, waiting for an incoming connection.");
  waitForConnection();
}
