#ifndef HAPTIC_SERVICE_H
#define HAPTIC_SERVICE_H

#include <Arduino.h>

class HapticService {
public:
    static void begin();
    static void playAlert();
    static void playConfirmation();
    static void stop();

private:
    static const int buzzerPin = 13;
    static const int motorPin = 12;
};

#endif
