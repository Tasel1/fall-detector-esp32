#include "power_mgmt.h"

#define BATT_ADC_PIN 35
#define VOLTAGE_DIVIDER_RATIO 2.0f

void PowerMgmt::goToDeepSleep() {
#ifdef ARDUINO
    // Enable wakeup by EXT0 (MPU6050 INT pin on GPIO 33)
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_33, 1); // 1 = High, 0 = Low depending on MPU6050 config
    
    // Enable wakeup by button (GPIO 4)
    esp_sleep_enable_ext1_wakeup(1ULL << GPIO_NUM_4, ESP_EXT1_WAKEUP_ALL_LOW);
    
    esp_deep_sleep_start();
#endif
}

float PowerMgmt::getBatteryVoltage() {
    int raw = analogRead(BATT_ADC_PIN);
    return (raw / 4095.0f) * 3.3f * VOLTAGE_DIVIDER_RATIO;
}

int PowerMgmt::getBatteryPercentage() {
    float voltage = getBatteryVoltage();
    int percentage = (int)((voltage - 3.3f) / (4.2f - 3.3f) * 100);
    if (percentage > 100) percentage = 100;
    if (percentage < 0) percentage = 0;
    return percentage;
}
