#ifndef POWER_MGMT_H
#define POWER_MGMT_H

#include <Arduino.h>

class PowerMgmt {
public:
    static void goToDeepSleep();
    static float getBatteryVoltage();
    static int getBatteryPercentage();
};

#endif
