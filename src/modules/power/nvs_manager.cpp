#include "nvs_manager.h"

#ifdef ARDUINO
Preferences NVSManager::preferences;
#endif

bool NVSManager::begin() {
#ifdef ARDUINO
    return preferences.begin("fallwatch", false);
#else
    return true;
#endif
}

bool NVSManager::saveContacts(const uint8_t* data, size_t len) {
#ifdef ARDUINO
    if (len > 0) {
        return preferences.putBytes("contacts", data, len) == len;
    }
#endif
    return false;
}

size_t NVSManager::loadContacts(uint8_t* buffer, size_t maxLen) {
#ifdef ARDUINO
    return preferences.getBytes("contacts", buffer, maxLen);
#else
    return 0;
#endif
}

bool NVSManager::saveSettings(float sensitivity, uint16_t timerVal) {
#ifdef ARDUINO
    size_t written = 0;
    written += preferences.putFloat("sensitivity", sensitivity);
    written += preferences.putUShort("timer_val", timerVal);
    return written > 0;
#else
    return true;
#endif
}

bool NVSManager::loadSettings(float &sensitivity, uint16_t &timerVal) {
#ifdef ARDUINO
    sensitivity = preferences.getFloat("sensitivity", 2.5f);
    timerVal = preferences.getUShort("timer_val", 60);
#else
    sensitivity = 2.5f;
    timerVal = 60;
#endif
    return true;
}
