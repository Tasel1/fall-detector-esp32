#include "haptic_service.h"

void HapticService::begin() {
    pinMode(buzzerPin, OUTPUT);
    pinMode(motorPin, OUTPUT);
}

void HapticService::playAlert() {
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(motorPin, HIGH);
}

void HapticService::playConfirmation() {
    digitalWrite(motorPin, HIGH);
    delay(200);
    digitalWrite(motorPin, LOW);
}

void HapticService::stop() {
    digitalWrite(buzzerPin, LOW);
    digitalWrite(motorPin, LOW);
}
