#ifndef BLE_SERVICE_H
#define BLE_SERVICE_H

#include <Arduino.h>
#ifdef ARDUINO
#include <NimBLEDevice.h>
#endif

class MyBLEService {
public:
    static void begin();
    static bool isConnected();

private:
#ifdef ARDUINO
    class MyServerCallbacks : public NimBLEServerCallbacks {
        void onConnect(NimBLEServer* pServer);
        void onDisconnect(NimBLEServer* pServer);
    };
    
    class ConfigCallbacks : public NimBLECharacteristicCallbacks {
        void onWrite(NimBLECharacteristic* pCharacteristic);
    };
#endif
};

#endif
