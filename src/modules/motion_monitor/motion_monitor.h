#ifndef MOTION_MONITOR_H
#define MOTION_MONITOR_H

#if defined(ARDUINO) || defined(UNIT_TEST)
#include <Arduino.h>
#else
#include <stdint.h>
extern "C" unsigned long millis();
#endif

#define WINDOW_SIZE 10

class MotionMonitor {
public:
    MotionMonitor();
    void update(float magnitude);
    bool isMotionless() const;
    bool hasFainted(unsigned long timeoutMs);
    void resetFaintTimer();

private:
    float _buffer[WINDOW_SIZE];
    int _index;
    unsigned long _stillStartMs;
    bool _isStill;
    
    float calculateVariance() const;
};

#endif
