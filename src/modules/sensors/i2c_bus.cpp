#include "i2c_bus.h"

bool I2CBus::begin() {
#ifdef ARDUINO
    return Wire.begin(I2C_SDA, I2C_SCL);
#else
    return true;
#endif
}
