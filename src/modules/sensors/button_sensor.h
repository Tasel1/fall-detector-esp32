#ifndef BUTTON_SENSOR_H
#define BUTTON_SENSOR_H

#include <Arduino.h>

class ButtonSensor {
public:
    static void begin();
    static void update(); // Добавляем метод обновления
    static bool isPressed();
    static bool wasPressed();
    static bool wasLongPressed();
    static bool wasSOSPressed();
    static void clear();

private:
#ifdef ARDUINO
    static void IRAM_ATTR handleInterrupt();
#else
    static void handleInterrupt();
#endif
};

#endif
