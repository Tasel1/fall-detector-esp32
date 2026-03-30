#include "gps_sensor.h"

#define GPS_TX 27
#define GPS_RX 26
#define GPS_BAUD 9600

#ifdef ARDUINO
TinyGPSPlus GPSSensor::gps;
#endif

void GPSSensor::begin() {
#ifdef ARDUINO
    Serial1.begin(GPS_BAUD, SERIAL_8N1, GPS_RX, GPS_TX);
#endif
}

void GPSSensor::update() {
#ifdef ARDUINO
    while (Serial1.available() > 0) {
        gps.encode(Serial1.read());
    }
#endif
}

bool GPSSensor::getCoordinates(String &coords) {
#ifdef ARDUINO
    if (gps.location.isValid()) {
        coords = "https://maps.google.com/?q=";
        coords += String(gps.location.lat(), 6);
        coords += ",";
        coords += String(gps.location.lng(), 6);
        return true;
    }
#endif
    coords = "Coordinates unavailable";
    return false;
}
