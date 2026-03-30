#include "alert_manager.h"
#include "../../config.h"
#include "../comms/gsm_service.h"

bool AlertManager::begin() {
#ifdef ARDUINO
    // Initial configuration
    ledcSetup(BUZZER_PWM_CHAN, BUZZER_FREQ_START, 8); 
#endif
    return true;
}

void AlertManager::startAlert() {
    Serial.println("Audio Alert Started");
#ifdef ARDUINO
    ledcAttachPin(BUZZER_PIN, BUZZER_PWM_CHAN);
    ledcWriteTone(BUZZER_PWM_CHAN, BUZZER_FREQ_START);
#endif
}

void AlertManager::updateAlert(float ratio) {
    if (ratio < 0) ratio = 0;
    if (ratio > 1.0f) ratio = 1.0f;
    
#ifdef ARDUINO
    uint32_t freq = BUZZER_FREQ_START + (uint32_t)((BUZZER_FREQ_END - BUZZER_FREQ_START) * ratio);
    ledcWriteTone(BUZZER_PWM_CHAN, freq);
    
    uint32_t duty = 32 + (uint32_t)((128 - 32) * ratio);
    ledcWrite(BUZZER_PWM_CHAN, duty);
#endif
}

void AlertManager::stop() {
    Serial.println("Audio Alert Stopped");
#ifdef ARDUINO
    ledcWriteTone(BUZZER_PWM_CHAN, 0);
    ledcWrite(BUZZER_PWM_CHAN, 0);
    ledcDetachPin(BUZZER_PIN);
    // Force pin to LOW to be absolutely sure
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, LOW);
#endif
}

void AlertManager::initiateAlertSequence() {
    Serial.println("Starting Emergency Alert Sequence...");
    
    for (int i = 0; i < 2; i++) {
        char msg[64];
        snprintf(msg, sizeof(msg), "Attempting call to 112 (Attempt %d)...", i + 1);
        Serial.println(msg);
        if (GSMService::makeVoiceCall("112")) {
            GSMService::playTTSMessage("Emergency alert. Fall detected.");
            delay(10000); 
        }
    }
    
    Serial.println("Proceeding to personal contacts...");
    String payload = GSMService::formatSMSPayload(0.0f, 0.0f);
    GSMService::sendSMS("+1234567890", payload.c_str());
}
