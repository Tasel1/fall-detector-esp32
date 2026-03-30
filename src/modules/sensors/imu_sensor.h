#ifndef IMU_SENSOR_H
#define IMU_SENSOR_H

#include <Arduino.h>
#ifdef ARDUINO
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#endif

class IMUSensor {
public:
    static bool begin();
    static bool getSensorData(float &accelX, float &accelY, float &accelZ);
    static float calculateMagnitude(float accelX, float accelY, float accelZ);
};

#endif
