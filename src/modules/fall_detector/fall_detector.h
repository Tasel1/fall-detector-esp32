#ifndef FALL_DETECTOR_H
#define FALL_DETECTOR_H

#if defined(ARDUINO) || defined(UNIT_TEST)
#include <Arduino.h>
#else
#include <stdint.h>
#include <math.h>
#endif

class FallDetector {
public:
    FallDetector();
    void setSensitivity(float g);
    bool processSensorData(float accelX, float accelY, float accelZ);
    static float calculateMagnitude(float accelX, float accelY, float accelZ);

private:
    float _sensitivity;
};

#endif
