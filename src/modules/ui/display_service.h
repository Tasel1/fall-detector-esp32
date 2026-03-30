#ifndef DISPLAY_SERVICE_H
#define DISPLAY_SERVICE_H

#include <Arduino.h>
#ifdef ARDUINO
#include <Adafruit_SSD1306.h>
#endif

class DisplayService {
public:
    static bool begin();
    static void showStatus(const char* status, int battery);
    static void showCountdown(int seconds);
    static void clear();

private:
#ifdef ARDUINO
    static Adafruit_SSD1306 display;
#endif
};

#endif
