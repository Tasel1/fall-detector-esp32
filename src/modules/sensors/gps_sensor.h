#ifndef GPS_SENSOR_H
#define GPS_SENSOR_H

#include <Arduino.h>
#ifdef ARDUINO
#include <TinyGPS++.h>
#endif

class GPSSensor {
public:
    static void begin();
    static bool getCoordinates(String &coords);
    static void update();

private:
#ifdef ARDUINO
    static TinyGPSPlus gps;
#endif
};

#endif
