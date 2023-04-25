#include "HardwareSerial.h"
#include "BLEDevice.h"
#include "BLEServer.h"
#include "BLEUtils.h"
#include "BLE2902.h"

#include "iostream"    // std::cout
#include "algorithm"    // std::min
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "modules/servo.hpp"
#include "modules/string_works.hpp"
#include "modules/hardware_info_works.hpp"
#include "modules/system_structs.cpp"
#include "modules/encryption_works.hpp"
#include "modules/e2prom_works.hpp"


SOFTWARE_GLOBAL_PARAMETERS_FIXED software_parameters_fixed;
DEVICE_GLOBAL_HARDWARE_PARAMETERS_FIXED constrcut_MCU_ID_fixed;
E2PROM_STORED_DATA_FIXED e2prom_variables;
BROADCAST_GLOBAL_VAR broadcast_global_variables;



using namespace std;


#define SERVICE_UUID        "4fafc102-1fb5-432e-8fcc-c5c2c331914b" // random UUID
#define CHARACTERISTIC_UUID "beb593b3-3e61-4a78-7f5b-e861ba07a826" // random UUID

BLEServer *pServe_r;
BLECharacteristic *pCharacteristic;
bool deviceConnected = false;
bool oldDeviceConnected = false;
std::string rxValue = "";
String rxValueCache = "";
//BLE server name
#define bleServerName "KryptonArc_BLE"

bool deviceLocked = false;

String txValue = "";



void incomingStringProcessing(String receivingString ){

    char myCharArray[receivingString.length() + 1]; // Allocate a char array with enough space to hold the string
    strcpy(myCharArray, receivingString.c_str()); // Copy the contents of the string to the char array

    String broadcastOutputAValString = find_values_between_substringsV3( myCharArray, broadcast_global_variables.broadcastOutputA_SubStringStart , broadcast_global_variables.broadcastOutputA_SubStringEnd );

    if ( broadcastOutputAValString != "N_A__" ){
      int broadcastOutputAValInt = broadcastOutputAValString.toInt();
      Serial.println("****** >>>>> ");
      Serial.print("broadcastOutputAValInt:   ");
      Serial.println( broadcastOutputAValInt );
      Serial.println("****** <<<<< ");
      servoWorksDrive( broadcastOutputAValInt );
    }

if ( receivingString ==  "TI_GetStatus_TI" ) {
  // Device Response : DR
    Serial.println("TI_GetStatus_TI: ");
    txValue = "-DR_200!OK!_DR-";
  }
  
};


    
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServe_r) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServe_r) {
      deviceConnected = false;
    }
};

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();
      if (value.length() > 0) {
        rxValue = value;
        Serial.println("Received Value: ");
        Serial.println(rxValue.c_str());

        String rxValueString = rxValue.c_str();

        if ( rxValueString == "10_react_native_101" ){
          rxValueCache = "";

        } else if ( rxValueString == "90_react_native_109" ){
          incomingStringProcessing( rxValueCache );
          rxValueCache = "";
        } else {
          rxValueCache = rxValueCache + rxValueString;
        }
        
      }
    }
};





void setup() {
  Serial.begin(115200);
  constrcut_MCU_ID_fixed = getMacAddress( );
 
  Serial.println("*****A11111");
  Serial.println( constrcut_MCU_ID_fixed.cChipModel );
  Serial.println( constrcut_MCU_ID_fixed.cChipRevision );
  Serial.println( constrcut_MCU_ID_fixed.cChipCores );
  Serial.println( constrcut_MCU_ID_fixed.cChipId );
  Serial.println("*****A222222");
  Serial.println( constrcut_MCU_ID_fixed.baseMacChrSOFTAP );
  Serial.println( constrcut_MCU_ID_fixed.baseMacChrBT );
  Serial.println( constrcut_MCU_ID_fixed.baseMacChrETH );
  Serial.println( constrcut_MCU_ID_fixed.baseMacChrWiFi );
  Serial.println("*****A33333");







  e2promInitiate();
  e2prom_variables = e2promReadAllWorks();

  // Serial.println("*****11 board_model");
  // Serial.println( e2prom_variables.board_model );
  // Serial.println("***** hardware_uuid");
  // Serial.println( e2prom_variables.hardware_uuid );
  // Serial.println("***** - vender_uuid");
  // Serial.println( e2prom_variables.vender_uuid );
  // Serial.println("***** - device_addr");
  // Serial.println( e2prom_variables.device_addr );
  // Serial.println("***** - tenant_addr");
  // Serial.println( e2prom_variables.tenant_addr );
  // Serial.println("***** - secure_code_01");
  // Serial.println( e2prom_variables.secure_code_01 );
  // Serial.println("***** - secure_code_02");
  // Serial.println( e2prom_variables.secure_code_02 );
  // Serial.println("***** - secure_code_03");
  // Serial.println( e2prom_variables.secure_code_03 );
  // Serial.println("*****");

  Serial.println("*****3333");

  Serial.println("*****1");

  Serial.println( generateUUIDString() );

  Serial.println("*****2");

  Serial.println("*****44");
  


  Serial.println("*****2");









  //// Servo works
  servoInitiate();

  BLEDevice::init( bleServerName );
  pServe_r = BLEDevice::createServer();
  pServe_r->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServe_r->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_NOTIFY |
                                         BLECharacteristic::PROPERTY_WRITE |
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_INDICATE
                                       );

  pCharacteristic->addDescriptor(new BLE2902());
  pCharacteristic->setCallbacks(new MyCallbacks());

  pService->start();

  BLEAdvertising *pAdvertising = pServe_r->getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter
  BLEUUID mUUID = BLEUUID::fromString(SERVICE_UUID);
  delay(500); // give the bluetooth stack the chance to get things ready
  pAdvertising->start();
  Serial.println("Waiting for a device to connect...");
}

void sendingChunkData(String sending_Chunk){
  pCharacteristic->setValue(sending_Chunk.c_str());
  pCharacteristic->notify();
  // Serial.println("Sent Value: ");
  // Serial.println(sending_Chunk.c_str());

  Serial.println("Senting Data: ");
  delay( 10 );
};


void loop() {
  while ( true ){

    // This hardware does not automatically send out data, it has to be instructed to send data by the device connected
    if (deviceConnected) {
      int txValueLength = txValue.length();

      if (txValue.length() > 0) {

        int sendingChunkSize = 20; //max packet size
        // Starting packet
        String starter_block = "100_esp32_000000101";
        sendingChunkData(starter_block);
        delay(10);

        // Data packets
        for (int i = 0; i < txValueLength; i += sendingChunkSize) {
          String sendingChunk = txValue.substring(i, min(i + sendingChunkSize, txValueLength)); //get next sendingChunk
          sendingChunkData( sendingChunk );

          // delay between packet transfer
          delay(10);
        }
        // Finishing packet
        String finisher_block = "900_esp32_000000109";
        sendingChunkData(finisher_block);

        txValue = "";
      }
      
    }

    if (deviceConnected != oldDeviceConnected) {
      oldDeviceConnected = deviceConnected;
      if (!deviceConnected) {
        delay(500); // give the bluetooth stack the chance to get things ready
        pServe_r->startAdvertising();
        Serial.println("Waiting for a device to connect... ...");
      }
    }
  }
}