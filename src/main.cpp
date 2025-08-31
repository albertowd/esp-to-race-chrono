#include <hal/gpio_types.h>

#include <Arduino.h>

#include <PedalManager.hpp>
#include <PedalValues.hpp>
#include <PerformanceManager.hpp>

#define DEBUG true
#define MAIN_LED GPIO_NUM_16

/**************************************
 * VIN    GND   SDA   SCL   XAS   SHUT
 *  ^      ^     ^     ^           ^
 * 3V3    GND   D21   D22         D25
 *************************************/

gpio_num_t pedalPins[3] = {GPIO_NUM_25, GPIO_NUM_26, GPIO_NUM_27};
//gpio_num_t pedalPins[2] = {GPIO_NUM_25, GPIO_NUM_26};
//gpio_num_t pedalPins[1] = {GPIO_NUM_25};
PedalManager pedals(pedalPins, 3U);


void loop()
{
  digitalWrite(MAIN_LED, LOW);
  PerformanceManager::instance()->reset();

  pedals.update(DEBUG);

  digitalWrite(MAIN_LED, HIGH);
  PerformanceManager::instance()->measure(true, true);
}

void setup()
{
  pinMode(MAIN_LED, OUTPUT);
  digitalWrite(MAIN_LED, LOW);

  PerformanceManager::instance()->reset();

  Serial.begin(115200);
  // Wait for 1 second to a USB instance
  unsigned long serialTimeout = millis() + 1000;
  while (!Serial && serialTimeout > millis())
  {
    delay(1);
  }
  Serial.println("Initializing ESP To Race Chrono...");

  pedals.setup();

  PerformanceManager::instance()->measure(false, true);
  digitalWrite(MAIN_LED, HIGH);
}
