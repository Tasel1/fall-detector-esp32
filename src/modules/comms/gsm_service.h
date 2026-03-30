#ifndef GSM_SERVICE_H
#define GSM_SERVICE_H

#include <Arduino.h>

class GSMService {
public:
    static bool begin();
    static bool sendSMS(const char* phoneNumber, const char* message);
    static bool makeVoiceCall(const char* phoneNumber);
    static bool playTTSMessage(const char* message);
    static String formatSMSPayload(float lat, float lng);
    static void setSOSLockout(bool locked);
    static bool isSOSLocked();
};

#endif
