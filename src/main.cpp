#include <hal/gpio_types.h>

#include <Arduino.h>

#include <PedalManager.hpp>
#include <PedalValues.hpp>
#include <PerformanceManager.hpp>

#define DEBUG true

/**************************************
 * VIN    GND   SDA   SCL   XAS   SHUT
 *  ^      ^     ^     ^           ^
 * 3V3    GND   D21   D22         D25
 *************************************/

gpio_num_t pedalPins[1] = {GPIO_NUM_25};
PedalManager pedals(pedalPins, 1U);

void loop() {
    digitalWrite(LED_BUILTIN, LOW);
    PerformanceManager::instance()->reset();

    pedals.update(DEBUG);
    PedalValues pedalA = pedals.getPedal(0U)->getValues();

    digitalWrite(LED_BUILTIN, HIGH);
    PerformanceManager::instance()->measure(true, false);
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  PerformanceManager::instance()->reset();

  Serial.begin(115200);
  // Wait for 1 second to a USB instance
  unsigned long serialTimeout = millis() + 1000;
  while (!Serial && serialTimeout > millis()) { delay(1); }

  pedals.setup();

  PerformanceManager::instance()->measure(false, true);
  digitalWrite(LED_BUILTIN, HIGH);
}
