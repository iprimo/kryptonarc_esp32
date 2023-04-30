#include "HardwareSerial.h"
#include "Arduino.h"
#include "BLEDevice.h"
#include "BLEServer.h"
#include "BLEUtils.h"
#include "BLE2902.h"

// #include "e2prom_works.hpp"
// #include "string_works.hpp"
// #include "servo.hpp"


extern BLEServer *pServer;
extern BLECharacteristic *pCharacteristic;
extern BLEUUID mUUID;
extern BLEAdvertising *pAdvertising;
extern BLEService *pService ;

extern SOFTWARE_GLOBAL_PARAMETERS_FIXED software_parameters_fixed;
extern DEVICE_GLOBAL_HARDWARE_PARAMETERS_FIXED constrcut_MCU_ID_fixed;
extern E2PROM_STORED_DATA_FIXED e2prom_variables;
extern BROADCAST_GLOBAL_VAR broadcast_global_variables;

extern bool deviceConnected ;
extern bool oldDeviceConnected ;

extern HardwareSerial Serial;

#define SERVICE_UUID        "4fafc102-1fb5-432e-8fcc-c5c2c331914b" // random UUID
#define CHARACTERISTIC_UUID "beb593b3-3e61-4a78-7f5b-e861ba07a826" // random UUID

// extern int RECIEVE_ARRAY_SIZE ;
// extern int TRANSFER_ARRAY_SIZE ;
// extern char* rx_DataAssembled ;
// extern char* txCValue ;



#define RECIEVE_ARRAY_SIZE 1000
char* rx_DataAssembled = new char[RECIEVE_ARRAY_SIZE](); // () initializes all elements to null
#define TRANSFER_ARRAY_SIZE 1000
char* txCValue = new char[ TRANSFER_ARRAY_SIZE ](); // () initializes all elements to null






#define sendingChunkSize 20 //max packet size

//BLE server name
#define BLE_SVR_NAME "KryptonArc_BLE"


char* extractSubstring(char* input, int startIndex, int endIndex) {

    int len = strlen(input);
    if (startIndex < 0 || startIndex >= len) {
        return NULL; // invalid start index
    }
    if (endIndex < 0 || endIndex >= len) {
        endIndex = len - 1; // adjust end index to last character of the array
    }
    int subStrLen = endIndex - startIndex + 1;
    char* subStr = (char*) malloc(subStrLen + 1); // allocate memory for the substring
    strncpy(subStr, input + startIndex, subStrLen); // copy the substring to the newly allocated memory
    subStr[subStrLen] = '\0'; // add null terminator to the end of the substring
    return subStr;
}


void incomingStringProcessing( char* receivingString ){

    // Ping Function  
    // if ( strlen( pointerCharPointer ) == 0 ) { 
    const int pingStringExistanceChk = strcmp(receivingString, "TI_GetStatus_TI" ) ;
    const int deviceXigCodeLengthCheck = strlen( e2prom_variables.device_xc );
    const int tenantXigCodeLengthCheck = strlen( e2prom_variables.tenant_xc );

    if ( pingStringExistanceChk == 0 && deviceXigCodeLengthCheck == 0 && tenantXigCodeLengthCheck == 0) {
      // Device Not registered
      //////////////////////////////////////////
      // DR ?(HC: HealthCheck): Device Response
      char* sendStr56 = new char[ TRANSFER_ARRAY_SIZE ](); 
      strcat(sendStr56,  "-DR_200!OK!_DR-");

      //////////////////////////////////////////
      // BURS: RegistrationStatus -RS_unregistered_RS-
      strcat(sendStr56,  "-BURS_unregistered_BURS-");

      //////////////////////////////////////////
      // HU : Hardware UUID (Broadcast Underwrite)
      strcat(sendStr56, "-HU_");
      strcat(sendStr56, e2prom_variables.hardware_uuid );
      strcat(sendStr56, "_HU-");

      //////////////////////////////////////////
      // BM: Board Model (Broadcast Underwrite)
      strcat(sendStr56, "-BM_");
      strcat(sendStr56, e2prom_variables.board_model );
      strcat(sendStr56, "_BM-");

      //////////////////////////////////////////      
      // VX: Vender XigCode (Broadcast Underwrite)
      strcat(sendStr56, "-VX_");
      strcat(sendStr56, e2prom_variables.vender_xc );
      strcat(sendStr56, "_VX-");

      //////////////////////////////////////////      
      // DX: Device XigCode (Broadcast Underwrite)
      strcat(sendStr56, "-DX_");
      strcat(sendStr56, e2prom_variables.device_xc );
      strcat(sendStr56, "_DX-");

      //////////////////////////////////////////      
      // HWCM: Hardware ChipModel
      strcat(sendStr56, "-HWCM_");
      strcat(sendStr56, constrcut_MCU_ID_fixed.cChipModel );
      strcat(sendStr56, "_HWCM-");

      //////////////////////////////////////////      
      // HWCR: Hardware ChipRevision
      strcat(sendStr56, "-HWCR_");
      strcat(sendStr56, constrcut_MCU_ID_fixed.cChipRevision );
      strcat(sendStr56, "_HWCR-");

      //////////////////////////////////////////      
      // HWCC: Hardware ChipCores
      strcat(sendStr56, "-HWCC_");
      strcat(sendStr56, constrcut_MCU_ID_fixed.cChipCores );
      strcat(sendStr56, "_HWCC-");

      //////////////////////////////////////////      
      // HWCI: Hardware ChipId
      strcat(sendStr56, "-HWCI_");
      strcat(sendStr56, constrcut_MCU_ID_fixed.cChipId );
      strcat(sendStr56, "_HWCI-");

      //////////////////////////////////////////      
      // HWAP: Hardware baseMacChrSOFTAP
      strcat(sendStr56, "-HWAP_");
      strcat(sendStr56, constrcut_MCU_ID_fixed.baseMacChrSOFTAP );
      strcat(sendStr56, "_HWAP-");

      //////////////////////////////////////////      
      // HWBT: Hardware baseMacChrBT
      strcat(sendStr56, "-HWBT_");
      strcat(sendStr56, constrcut_MCU_ID_fixed.baseMacChrBT );
      strcat(sendStr56, "_HWBT-");

      //////////////////////////////////////////      
      // HWETH: Hardware baseMacChrETH
      strcat(sendStr56, "-HWETH_");
      strcat(sendStr56, constrcut_MCU_ID_fixed.baseMacChrETH );
      strcat(sendStr56, "_HWETH-");

      //////////////////////////////////////////      
      // HWWIFI: Hardware baseMacChrWiFi
      strcat(sendStr56, "-HWWIFI_");
      strcat(sendStr56, constrcut_MCU_ID_fixed.baseMacChrWiFi );
      strcat(sendStr56, "_HWWIFI-");

      strcpy( txCValue , sendStr56 );
      return;
    } else if ( pingStringExistanceChk == 0 ) {
      // Device registered - health check
      strcpy( txCValue , "-DR_200!OK!_DR-");
      return;

    } else if (  strcmp(receivingString, "TI_WipeAllLicensesAndReissueHWUUID_TI" ) == 0 ) {
      wipeAllAndReissueAllBasics();
      return;
    }

    const char* broadcastOutputAValString = find_values_between_substringsV4( receivingString, broadcast_global_variables.broadcastOutputA_SubStringStart , broadcast_global_variables.broadcastOutputA_SubStringEnd );

    if ( strcmp(broadcastOutputAValString, "N_A__" ) != 0 ){
      int broadcastOutputAValInt = atoi( broadcastOutputAValString );
      servoWorksDrive( broadcastOutputAValInt );
      strcpy( txCValue , "-DR_ActionTaken_DR-");
      return;
    }
  
};

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      uint8_t* received_data = pCharacteristic->getData();
      char* pointerCharPointer = (char*) received_data;

      if ( strlen( pointerCharPointer ) == 0 ) { 
        return; 

      } else if ( strcmp(pointerCharPointer, "10_react_native_101" ) == 0 ){
        rx_DataAssembled[0] = '\0';

      } else if ( strcmp(pointerCharPointer, "90_react_native_109" ) == 0 ){
        incomingStringProcessing( rx_DataAssembled );
        rx_DataAssembled[0] = '\0';

      } else {
        strcat(rx_DataAssembled, pointerCharPointer); // concatenate str2 to str1

      }
      
    }
};



void BluetoothInitiate() {

  ////////////////////////////////////////////////////////////////////////
  //


  BLEDevice::init( BLE_SVR_NAME );
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // BLEService *pService = pServer->createService(SERVICE_UUID);
  pService = pServer->createService(SERVICE_UUID);
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

  // BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising = pServer->getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter
  // BLEUUID mUUID = BLEUUID::fromString(SERVICE_UUID);
  mUUID = BLEUUID::fromString(SERVICE_UUID);
  delay(500); // give the bluetooth stack the chance to get things ready
  pAdvertising->start();
  Serial.println("Waiting for a device to connect...");

}

void sendingChunkData(char* sending_Chunk){
    
  pCharacteristic->setValue( sending_Chunk );
  pCharacteristic->notify();
  Serial.println("Senting Data...");
  delay( 10 );
};


void BluetoothMainProcess() {
    // This hardware does not automatically send out data, it has to be instructed to send data by the device connected
    if (deviceConnected) {
      int tx_CValueLength =  strlen( txCValue );
      
      if ( tx_CValueLength == 0 ) { return; }
      
      // Starting packet
      char starter_block[ sendingChunkSize ] = "100_esp32_000000101";
      sendingChunkData( starter_block );
      delay(10);

      // Data packets
      for (int i = 0; i < tx_CValueLength; i += sendingChunkSize) {
        sendingChunkData( extractSubstring( txCValue, i, i + sendingChunkSize ) );
        delay(10);
      }

      // Finishing packet
      char finisher_block[ sendingChunkSize ] = "900_esp32_000000109";
      sendingChunkData(finisher_block);
      txCValue[0] = '\0';
      
    }

    if (deviceConnected != oldDeviceConnected) {
      oldDeviceConnected = deviceConnected;
      if (!deviceConnected) {
        delay(500); // give the bluetooth stack the chance to get things ready
        pServer->startAdvertising();
        Serial.println("Waiting for a device to connect... ...");
      }
    }
  
}