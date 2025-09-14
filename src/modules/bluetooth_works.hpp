#ifndef BLUETOOTH_WORKS_HPP
#define BLUETOOTH_WORKS_HPP


#include "HardwareSerial.h"
#include "Arduino.h"
#include "BLEDevice.h"
#include "BLEServer.h"
#include "BLEUtils.h"
#include "BLE2902.h"
#include "modules/md5.hpp"
#include "modules/data_string_builder.hpp"
#include "modules/sha_hash.hpp"
#include "modules/base64_char_masking.hpp"
#include "modules/string_works.hpp"
#include "modules/lock_shackle_actions.hpp"
#include "modules/led_works.hpp"
#include "modules/timer_works.hpp"
#include "modules/system_structs.hpp"
#include "modules/crypto_utils.h"
#include "modules/esp32_time_utils.hpp"
#include "iostream"
#include "cstring"
#include "base64.h"


extern BLEServer *pServer;
extern BLECharacteristic *pCharacteristic;
extern BLEUUID mUUID;
extern BLEAdvertising *pAdvertising;
extern BLEService *pService ;

// extern SOFTWARE_GLOBAL_PARAMETERS_VAR software_parameters_variables;
// extern SOFTWARE_GLOBAL_PARAMETERS_FIXED software_parameters_fixed;
// extern DEVICE_GLOBAL_HARDWARE_PARAMETERS_FIXED constrcut_mcu_id_fixed;
// extern E2PROM_STORED_DATA_FIXED e2prom_variables;
// extern BROADCAST_GLOBAL_VAR broadcast_global_variables;

extern bool bleDeviceConnected ;
extern bool oldBLEDeviceConnected;

extern HardwareSerial Serial;

#define SERVICE_UUID        "0002eeff-0000-1000-8000-00805fab94fb" // random UUID
#define CHARACTERISTIC_UUID "5fafc502-0000-1000-8000-00105f9b14fb" // random UUID


#define RECIEVE_ARRAY_SIZE 4096
char* rx_DataCache_Assembled = new char[RECIEVE_ARRAY_SIZE](); // () initializes all elements to null
#define TRANSFER_ARRAY_SIZE 4096
char* tx_DataCache = new char[ TRANSFER_ARRAY_SIZE ](); // () initializes all elements to null

char* tx_InFlightData = new char[ TRANSFER_ARRAY_SIZE ](); // () initializes all elements to null
bool tx_Data_InFlight_InProgress = false;

#define sendingChunkSize 20 //max packet size

//////////////////////////////////////////
// DR ?(HC: HealthCheck): Device Response
char* sendStr56 = new char[ TRANSFER_ARRAY_SIZE ](); 
char* tempCache = new char[ TRANSFER_ARRAY_SIZE ](); // () initializes all elements to null

//BLE server name
#define BLE_SVR_NAME "KryptonArc_BLE"

void disable_bluetooth(){
  // Disable Bluetooth
  Serial.println("Disabling Bluetooth...");
  btStop();
};

void sendingChunkData(char* sending_Chunk){
    
  pCharacteristic->setValue( sending_Chunk );
  pCharacteristic->notify();
  Serial.println("Senting Data...");
  delay(15);
};


char* extractSubstring(const char* source, int start, int end) {
  // Ensure start and end are within bounds
  int length = strlen(source);
  if (start >= length) return nullptr; // Nothing to extract
  if (end > length) end = length;

  // Calculate substring length
  int subLength = end - start;
  char* substring = new char[subLength + 1]; // +1 for null terminator

  strncpy(substring, source + start, subLength);
  substring[subLength] = '\0'; // Null-terminate the string
  return substring;
}

// char* extractSubstring(char* input, int startIndex, int endIndex) {

//     int len = strlen(input);

//     char* subStringDivided = new char[ sendingChunkSize ](); // () initializes all elements to null

//     if (startIndex < 0 || startIndex >= len) {
//         // return NULL; // invalid start index
//       return subStringDivided ;
//     }
//     if (endIndex < 0 || endIndex >= len) {
//         endIndex = len - 1; // adjust end index to last character of the array
//     }
//     int subStrLen = endIndex - startIndex + 1;
//     strncpy(subStringDivided, input + startIndex, subStrLen); // copy the substring to the newly allocated memory
//     subStringDivided[subStrLen] = '\0'; // add null terminator to the end of the substring
//     return subStringDivided;
// }


void incomingStringProcessing( char* receivingString ){

  Serial.print("receivingString>###>>  ");
  Serial.println(receivingString);

  char* dataBefore_data = (char*)malloc(4096);
  char* dataAfter_hash = (char*)malloc(65);
  if (!dataBefore_data || !dataAfter_hash) {
    Serial.println("Failed to allocate memory for incomingStringProcessing buffers!");
    if (dataBefore_data) free(dataBefore_data);
    if (dataAfter_hash) free(dataAfter_hash);
    return;
  }

  bool hashExists = splitAtLastDelimiter(receivingString, '|', dataBefore_data, dataAfter_hash);
  if ( !hashExists ) {
    free(dataBefore_data);
    free(dataAfter_hash);
    return;
  }

    // Serial.print("dataBefore_data  >>>  ");
    // Serial.println(dataBefore_data);
    // Serial.print("dataAfter_hash  >>>  ");
    // Serial.println(dataAfter_hash);
   
    // Serial.println(dataBefore_data[ 3 ]);
    // Serial.println("dataBefore_data[ 3 ] >>>  ");
    
    // Serial.println(dataBefore_data[ 4 ] );
    // Serial.println("dataBefore_data[ 4 ] >>>  ");
    
    // Serial.println("software_parameters_fixed.GLOBAL_SHARED_HASH_KEY  >>>  ");
    // Serial.println(software_parameters_fixed.GLOBAL_SHARED_HASH_KEY);

    // 0x-0	: global hash and enrypton keys used
    // 0x-1	: device hash and enrypton keys used

    char hash256ResultArray[ 65 ];
    if ( dataBefore_data[ 3 ] == '1' ){
      // this matches device specfic hash
      hashSHA256( dataBefore_data, e2prom_variables.hashKey_Internal, hash256ResultArray );
    } else {
      // Global has used 
      hashSHA256( dataBefore_data , software_parameters_fixed.GLOBAL_SHARED_HASH_KEY, hash256ResultArray );
    }

    // Serial.print("hash256ResultArray  >>>  ");
    // Serial.println(hash256ResultArray);
    
    // hash mis-match

    if ( strcmp( dataAfter_hash, hash256ResultArray ) != 0 ) {
      free(dataBefore_data);
      free(dataAfter_hash);
      return;
    } 

    Serial.print("  >>>  hash OK !  >>>  ");


    if ( !software_parameters_variables.timeStampSetUsingFristTimeStamp ){
      Serial.println("999999 set first time  >>>  ");
      // Setting time stamp using incoming data time stamp
      const char* found_ts = find_values_between_substringsV5(receivingString, "tS_", "_tS");
      if (found_ts && strlen(found_ts) > 0) {
          strcpy(software_parameters_variables.incoming_data_time_stamp, found_ts);
          set_esp32_time_from_string(software_parameters_variables.incoming_data_time_stamp);
          software_parameters_variables.timeStampSetUsingFristTimeStamp = true;
      } else {
          Serial.println("No valid timestamp found in incoming string!");
      }
    }
    Serial.println("999999 read time  >>>  ");
    char timebuf[32];
    get_esp32_time_string(timebuf, sizeof(timebuf));
    Serial.println(timebuf); // Prints: 2025-09-10T20:53:19Z




    // Serial.print("pingStringExistanceChk  >>>  ");
    // Serial.println(pingStringExistanceChk);
    // Serial.print("deviceXigCodeLengthCheck  >>>  ");
    // Serial.println(deviceXigCodeLengthCheck);
    // Serial.print("tenantXigCodeLengthCheck  >>>  ");
    // Serial.println(tenantXigCodeLengthCheck);

    // const char* subString = "0x2001tI_GetStatus_tI"; // Replace with the substring you want to find

    // if (findSubstring(receivingString, "0x2001tI_GetStatus_tI")) {
    //   Serial.println(">>>>1111   Substring found in the string.");
    // } else {
    //   Serial.println(">>>>1111   Substring not found in the string.");
    // }


    // LED flash indicator -receiving data from cloud 
    if ( findSubstring(receivingString, "0x1" )  ) { 
      flashing_led_blue( "on" , "very_fast_flashing"  , false, 10 , true);
    }


    // Selector data processing
    if (  findSubstring(receivingString, "0x2001tI_GetStatus_tI" ) && 
          strlen( e2prom_variables.device_xc ) == 0 && 
          strlen( e2prom_variables.tenant_xc ) == 0) { 
      Serial.println("Blank Device matched - 0x2001tI_GetStatus_tI  >>>  ");

      //////////////////////////////////////////
      // DR ?(HC: HealthCheck): Device Response
      delete[] sendStr56;
      sendStr56 = new char[TRANSFER_ARRAY_SIZE]();

      delete[] tempCache;
      tempCache = new char[TRANSFER_ARRAY_SIZE](); // () initializes all elements to null
      
      std::string info = std::string("v01__0x0001") + 
            "_hwConfigState:" + "unregisteredDevice" +
            "_md5Hashing:" + "none" +
            "_encryption:" + "none" + "__v01";
      strcat(sendStr56, info.c_str());


      Serial.print("sendStr56:22222 ");
      Serial.println(sendStr56);

      append_status_information( sendStr56 );
      append_secret_config_information( sendStr56 );
      append_config_information( sendStr56 );
      append_hardware_information( sendStr56 );
      append_firmware_information( sendStr56 );
      append_bluetooth_session_sequence( sendStr56 );

      Serial.println("Blank Device matched - 0x2001tI_GetStatus_tI  >>>  11111 ");


      //////////////////////////////////////////      
      // 
      // Serial.println("sendStr56>>>>   ");
      // Serial.println(sendStr56);
      String encoded = base64::encode( sendStr56 );
      // Serial.println("encoded>>>>   ");
      // Serial.println(encoded);
      
      // Combined strings
      strcat( tempCache, "0x0001" );
      strcat( tempCache, encoded.c_str() );
      // strcat( tempCache, (base64::encode( sendStr56.c_str() ) ).c_str() );

      strcpy( tx_DataCache , tempCache );
    // } else if ( pingStringExistanceChk == 0 ) {
    //   // Device registered - health check
    //   strcpy( tx_DataCache , "-DR_200!OK!_DR-");
    //   return;

    } else if (
          findSubstring(receivingString, "0x2001tI_GetStatus_tI" ) && 
          strlen( e2prom_variables.device_xc ) > 10 && 
          strlen( e2prom_variables.tenant_xc ) > 10 ) {
        //////////////////////////////////////////
        // DR ?(HC: HealthCheck): Device Response
        delete[] sendStr56;
        sendStr56 = new char[TRANSFER_ARRAY_SIZE]();

        delete[] tempCache;
        tempCache = new char[TRANSFER_ARRAY_SIZE](); // () initializes all elements to null

        std::string info = std::string("v01__0x0102") + 
                    "_traffOrigin:" + "hwDevice" +
                    "_md5Hashing:" + "hwDevice" +
                    "_encryption:" + "none" +
                    "_hwConfigState:" + "registeredDevice" + "__v01";

        strcat(sendStr56, info.c_str());

        Serial.print("sendStr56:111111 ");
        Serial.println(sendStr56);

        append_status_information( sendStr56 );
        append_config_information( sendStr56 );
        // append_hardware_information( sendStr56 );
        append_firmware_information( sendStr56 );
        append_bluetooth_session_sequence( sendStr56 );

        Serial.print("sendStr56:333333 ");
        Serial.println(sendStr56);

        // Build the full response in a std::string
        std::string fullResponse = std::string(sendStr56);

        Serial.print("sendStr56:444444 ");
        Serial.println(sendStr56);
        //////////////////////////////////////////
        // RSA Encryption of encKey, hashKey and timeStamp
          
        char *plain = (char*)malloc(512);
        if (!plain) {
          Serial.println("Failed to allocate memory for plain buffer!");
        } else {
          plain[0] = '\0';
          strcat(plain, "encKey_");
          strcat(plain, e2prom_variables.encryptionKey_Internal);
          strcat(plain, "_encKey-hashKey_");
          strcat(plain, e2prom_variables.hashKey_Internal);
          strcat(plain, "_hashKey-ts_");
          strcat(plain, software_parameters_variables.incoming_data_time_stamp);
          strcat(plain, "_ts");

          Serial.print("Plain: ");
          Serial.println(plain);

          int plain_len = strlen(plain);
          Serial.print("plain_len: ");
          Serial.println(plain_len);
        }

        // RSA encryption
        char *encrypted = (char*)malloc(1024);
        if (!plain || !encrypted) {
            if (!plain) Serial.println("Failed to allocate memory for plain buffer!");
            if (!encrypted) Serial.println("Failed to allocate memory for encryption buffer!");
        } else {
          encrypted[0] = '\0';
          int enc_result = encrypt_with_public_key(plain, encrypted, 1024);
          if (enc_result == 0) {
            Serial.print("Encrypted: ");
            Serial.println(encrypted);
            // // Decrypt for testing
            // char *decrypted = (char*)malloc(1024); // Increased buffer size to match encrypted
            // if (!decrypted) {
            //   Serial.println("Failed to allocate memory for decrypted buffer!");
            // } else {
            //   decrypted[0] = '\0';
            //   int dec_result = decrypt_with_private_key(encrypted, decrypted, 1024);
            //   if (dec_result == 0) {
            //     Serial.print("Decrypted: ");
            //     Serial.println(decrypted);
            //   } else {
            //     Serial.print("Decryption failed! Error code: ");
            //     Serial.println(dec_result);
            //   }
            //   free(decrypted);
            // }
          } else {
            Serial.print("Encryption failed! Error code: ");
            Serial.println(enc_result);
            Serial.print("Encrypted buffer (may be garbage): ");
            Serial.println(encrypted);
          }
        }


        Serial.print("sendStr56:555555 ");
        Serial.println(sendStr56);

        // Append the encrypted block to the full response
        fullResponse += "publicKeyEnc_";
        if (encrypted) fullResponse += encrypted;
        fullResponse += "_publicKeyEnc";
        // Copy the result to tx_DataCache
        strncpy(tx_DataCache, fullResponse.c_str(), TRANSFER_ARRAY_SIZE - 1);
        tx_DataCache[TRANSFER_ARRAY_SIZE - 1] = '\0';

        if (plain) free(plain);
        if (encrypted) free(encrypted);

        

        Serial.print("tx_DataCache:777777 ");
        Serial.println(tx_DataCache);
        
    } else if (  findSubstring(receivingString, "0x2002tI_Reboot_tI" ) && 
          strlen( e2prom_variables.device_xc ) == 0 && 
          strlen( e2prom_variables.tenant_xc ) == 0
          ) {
      Serial.println("Restarting in 1 seconds");
      delay(1000);
      ESP.restart();

    } else if (  findSubstring(receivingString, "0x2002tI_Reboot_tI" ) ) {
      strcpy( tx_DataCache , "0x0001_Error_Occured" );
      
    } else if ( findSubstring(receivingString, "0x1102" )  ) {
        
      //  0x1102dFhDXzAwMDAxXzAwMDAxXzAwMDAxXzAwMDAxX3RlbmFudGFjY291bnRfdFhDZFhDXzIzOGI1Y19mNjk1NWNfZGY4YThhX2FjMzBhNmExZDgxX2hhcmR3YXJldHdpbl9kWENzSV9iTEVTU0VRX05hTl9iTEVTU0VRdFNfMjAyNC0wMS0xOVQwNToyODoxOS4xMDNaX3RTX3NJaFdBY3Rpb25fdW5sb2NrX2hXQWN0aW9u|413565c688bb4336c0e54d478daedd39f0aa7e321df8abafbbbed545a3e1bde
      Serial.println("0x1102>444    matched 444>>>   dataBefore_data: ");
      Serial.println( dataBefore_data );

      // extracting masked data
      char* masked_data = extract_substring( 6 , dataBefore_data ) ;
      Serial.println("masked_data: ");
      Serial.println( masked_data );

      char* unmasked_data = new char[ TRANSFER_ARRAY_SIZE ](); 
      base64_char_decoding( masked_data,  unmasked_data );
      Serial.println("unmasked_data: ");
      Serial.println( unmasked_data );

      // Hardware XigCode validation
      const char* incomingTXC = find_values_between_substringsV5( unmasked_data, "tXC_" , "_tXC" );
      // Serial.println("incomingTXC   >>_+_+_> ");
      // Serial.println(incomingTXC);

      if ( strcmp( incomingTXC, e2prom_variables.tenant_xc ) != 0 ){  
        Serial.print("  >>>  tenant mis-match  >>>  ");
        return;
      }

      // Device XigCode validation
      const char* incoming_DXC = find_values_between_substringsV5( unmasked_data, "dXC_" , "_dXC" );
      // Serial.println("incoming_DXC   >>_+_+_> ");
      // Serial.println(incoming_DXC);

      if ( strcmp( incoming_DXC, e2prom_variables.device_xc ) != 0 ){  
        Serial.print("  >>>  tenant mis-match  >>>  ");
        return;
      }
      strcpy( software_parameters_variables.incoming_data_time_stamp , find_values_between_substringsV5( unmasked_data, "tS_" , "_tS" ) );
      // Serial.println("software_parameters_variables.incoming_data_time_stamp: ");
      // Serial.println( software_parameters_variables.incoming_data_time_stamp );

      const char* incoming_action_instruction = find_values_between_substringsV5( unmasked_data, "hWAction_" , "_hWAction" );
      Serial.println("incoming_action_instruction: ");
      Serial.println( incoming_action_instruction );
      write_shackle_lock_status( incoming_action_instruction );

    // } else if ( ( 
    //               strlen( e2prom_variables.hardware_uuid ) == 0 || 
    //               strlen( e2prom_variables.board_model ) == 0 
    //             ) && 
    //               strcmp(receivingString, "tI_ConditionalWipeAllLicensesAndReissueHWUUID_tI" ) == 0 
    //             ) {
    //   // Reset all settings if device does not have basics
    //   wipeAllAndReissueAllBasics();
    //   return;
      

    // } else if (  strcmp(receivingString, "tI_WipeAllLicensesAndReissueHWUUID_tI" ) == 0 ) {
    //   // Reset all settings in any condition
    //   wipeAllAndReissueAllBasics();
    //   return;
      

    } else {
    }

    // const char* broadcastOutputAValString = find_values_between_substringsV4( receivingString, broadcast_global_variables.broadcastOutputA_SubStringStart , broadcast_global_variables.broadcastOutputA_SubStringEnd );
    // Serial.println("broadcastOutputAValString   >>> ");
    // Serial.println(broadcastOutputAValString);

    // if ( strcmp(broadcastOutputAValString, "N_A__" ) != 0 ){
    //   int broadcastOutputAValInt = atoi( broadcastOutputAValString );
    //   servoWorksDrive( broadcastOutputAValInt );
    //   strcpy( tx_DataCache , "-DR_DeviceInSync_DR-");
    //   return;
    // }
    // // strcpy( tx_DataCache , "-DR_200!OK!_NoActionMatched_DR-");
    // return;


    // led_static_action( "red", "off" );
    // led_static_action( "green", "off" );
    // led_static_action( "blue", "off" ); // orange
    

  free(dataBefore_data);
  free(dataAfter_hash);
  return;
    
};

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      bleDeviceConnected = true;
      flashing_led_blue( "on" , "fix_light_on" , true );
    };

    void onDisconnect(BLEServer* pServer) {
      bleDeviceConnected = false;
      flashing_led_blue( "on" , "normal_flashing" , true );
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


void stopBLE() {
  Serial.println("Stopping BLE stack...");
  pAdvertising->stop();
}

void deinitBLE() {
  Serial.println("deinit BLE stack...");
  BLEDevice::deinit(); // Deinitialize BLE stack
}

void restartBLE() {
  Serial.println("Restarting BLE stack...");
  BLEDevice::deinit(); // Deinitialize BLE stack
  BLEDevice::init( BLE_SVR_NAME ); // Reinitialize
}


void bluetooth_initialization () {

  ////////////////////////////////////////////////////////////////////////
  //
  BLEDevice::init( BLE_SVR_NAME );
  pServer = BLEDevice::createServer();
  if (!pServer) throw "Failed to create BLE server - 1.";
  pServer->setCallbacks(new MyServerCallbacks());

  // BLEService *pService = pServer->createService(SERVICE_UUID);
  pService = pServer->createService(SERVICE_UUID);
  if (!pService) throw "Failed to create BLE service - 2.";
  pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_NOTIFY |
                                         BLECharacteristic::PROPERTY_WRITE |
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_INDICATE
                                       );
  if (!pCharacteristic) throw "Failed to create BLE characteristic.";

  pCharacteristic->addDescriptor(new BLE2902());
  pCharacteristic->setCallbacks(new MyCallbacks());

  pService->start();

  // BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising = pServer->getAdvertising();
  if (!pAdvertising) throw "Failed to get BLE advertising instance.";

  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter
  // BLEUUID mUUID = BLEUUID::fromString(SERVICE_UUID);
  mUUID = BLEUUID::fromString(SERVICE_UUID);
  
  flashing_led_blue( "on" , "normal_flashing" , true );
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
        // const int deviceXigCodeLengthCheck = strlen( e2prom_variables.device_xc );
        // const int tenantXigCodeLengthCheck = strlen( e2prom_variables.tenant_xc );
        char hash256ResultArray[ 65 ];
        if ( strlen( e2prom_variables.device_xc ) > 10 && strlen( e2prom_variables.tenant_xc ) > 10 ){
          hashSHA256( tx_InFlightData, e2prom_variables.hashKey_Internal, hash256ResultArray );
        } else {
          hashSHA256( tx_InFlightData, software_parameters_fixed.GLOBAL_SHARED_HASH_KEY, hash256ResultArray );
        }

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
          
          // Check if extraction succeeded
          if (mySubstring == nullptr) {
            Serial.println("Error: Failed to extract substring.");
            continue; // Skip this iteration
          }

          sendingChunkData( mySubstring );

          // Free dynamically allocated memory (if extractSubstring allocates)
          delete[] mySubstring; // or free(mySubstring) if malloc was used
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
        flashing_led_blue( "on" , "very_fast_flashing" , true );
        pServer->startAdvertising();
        Serial.println("Waiting for a device to connect... ...");
      }
    }
  
}

#endif

