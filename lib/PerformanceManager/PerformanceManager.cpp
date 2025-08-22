#include <Arduino.h>
#include "PerformanceManager.hpp"

PerformanceManager PerformanceManager::singleton;

PerformanceManager* PerformanceManager::instance() {
  return &PerformanceManager::singleton;
}

unsigned long PerformanceManager::getElapsedTime() const {
  return this->elapsedMs;
}

void PerformanceManager::measure(bool shouldDelay, bool debug) {
  this->elapsedMs = millis() - this->startMs;
  if (this->elapsedMs) {
    Serial.printf("Performance: %lu Hz ~ %lu ms (%lu ms)\n", 1000 / this->elapsedMs, this->elapsedMs, this->targetMs);
  }
  if (this->targetMs > this->elapsedMs) {
    delay(this->targetMs - this->elapsedMs + 1000);
  } else {
    delay(1000);
  }
}

void PerformanceManager::reset() {
  this->startMs = millis();
}

void PerformanceManager::setTargetHz(unsigned long targetHz) {
  this->targetMs = 1000 / targetHz;
}
