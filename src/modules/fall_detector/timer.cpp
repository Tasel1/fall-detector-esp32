#include "timer.h"

FallTimer::FallTimer() : _startMs(0), _durationMs(0), _running(false) {}

void FallTimer::start(unsigned long durationMs) {
    _startMs = millis();
    _durationMs = durationMs;
    _running = true;
}

bool FallTimer::isExpired() const {
    if (!_running) return false;
    return (millis() - _startMs) >= _durationMs;
}

unsigned long FallTimer::remaining() const {
    if (!_running) return 0;
    unsigned long elapsed = millis() - _startMs;
    if (elapsed >= _durationMs) return 0;
    return _durationMs - elapsed;
}

void FallTimer::stop() {
    _running = false;
}
