#ifndef NVS_MANAGER_H
#define NVS_MANAGER_H

#include <Arduino.h>
#ifdef ARDUINO
#include <Preferences.h>
#endif

class NVSManager {
public:
    static bool begin();
    static bool saveContacts(const uint8_t* data, size_t len);
    static size_t loadContacts(uint8_t* buffer, size_t maxLen);
    static bool saveSettings(float sensitivity, uint16_t timerVal);
    static bool loadSettings(float &sensitivity, uint16_t &timerVal);

private:
#ifdef ARDUINO
    static Preferences preferences;
#endif
};

#endif
