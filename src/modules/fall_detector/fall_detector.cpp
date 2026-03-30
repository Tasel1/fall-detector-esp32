#include "fall_detector.h"
#include <math.h>

FallDetector::FallDetector() : _sensitivity(2.5f) {}

void FallDetector::setSensitivity(float g) {
    _sensitivity = g;
}

bool FallDetector::processSensorData(float accelX, float accelY, float accelZ) {
    float magnitude = calculateMagnitude(accelX, accelY, accelZ);
    float gForce = magnitude / 9.81f;
    return gForce > _sensitivity;
}

float FallDetector::calculateMagnitude(float accelX, float accelY, float accelZ) {
    return sqrt(accelX * accelX + accelY * accelY + accelZ * accelZ);
}
