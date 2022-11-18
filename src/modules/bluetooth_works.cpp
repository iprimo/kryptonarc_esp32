// https://github.com/palmmaximilian/ReactNativeArduinoBLE
// https://github.com/palmmaximilian/ReactNativeArduinoBLE

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include "modules/hardware_uuid.h"
#include "modules/e2prom_read_write.h"

// BLE SECTION
BLEServer *pServer = NULL;

BLECharacteristic *message_characteristic = NULL;
BLECharacteristic *box_characteristic = NULL;

String boxValue = "0";
// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID "5e6df2dd-e7c5-4ce3-aa8d-6c7a5871fc51"

#define MESSAGE_CHARACTERISTIC_UUID "6ec0962b-fd7c-4a91-9d21-bdf4c1266136"
#define BOX_CHARACTERISTIC_UUID "e3badad0-ebba-4059-9b2e-b8a959d95781"

class MyServerCallbacks : public BLEServerCallbacks
{
    void onConnect(BLEServer *pServer)
    {
        Serial.println("Submodule: Connected");
    };

    void onDisconnect(BLEServer *pServer)
    {
        Serial.println("Submodule: Disconnected");
    }
};

class CharacteristicsCallbacks : public BLECharacteristicCallbacks
{
    void onWrite(BLECharacteristic *pCharacteristic)
    {
        Serial.print("Value Written ");
        Serial.println(pCharacteristic->getValue().c_str());

        if (pCharacteristic == box_characteristic)
        {
            boxValue = pCharacteristic->getValue().c_str();
            box_characteristic->setValue(const_cast<char *>(boxValue.c_str()));
            box_characteristic->notify();
        }
    }
};



void bluetoothInitiate() {
  
    Serial.println("Submodule: Test___000001444");
    // Create the BLE Device
    BLEDevice::init("BLEExample");
    // Create the BLE Server
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());
    // uint16_t mtu = 128;
    // BLEDevice::setMTU(mtu);    
    // Create the BLE Service
    BLEService *pService = pServer->createService(SERVICE_UUID);
    delay(100);

    // Create a BLE Characteristic
    message_characteristic = pService->createCharacteristic(
        MESSAGE_CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ |
            BLECharacteristic::PROPERTY_WRITE |
            BLECharacteristic::PROPERTY_NOTIFY |
            BLECharacteristic::PROPERTY_INDICATE);

    box_characteristic = pService->createCharacteristic(
        BOX_CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ |
            BLECharacteristic::PROPERTY_WRITE |
            BLECharacteristic::PROPERTY_NOTIFY |
            BLECharacteristic::PROPERTY_INDICATE);

    // Start the BLE service
    pService->start();

    // Start advertising
    pServer->getAdvertising()->start();

    message_characteristic->setValue("Submodule 01 : Message one");
    message_characteristic->setCallbacks(new CharacteristicsCallbacks());

    box_characteristic->setValue("0");
    box_characteristic->setCallbacks(new CharacteristicsCallbacks());

    Serial.println("Submodule: Waiting for a client connection to notify...");
}


void bluetoothWorks() {

        message_characteristic->setValue("Submodule 11 : Message one");
        message_characteristic->notify();
        Serial.println("Submodule: Message one - Sent");
        delay(1000);

        message_characteristic->setValue("Submodule 12 : Message Two");
        message_characteristic->notify();
        Serial.println("Submodule: Message Two - Sent");
        delay(1000);
    }








