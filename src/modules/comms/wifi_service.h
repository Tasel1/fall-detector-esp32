#ifndef WIFI_SERVICE_H
#define WIFI_SERVICE_H

#include <Arduino.h>
#ifdef ARDUINO
#include <WiFi.h>
#endif

class WiFiService {
public:
    static void begin(const char* ssid, const char* password);
    static bool isConnected();
    static void stop();
};

#endif
