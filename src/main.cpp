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
#include "modules/e2prom_works.hpp"


SOFTWARE_GLOBAL_PARAMETERS_FIXED software_parameters_fixed;
DEVICE_GLOBAL_HARDWARE_PARAMETERS_FIXED constrcut_MCU_ID_fixed;
E2PROM_STORED_DATA_FIXED e2prom_variables;
BROADCAST_GLOBAL_VAR broadcast_global_variables;


using namespace std;


#define SERVICE_UUID        "4fafc102-1fb5-432e-8fcc-c5c2c331914b" // random UUID
#define CHARACTERISTIC_UUID "beb593b3-3e61-4a78-7f5b-e861ba07a826" // random UUID

BLEServer *pServer;
BLECharacteristic *pCharacteristic;
bool deviceConnected = false;
bool oldDeviceConnected = false;

#define RECIEVE_ARRAY_SIZE 1000
#define sendingChunkSize 20 //max packet size
char* rx_DataAssembled = new char[RECIEVE_ARRAY_SIZE](); // () initializes all elements to null

#define TRANSFER_ARRAY_SIZE 1000

//BLE server name
#define BLE_SVR_NAME "KryptonArc_BLE"

bool deviceLocked = false;

char* txCValue = new char[ TRANSFER_ARRAY_SIZE ](); // () initializes all elements to null

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

    const char* broadcastOutputAValString = find_values_between_substringsV4( receivingString, broadcast_global_variables.broadcastOutputA_SubStringStart , broadcast_global_variables.broadcastOutputA_SubStringEnd );

    if ( receivingString ==  "TI_GetStatus_TI" ) {
      strcpy( txCValue , "-DR_200!OK!_DR-");
      return;
    }

    if ( strcmp(broadcastOutputAValString, "N_A__" ) != 0 ){
      int broadcastOutputAValInt = atoi( broadcastOutputAValString );
      servoWorksDrive( broadcastOutputAValInt );
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

      if ( !( strlen( pointerCharPointer ) > 0)) { 
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





void setup() {
  Serial.begin(115200);

  ////////////////////////////////////////////////////////////////////////
  // Servo works
  servoInitiate();
  const char* tmp_110 = e2promInitiate();

  e2prom_variables = e2promReadAllWorks();
  if ( strlen( e2prom_variables.hardware_uuid ) == 0 || strlen( e2prom_variables.board_model ) == 0 || strlen( e2prom_variables.vender_uuid ) == 0 ) {

    e2promWipeAllData();
    // UUID
    e2promWriteWorks(  "hardware_uuid" , generateUUIDString() ) ;

    const char* board_model_var = "KA_CB_G090V5B";
    e2promWriteWorks(  "board_model" , board_model_var ) ;

    const char* zero_uuid = "00000000-0000-0000-0000-000000000000";
    e2promWriteWorks(  "vender_uuid" , zero_uuid ) ;

    e2prom_variables = e2promReadAllWorks();
  }


  Serial.print(">>1> x2  second ") ; Serial.println(e2prom_variables.hardware_uuid );     Serial.print(">>1> length >>>    ") ;  Serial.println(  strlen( e2prom_variables.hardware_uuid ));
  Serial.print(">>0> x2  second ") ; Serial.println(e2prom_variables.board_model );     Serial.print(">>0> length >>>    ") ;  Serial.println(  strlen( e2prom_variables.board_model ));
  Serial.print(">>2> x2  second ") ; Serial.println(e2prom_variables.vender_uuid );     Serial.print(">>2> length >>>    ") ;  Serial.println(  strlen( e2prom_variables.vender_uuid ));
  Serial.print(">>3> x2  second ") ; Serial.println(e2prom_variables.device_addr );     Serial.print(">>3> length >>>    ") ;  Serial.println(  strlen( e2prom_variables.device_addr ));
  Serial.print(">>4> x2  second ") ; Serial.println(e2prom_variables.tenant_addr );     Serial.print(">>4> length >>>    ") ;  Serial.println(  strlen( e2prom_variables.tenant_addr ));
  Serial.print(">>5> x2  second ") ; Serial.println(e2prom_variables.secure_code_01  );     Serial.print(">>5> length >>>    ") ;  Serial.println(  strlen( e2prom_variables.secure_code_01  ));
  Serial.print(">>6> x2  second ") ; Serial.println(e2prom_variables.secure_code_02  );     Serial.print(">>6> length >>>    ") ;  Serial.println(  strlen( e2prom_variables.secure_code_02  ));
  Serial.print(">>7> x2  second ") ; Serial.println(e2prom_variables.secure_code_03  );     Serial.print(">>7> length >>>    ") ;  Serial.println(  strlen( e2prom_variables.secure_code_03  ));












  ////////////////////////////////////////////////////////////////////////
  //


  BLEDevice::init( BLE_SVR_NAME );
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService(SERVICE_UUID);
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

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter
  BLEUUID mUUID = BLEUUID::fromString(SERVICE_UUID);
  delay(500); // give the bluetooth stack the chance to get things ready
  pAdvertising->start();
  Serial.println("Waiting for a device to connect...");

}

void sendingChunkData(char* sending_Chunk){
  pCharacteristic->setValue( sending_Chunk );
  pCharacteristic->notify();
  Serial.println("Senting Data: ");
  delay( 10 );
};


void loop() {



  while ( true ){

    // This hardware does not automatically send out data, it has to be instructed to send data by the device connected
    if (deviceConnected) {
      int tx_CValueLength =  strlen( txCValue );
      
      if ( !(tx_CValueLength > 0)) { return; }

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
}