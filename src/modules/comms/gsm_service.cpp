#include "gsm_service.h"

// Define SIM800L pins for ESP32
#define MODEM_TX 17
#define MODEM_RX 16
#define MODEM_BAUD 9600

static bool _sosLocked = false;

bool GSMService::begin() {
#ifdef ARDUINO
    Serial2.begin(MODEM_BAUD, SERIAL_8N1, MODEM_RX, MODEM_TX);
#endif
    return true;
}

bool GSMService::sendSMS(const char* phoneNumber, const char* message) {
    Serial.print("Sending SMS to ");
    Serial.println(phoneNumber);
    Serial.println(message);
    return true;
}

bool GSMService::makeVoiceCall(const char* phoneNumber) {
    Serial.print("Calling ");
    Serial.println(phoneNumber);
    return true;
}

bool GSMService::playTTSMessage(const char* message) {
    Serial.print("Playing TTS: ");
    Serial.println(message);
    return true;
}

String GSMService::formatSMSPayload(float lat, float lng) {
    String payload = "[FallWatch] EMERGENCY! Fall/Faint detected. Location: https://maps.google.com/?q=";
    payload += String(lat, 6);
    payload += ",";
    payload += String(lng, 6);
    return payload;
}

void GSMService::setSOSLockout(bool locked) {
    _sosLocked = locked;
}

bool GSMService::isSOSLocked() {
    return _sosLocked;
}
