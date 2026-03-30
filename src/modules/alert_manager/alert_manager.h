#ifndef ALERT_MANAGER_H
#define ALERT_MANAGER_H

#include <Arduino.h>

class AlertManager {
public:
    static bool begin();
    static void startAlert();
    static void updateAlert(float ratio);
    static void stop();
    static void initiateAlertSequence();
};

#endif
