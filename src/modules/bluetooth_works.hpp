#include "HardwareSerial.h"
#include "Arduino.h"
#include "BLEDevice.h"
#include "BLEServer.h"
#include "BLEUtils.h"
#include "BLE2902.h"
#include "modules/md5.hpp"
#include "modules/encryption_works.hpp"
#include "modules/sha_hash.hpp"
#include "iostream"
#include "cstring"
#include "base64.h"


extern BLEServer *pServer;
extern BLECharacteristic *pCharacteristic;
extern BLEUUID mUUID;
extern BLEAdvertising *pAdvertising;
extern BLEService *pService ;

extern SOFTWARE_GLOBAL_PARAMETERS_FIXED software_parameters_fixed;
extern DEVICE_GLOBAL_HARDWARE_PARAMETERS_FIXED constrcut_MCU_ID_fixed;
extern E2PROM_STORED_DATA_FIXED e2prom_variables;
extern BROADCAST_GLOBAL_VAR broadcast_global_variables;

extern bool bleDeviceConnected ;
extern bool oldBLEDeviceConnected;

extern HardwareSerial Serial;

#define SERVICE_UUID        "4fafc102-1fb5-432e-8fcc-c5c2c331914b" // random UUID
#define CHARACTERISTIC_UUID "beb593b3-3e61-4a78-7f5b-e861ba07a826" // random UUID


#define RECIEVE_ARRAY_SIZE 1024
char* rx_DataCache_Assembled = new char[RECIEVE_ARRAY_SIZE](); // () initializes all elements to null
#define TRANSFER_ARRAY_SIZE 1024
char* tx_DataCache = new char[ TRANSFER_ARRAY_SIZE ](); // () initializes all elements to null

char* tx_InFlightData = new char[ TRANSFER_ARRAY_SIZE ](); // () initializes all elements to null
bool tx_Data_InFlight_InProgress = false;

#define sendingChunkSize 20 //max packet size

//BLE server name
#define BLE_SVR_NAME "KryptonArc_BLE"

void sendingChunkData(char* sending_Chunk){
    
  pCharacteristic->setValue( sending_Chunk );
  pCharacteristic->notify();
  Serial.println("Senting Data...");
  delay(15);
};

char* extractSubstring(char* input, int startIndex, int endIndex) {

    int len = strlen(input);

    char* subStringDivided = new char[ sendingChunkSize ](); // () initializes all elements to null

    if (startIndex < 0 || startIndex >= len) {
        // return NULL; // invalid start index
      return subStringDivided ;
    }
    if (endIndex < 0 || endIndex >= len) {
        endIndex = len - 1; // adjust end index to last character of the array
    }
    int subStrLen = endIndex - startIndex + 1;
    strncpy(subStringDivided, input + startIndex, subStrLen); // copy the substring to the newly allocated memory
    subStringDivided[subStrLen] = '\0'; // add null terminator to the end of the substring
    return subStringDivided;
}


void incomingStringProcessing( char* receivingString ){

  

    // Ping Function  
    // if ( strlen( pointerCharPointer ) == 0 ) { 
    const int pingStringExistanceChk = strcmp(receivingString, "TI_GetStatus_TI" ) ;
    const int deviceXigCodeLengthCheck = strlen( e2prom_variables.device_xc );
    const int tenantXigCodeLengthCheck = strlen( e2prom_variables.tenant_xc );

    Serial.print("receivingString  >>>  ");
    Serial.println(receivingString);


    Serial.print("pingStringExistanceChk  >>>  ");
    Serial.println(pingStringExistanceChk);
    Serial.print("deviceXigCodeLengthCheck  >>>  ");
    Serial.println(deviceXigCodeLengthCheck);
    Serial.print("tenantXigCodeLengthCheck  >>>  ");
    Serial.println(tenantXigCodeLengthCheck);



      // "0x0000" - public information:
      //        configured device
      //        md5 hashing used
      //        global hashing salt used
      //        no encryption used


    if ( pingStringExistanceChk == 0 && deviceXigCodeLengthCheck == 0 && tenantXigCodeLengthCheck == 0) {
      // Device Not registered
      // "0x0001" - blank device:
      //        md5 hashing used
      //        global hashing salt used
      //        no encryption used
      

      //////////////////////////////////////////
      // DR ?(HC: HealthCheck): Device Response
      char* sendStr56 = new char[ TRANSFER_ARRAY_SIZE ](); 
      char* tempCache = new char[ TRANSFER_ARRAY_SIZE ](); // () initializes all elements to null

      //////////////////////////////////////////
      // HU : Hardware UUID
      strcat(sendStr56, "-HU_");
      strcat(sendStr56, e2prom_variables.hardware_uuid );
      strcat(sendStr56, "_HU-");

      //////////////////////////////////////////
      // BM: Board Model
      strcat(sendStr56, "-BM_");
      strcat(sendStr56, e2prom_variables.board_model );
      strcat(sendStr56, "_BM-");

      //////////////////////////////////////////      
      // VX: Vender XigCode
      strcat(sendStr56, "-VX_");
      strcat(sendStr56, e2prom_variables.vender_xc );
      strcat(sendStr56, "_VX-");

      //////////////////////////////////////////      
      // DX: Device XigCode
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

      //////////////////////////////////////////      
      // Request session ID 
      strcat(sendStr56, "-RSID_");
      strcat(sendStr56, constrcut_MCU_ID_fixed.baseMacChrWiFi );
      strcat(sendStr56, "_RSID-");


      Serial.println("sendStr56>>>>   ");
      Serial.println(sendStr56);
      String encoded = base64::encode( sendStr56 );
      Serial.println("encoded>>>>   ");
      Serial.println(encoded);
      
      // Combined strings
      strcat( tempCache, "0x0001" );
      strcat( tempCache, encoded.c_str() );
      // strcat( tempCache, (base64::encode( sendStr56.c_str() ) ).c_str() );




      strcpy( tx_DataCache , tempCache );
      return;
    } else if ( pingStringExistanceChk == 0 ) {
      // Device registered - health check
      strcpy( tx_DataCache , "-DR_200!OK!_DR-");
      return;

    } else if ( ( 
                  strlen( e2prom_variables.hardware_uuid ) == 0 || 
                  strlen( e2prom_variables.board_model ) == 0 
                ) && 
                  strcmp(receivingString, "TI_ConditionalWipeAllLicensesAndReissueHWUUID_TI" ) == 0 
                ) {
      // Reset all settings if device does not have basics
      wipeAllAndReissueAllBasics();
      return;
      

    } else if (  strcmp(receivingString, "TI_WipeAllLicensesAndReissueHWUUID_TI" ) == 0 ) {
      // Reset all settings in any condition
      wipeAllAndReissueAllBasics();
      return;
      
    } else if (  strcmp(receivingString, "TI_HardwareDeviceReload_TI" ) == 0 ) {
      Serial.println("Restarting in 1 seconds");
      delay(1000);
      ESP.restart();
      return;
    }

    const char* broadcastOutputAValString = find_values_between_substringsV4( receivingString, broadcast_global_variables.broadcastOutputA_SubStringStart , broadcast_global_variables.broadcastOutputA_SubStringEnd );

    if ( strcmp(broadcastOutputAValString, "N_A__" ) != 0 ){
      int broadcastOutputAValInt = atoi( broadcastOutputAValString );
      servoWorksDrive( broadcastOutputAValInt );
      strcpy( tx_DataCache , "-DR_DeviceInSync_DR-");
      return;
    }
    strcpy( tx_DataCache , "-DR_200!OK!_NoActionMatched_DR-");
    return;
};

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      bleDeviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      bleDeviceConnected = false;
    }
};

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      uint8_t* received_data = pCharacteristic->getData();
      char* pointerCharPointer = (char*) received_data;
      
    Serial.print("pointerCharPointer  >>>  ");
    Serial.println(pointerCharPointer);

      if ( strlen( pointerCharPointer ) == 0 ) { 
        return; 

      } else if ( strcmp(pointerCharPointer, "10_react_native_101" ) == 0 ){
        rx_DataCache_Assembled[0] = '\0';

      } else if ( strcmp(pointerCharPointer, "90_react_native_109" ) == 0 ){
        incomingStringProcessing( rx_DataCache_Assembled );
        rx_DataCache_Assembled[0] = '\0';

      } else {
        strcat(rx_DataCache_Assembled, pointerCharPointer); // concatenate str2 to str1

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


void BluetoothMainProcess() {
    // This hardware does not automatically send out data, it has to be instructed to send data by the device connected
    if ( bleDeviceConnected ) {
      int tx_CValueLength =  strlen( tx_DataCache );

      if ( !tx_CValueLength == 0 && !tx_Data_InFlight_InProgress ) { 
        tx_Data_InFlight_InProgress = true;

        strcpy( tx_InFlightData , tx_DataCache );
        // Emptying the incoming string
        tx_DataCache[0] = '\0';
        
        // Starting packet
        char starter_block[ sendingChunkSize ] = "100_esp32_000000101";
        sendingChunkData( starter_block );


        // Creating hash of data - if device is configred used global hash key, if device is configured use device specific hash key
        const int deviceXigCodeLengthCheck = strlen( e2prom_variables.device_xc );
        const int tenantXigCodeLengthCheck = strlen( e2prom_variables.tenant_xc );
        char hashSalt[33]  ; //  32 visible characters plus one null-terminated, character \0 (null character) at the end to mark the string's end.

        // if device already configured, it will use the device dedicated hashSalt. If device is blank, it add the globally known Hash salt.
        if ( deviceXigCodeLengthCheck != 0 && tenantXigCodeLengthCheck != 0) {
          strncpy(hashSalt, e2prom_variables.hardware_specific_hash_salt, 32);  // limiting has salt to just 32 byte
          hashSalt[32] = '\0';  // Ensure null termination 
        } else {
           strcpy(hashSalt, software_parameters_fixed.GLOBAL_HASH_SALT);  
        }

        // Determine the length of the combined string
        size_t combinedLength = strlen(tx_InFlightData) + strlen(hashSalt) + 1; // +1 for the null terminator

        // Create a new char array to hold the combined string
        char combinedStr[ combinedLength ];

        // Copy the first string into the combined array
        strcpy(combinedStr, tx_InFlightData);

        // Concatenate the second string onto the combined array
        strcat(combinedStr, hashSalt);
        
        Serial.print(" combinedStr >>>  " );
        Serial.println( combinedStr );

        // String iii = generateMD5Hash( combinedStr );
        // Serial.print( "iii  >>> ooooooooo - ooooooooo " );
        // Serial.println( iii );



//   // https://techtutorialsx.com/2018/01/25/esp32-arduino-applying-the-hmac-sha-256-mechanism/
//   char* key = "48cf29ea128baf2d";
//   char *payload = combinedStr; // "Hello HMAC SHA 256!";
//   byte hmacResult[32];
 
//   mbedtls_md_context_t ctx;
//   mbedtls_md_type_t md_type = MBEDTLS_MD_SHA256;
 
//   // const size_t payloadLength = strlen(payload);
//   const size_t payloadLength = strlen(combinedStr);
//   const size_t keyLength = strlen(key);            
 
//   mbedtls_md_init(&ctx);
//   mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(md_type), 1);
//   mbedtls_md_hmac_starts(&ctx, (const unsigned char *) key, keyLength);
//   mbedtls_md_hmac_update(&ctx, (const unsigned char *) payload, payloadLength);
//   mbedtls_md_hmac_finish(&ctx, hmacResult);
//   mbedtls_md_free(&ctx);
 
//   Serial.println("!!!   sizeof(hmacResult): ");
 
//   char hash256ResultArray[sizeof(hmacResult) * 2 + 1];  // Allocate space for digits and null terminator

// Serial.println(" ---- ");
// Serial.println("!!!   sizeof(hmacResult): ");
// Serial.println(sizeof(hmacResult));
// Serial.println(" ---- ");
// Serial.println("!!!  sizeof(hmacResult) * 2 + 1: ");
// Serial.println(sizeof(hmacResult) * 2 + 1);
// Serial.println(" ---- ");




//   int resultIndex = 0;

//   for (int i = 0; i < sizeof(hmacResult); i++) {
//       char str[3];
//       sprintf(str, "%02x", (int)hmacResult[i]);

//       // Append str to the hash256ResultArray
//       strncpy(hash256ResultArray + resultIndex, str, 2);  // Copy 2 characters from str
//       resultIndex += 2;  // Move the index for the next append
//   }

//   // Add null terminator to mark the end of the string
//   hash256ResultArray[resultIndex] = '\0';

//   Serial.println("");
//   Serial.println("hashChar >---> ");
//   Serial.println(hash256ResultArray);

//   Serial.println("");
//   // Serial.println("hashChar >-2--> ");
//   // hashChar[ sizeof(hmacResult) ] = '\0';
//   // Serial.println(hashChar);

//   Serial.println("");

//   Serial.println("!!!   Hash: ");
//   char* key = "48cf29ea128baf2d";
//   char *payload = combinedStr; // "Hello HMAC SHA 256!";

    char* key = "48cf29ea128baf2d";
    char hash256ResultArray[ 65 ];
    hashSHA256( combinedStr, key, hash256ResultArray );



        // Adding has to the end of sending string
        strcat(tx_InFlightData, "|");  // Add double quotes
        strcat(tx_InFlightData, hash256ResultArray );  // Add the String variable



        int tx_InFlightDataLength =  strlen( tx_InFlightData );
        // Data packets
        Serial.println("tx_InFlightData :::  ");
        Serial.println( tx_InFlightData );
        Serial.println("tx_InFlightDataLength :::  ");
        Serial.println( tx_InFlightDataLength );




        for (int i = 0; i < tx_InFlightDataLength; i += sendingChunkSize) {
          char* mySubstring = extractSubstring( tx_InFlightData, i, i + sendingChunkSize ) ;
          sendingChunkData( mySubstring );
        }

        // Finishing packet
        char finisher_block[ sendingChunkSize ] = "900_esp32_000000109";
        sendingChunkData(finisher_block);

        tx_Data_InFlight_InProgress = false;
        tx_InFlightData[0] = '\0';
      }

    }

    if ( bleDeviceConnected != oldBLEDeviceConnected ) {
      oldBLEDeviceConnected = bleDeviceConnected;
      if ( !bleDeviceConnected ) {
        pServer->startAdvertising();
        Serial.println("Waiting for a device to connect... ...");
      }
    }
  
}