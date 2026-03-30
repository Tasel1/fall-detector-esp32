#include "button_sensor.h"
#include "../../config.h"

#define BUTTON_PIN 18

static unsigned long pressStartMs = 0;
static bool clickFlag = false;
static bool sosFlag = false;
static bool lastState = HIGH;

void ButtonSensor::begin() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    lastState = digitalRead(BUTTON_PIN);
    clear();
}

void ButtonSensor::update() {
    bool currentState = digitalRead(BUTTON_PIN);
    unsigned long now = millis();

    // Обработка нажатия (HIGH -> LOW)
    if (lastState == HIGH && currentState == LOW) {
        pressStartMs = now;
    }
    
    // Обработка удержания
    if (currentState == LOW) {
        if (pressStartMs != 0 && (now - pressStartMs >= SOS_LONG_PRESS_MS)) {
            if (!sosFlag) {
                sosFlag = true; // SOS взводится только один раз за нажатие
            }
        }
    }

    // Обработка отпускания (LOW -> HIGH)
    if (lastState == LOW && currentState == HIGH) {
        unsigned long duration = now - pressStartMs;
        // Если это был короткий клик и SOS еще не сработал
        if (duration > 50 && duration < SOS_LONG_PRESS_MS && !sosFlag) {
            clickFlag = true;
        }
        pressStartMs = 0;
    }

    lastState = currentState;
}

bool ButtonSensor::wasPressed() {
    if (clickFlag) {
        clickFlag = false;
        return true;
    }
    return false;
}

bool ButtonSensor::wasSOSPressed() {
    if (sosFlag) {
        sosFlag = false;
        return true;
    }
    return false;
}

bool ButtonSensor::isPressed() {
    return digitalRead(BUTTON_PIN) == LOW;
}

void ButtonSensor::clear() {
    pressStartMs = 0;
    clickFlag = false;
    sosFlag = false;
}
