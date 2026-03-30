#include "ble_service.h"
#include "modules/power/nvs_manager.h"

#define SERVICE_UUID "FD01"
#define CHAR_CONTACTS_UUID "FD11"

static bool deviceConnected = false;

#ifdef ARDUINO
void MyBLEService::MyServerCallbacks::onConnect(NimBLEServer* pServer) {
    deviceConnected = true;
}

void MyBLEService::MyServerCallbacks::onDisconnect(NimBLEServer* pServer) {
    deviceConnected = false;
    NimBLEDevice::startAdvertising();
}

void MyBLEService::ConfigCallbacks::onWrite(NimBLECharacteristic* pCharacteristic) {
    std::string value = pCharacteristic->getValue();
    if (pCharacteristic->getUUID().toString() == CHAR_CONTACTS_UUID) {
        NVSManager::saveContacts((const uint8_t*)value.data(), value.length());
    }
}
#endif

void MyBLEService::begin() {
#ifdef ARDUINO
    NimBLEDevice::init("FallWatch-ESP32");
    NimBLEServer* pServer = NimBLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

    NimBLEService* pConfigService = pServer->createService(SERVICE_UUID);
    NimBLECharacteristic* pContactsChar = pConfigService->createCharacteristic(
        CHAR_CONTACTS_UUID,
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE
    );
    pContactsChar->setCallbacks(new ConfigCallbacks());

    pConfigService->start();
    NimBLEDevice::startAdvertising();
#endif
}

bool MyBLEService::isConnected() {
    return deviceConnected;
}
