#include "motion_monitor.h"
#include "../../config.h"

MotionMonitor::MotionMonitor() : _index(0), _stillStartMs(0), _isStill(false) {
    for (int i = 0; i < WINDOW_SIZE; i++) _buffer[i] = 0;
}

void MotionMonitor::update(float magnitude) {
    _buffer[_index] = magnitude;
    _index = (_index + 1) % WINDOW_SIZE;
    
    float var = calculateVariance();
    bool currentlyStill = (var < STILLNESS_VARIANCE);
    
    if (currentlyStill && !_isStill) {
        _stillStartMs = millis();
    } else if (!currentlyStill) {
        _stillStartMs = 0;
    }
    _isStill = currentlyStill;
}

float MotionMonitor::calculateVariance() const {
    float sum = 0;
    for (int i = 0; i < WINDOW_SIZE; i++) sum += _buffer[i];
    float mean = sum / WINDOW_SIZE;
    
    float varSum = 0;
    for (int i = 0; i < WINDOW_SIZE; i++) {
        float diff = _buffer[i] - mean;
        varSum += diff * diff;
    }
    return varSum / WINDOW_SIZE;
}

bool MotionMonitor::isMotionless() const {
    return _isStill;
}

bool MotionMonitor::hasFainted(unsigned long timeoutMs) {
    if (!_isStill || _stillStartMs == 0) return false;
    return (millis() - _stillStartMs) >= timeoutMs;
}

void MotionMonitor::resetFaintTimer() {
    _stillStartMs = millis();
}
