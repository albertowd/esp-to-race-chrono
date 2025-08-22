#include <Arduino.h>

#ifndef PERFORMANCE_MANAGER_DEFAULT_HZ
  #define PERFORMANCE_MANAGER_DEFAULT_HZ (uint32)33U
#endif

/**
 * Manager to keep the processing time stable.
 */
class PerformanceManager {
  private:
    /**
     * Elapsed milliseconds measured
     * atfer the last reset.
     */
    unsigned long elapsedMs;

    /**
     * Start milliseconds from the
     * last reset.
     */
    unsigned long startMs;

    /**
     * Target milliseconds to delay
     * on measurement (targetMs * Hz = 1s)
     */
    unsigned long targetMs;

    /**
     * Singleton instance.
     */
    static PerformanceManager singleton;

    /**
     * Privated constructor to avoid calling.
     */
    PerformanceManager(): elapsedMs(1000U / PERFORMANCE_MANAGER_DEFAULT_HZ), startMs(0), targetMs(1000U / PERFORMANCE_MANAGER_DEFAULT_HZ) {}

    /**
     * Privated constructor to avoid calling.
     */
    PerformanceManager(const PerformanceManager &pedalManager) {}

    /**
     * Privated destructor to avoid calling.
     */
    ~PerformanceManager() {}

  public:
    /**
     * Static method to access the singleton.
     */
    static PerformanceManager* instance();

    /**
     * Returns the last elapsed time.
     * @returns The last measured elapsed
     * time in milliseconds.
     */
    unsigned long getElapsedTime() const;

    /**
     * Measure the elapsed time from the last
     * reset and delay, if required.
     * @param shouldDelay Delay to the target Hz.
     * @param debug Debug flag on measurement.
     */
    void measure(bool shouldDelay = true, bool debug = false);

    /**
     * Resets the timer, for the next measurement.
     */
    void reset();

    /**
     * Sets the new target Hz, it wil divide 1000
     * by it to achieve the target delay in
     * milliseconds.
     * @param targetHz The required Hz to achieve.
     */
    void setTargetHz(unsigned long targetHz);
};
