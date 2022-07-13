// https://github.com/palmmaximilian/ReactNativeArduinoBLE
// https://github.com/palmmaximilian/ReactNativeArduinoBLE

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include "modules/hardware_uuid.h"
#include "modules/e2prom_read_write.h"
#include "modules/e2prom_read_write_basic.h"

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
        Serial.println("Connected");
    };

    void onDisconnect(BLEServer *pServer)
    {
        Serial.println("Disconnected");
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

void setup()
{
  
    Serial.begin(115200);
    Serial.println("Test___111111");
    // Create the BLE Device
    BLEDevice::init("BLEExample");
    // Create the BLE Server
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());
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

    message_characteristic->setValue("Message one");
    message_characteristic->setCallbacks(new CharacteristicsCallbacks());

    box_characteristic->setValue("0");
    box_characteristic->setCallbacks(new CharacteristicsCallbacks());

    Serial.println("Waiting for a client connection to notify...");
    Serial.println(getMacAddress());
}

void loop()
{

    e2promInitiate();

    Serial.println( "   =====   padlock   =====   11111" ) ; 
    e2promWriteWorks("padlock", "padlock_____1111111111222222222233333333334444444448_____padlock" );
    e2promReadWorks("padlock");
    Serial.println();

    Serial.println( "   =====   tenant   =====    11111") ; 
    // e2promWriteWorks("tenant", "tenant_____22222222223333333333444444444455111111111_____tenant");
    e2promWriteWorks("tenant", "tenant_____ABC_____tenant");
    e2promReadWorks("tenant");
    Serial.println();

    // Serial.println( "   =====   aes_01   =====    11111" ) ; 
    // e2promWriteWorks("aes_01", "aes_01_____iiiiiiiii11111111112222222222iii444444444_____aes_01" );
    // e2promReadWorks("aes_01");
    // Serial.println();

    Serial.println( "   =====   aes_02   =====    11111" ) ; 
    e2promWriteWorks("aes_02", "aes_02_____444444444iiiiiiiii11111111112222222222iii8_____aes_02??????????" );
    e2promReadWorks("aes_02");
    Serial.println();

    Serial.println( "   =====   padlock   =====    22222" ) ; 
    e2promReadWorks("padlock");
    Serial.println();

    Serial.println( "   =====   tenant   =====    22222" ) ; 
    e2promReadWorks("tenant");
    Serial.println();

    Serial.println( "   =====   aes_01   =====    22222" ) ; 
    e2promReadWorks("aes_01");
    Serial.println();
    
    Serial.println( "   =====   aes_02   =====    22222" ) ; 
    e2promReadWorks("aes_02");
    Serial.println();

     

    while ( true ) {

        message_characteristic->setValue("Message one");
        message_characteristic->notify();

        Serial.println("Message one - Sent");
        Serial.println(addx(100, -80));
        delay(1000);

        message_characteristic->setValue("Message Two");
        message_characteristic->notify();
        
        Serial.println("Message Two - Sent");
        Serial.println(getMacAddress());
        delay(1000);
    }
}