#include "imu_sensor.h"

#ifdef ARDUINO
static Adafruit_MPU6050 mpu;
#endif

bool IMUSensor::begin() {
#ifdef ARDUINO
    if (!mpu.begin()) {
        return false;
    }
    
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
#endif
    return true;
}

bool IMUSensor::getSensorData(float &accelX, float &accelY, float &accelZ) {
#ifdef ARDUINO
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    
    accelX = a.acceleration.x;
    accelY = a.acceleration.y;
    accelZ = a.acceleration.z;
#else
    accelX = 0;
    accelY = 0;
    accelZ = 9.81f;
#endif
    return true;
}

float IMUSensor::calculateMagnitude(float accelX, float accelY, float accelZ) {
    return sqrt(accelX * accelX + accelY * accelY + accelZ * accelZ);
}
