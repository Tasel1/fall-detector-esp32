#ifndef TIMER_H
#define FALL_TIMER_H

#if defined(ARDUINO) || defined(UNIT_TEST)
#include <Arduino.h>
#else
#include <stdint.h>
extern "C" unsigned long millis();
#endif

class FallTimer {
public:
    FallTimer();
    void start(unsigned long durationMs);
    bool isExpired() const;
    unsigned long remaining() const;
    void stop();

private:
    unsigned long _startMs;
    unsigned long _durationMs;
    bool _running;
};

#endif
