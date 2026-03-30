#include <Arduino.h>
#include "config.h"
#include "modules/power/nvs_manager.h"
#include "modules/sensors/i2c_bus.h"
#include "modules/power/power_mgmt.h"
#include "modules/sensors/imu_sensor.h"
#include "modules/sensors/button_sensor.h"
#include "modules/fall_detector/fall_detector.h"
#include "modules/fall_detector/timer.h"
#include "modules/motion_monitor/motion_monitor.h"
#include "modules/ui/display_service.h"
#include "modules/ui/haptic_service.h"
#include "modules/alert_manager/alert_manager.h"

enum class SystemState { MONITORING, PRE_ALERT, FALL_DETECTED, MANUAL_SOS };
SystemState currentState = SystemState::MONITORING;

FallDetector detector;
FallTimer preAlertTimer;
MotionMonitor motionMonitor;
unsigned long lastSensorRead = 0;
unsigned long preAlertStartTime = 0;

void setup() {
    Serial.begin(115200);
    pinMode(2, OUTPUT); 
    I2CBus::begin();
    DisplayService::begin();
    NVSManager::begin();
    IMUSensor::begin();
    ButtonSensor::begin();
    AlertManager::begin();
    DisplayService::showStatus("Monitoring", PowerMgmt::getBatteryPercentage());
}

void loop() {
    unsigned long now = millis();
    
    // ВАЖНО: Обновляем состояние кнопки в каждой итерации
    ButtonSensor::update();

    // Визуализация Heartbeat
    digitalWrite(2, (now / 500) % 2);

    // SOS check (Высокий приоритет)
    if (ButtonSensor::wasSOSPressed()) {
        currentState = SystemState::MANUAL_SOS;
    }

    switch (currentState) {
        case SystemState::MONITORING: {
            if (now - lastSensorRead >= 100) {
                lastSensorRead = now;
                float ax, ay, az;
                if (IMUSensor::getSensorData(ax, ay, az)) {
                    float mag = IMUSensor::calculateMagnitude(ax, ay, az);
                    motionMonitor.update(mag);

                    if (detector.processSensorData(ax, ay, az) || motionMonitor.hasFainted(FAINT_TIMEOUT_MS)) {
                        currentState = SystemState::PRE_ALERT;
                        preAlertTimer.start(PRE_ALERT_DURATION_MS);
                        preAlertStartTime = now;
                        AlertManager::startAlert();
                        ButtonSensor::clear(); 
                    }
                }
            }
            break;
        }
            
        case SystemState::PRE_ALERT: {
            // Отмена только через 1 сек после начала (защита от дребезга симулятора)
            if (now - preAlertStartTime > 1000) {
                if (ButtonSensor::wasPressed()) {
                    AlertManager::stop();
                    currentState = SystemState::MONITORING;
                    motionMonitor.resetFaintTimer();
                    DisplayService::showStatus("Canceled", PowerMgmt::getBatteryPercentage());
                    delay(1500);
                    DisplayService::showStatus("Monitoring", PowerMgmt::getBatteryPercentage());
                    return;
                }
            }

            if (preAlertTimer.isExpired()) {
                AlertManager::stop();
                currentState = SystemState::FALL_DETECTED;
            } else {
                float ratio = 1.0f - ((float)preAlertTimer.remaining() / PRE_ALERT_DURATION_MS);
                AlertManager::updateAlert(ratio);
                DisplayService::showCountdown(preAlertTimer.remaining() / 1000);
            }
            break;
        }

        case SystemState::FALL_DETECTED:
        case SystemState::MANUAL_SOS: {
            DisplayService::showStatus("SOS SENT!", PowerMgmt::getBatteryPercentage());
            delay(3000);
            ButtonSensor::clear(); 
            currentState = SystemState::MONITORING;
            motionMonitor.resetFaintTimer();
            DisplayService::showStatus("Monitoring", PowerMgmt::getBatteryPercentage());
            break;
        }
            
        default: break;
    }
}
