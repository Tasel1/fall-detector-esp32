#include "wifi_service.h"

void WiFiService::begin(const char* ssid, const char* password) {
#ifdef ARDUINO
    if (ssid == nullptr || strlen(ssid) == 0) return;
    WiFi.begin(ssid, password);
#endif
}

bool WiFiService::isConnected() {
#ifdef ARDUINO
    return WiFi.status() == WL_CONNECTED;
#else
    return false;
#endif
}

void WiFiService::stop() {
#ifdef ARDUINO
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
#endif
}
