#ifndef I2C_BUS_H
#define I2C_BUS_H

#include <Arduino.h>
#ifdef ARDUINO
#include <Wire.h>
#endif

#define I2C_SDA 21
#define I2C_SCL 22

class I2CBus {
public:
    static bool begin();
};

#endif
