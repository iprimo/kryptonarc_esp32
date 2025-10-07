#ifndef BLUETOOTH_WORKS_HPP
#define BLUETOOTH_WORKS_HPP


#include "HardwareSerial.h"
#include "Arduino.h"
#include "BLEDevice.h"
#include "BLEServer.h"
#include "BLEUtils.h"
#include "BLE2902.h"
#include "modules/hash_works.hpp"
#include "modules/data_string_builder.hpp"
#include "modules/sha_hash.hpp"
#include "modules/e2prom_works.hpp"
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
#include "modules/exec_code.hpp"


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
  // Serial.println("Senting Data...");
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



void incomingStringProcessing( char* receivingString ){

  Serial.print("receivingString>###>>  ");
  Serial.println(receivingString);

  // Use helper function to extract meta, hash, and data
  char* meta = nullptr;
  char* hash = nullptr;
  char* data_raw = nullptr;
  char* data_decoded = nullptr;
  if (!parseMetaHashData(receivingString, meta, hash, data_raw, data_decoded)) {
    if (data_raw) { delete[] data_raw; data_raw = nullptr; }
    if (meta) { delete[] meta; meta = nullptr; }
    if (hash) { delete[] hash; hash = nullptr; }
    if (data_decoded) { delete[] data_decoded; data_decoded = nullptr; }
    return;
  }

  Serial.println("meta: ");
  Serial.println(meta);

  Serial.println("hash: ");
  Serial.println(hash);

  Serial.println("data_raw: ");
  Serial.println(data_raw);

  Serial.println("data_decoded: ");
  Serial.println(data_decoded);

  if (!verifyTrafficHash(meta, hash, data_raw)) {
    if (data_raw) { delete[] data_raw; data_raw = nullptr; }
    if (meta) { delete[] meta; meta = nullptr; }
    if (hash) { delete[] hash; hash = nullptr; }
    if (data_decoded) { delete[] data_decoded; data_decoded = nullptr; }
    return;
  }

    // LED flash indicator -receiving data from cloud 
    if ( findSubstring(data_decoded, "0x1" )  ) { 
      flashing_led_blue( "on" , "very_fast_flashing"  , false, 10 , true);
    }


    // Selector data processing
    if (  findSubstring(data_decoded, "0x2002tI_Reboot_tI" )) {
      Serial.println("Restarting in 1 seconds");
      delay(1000);
      ESP.restart();


    } else if (  findSubstring(data_decoded, "request:8" )) {
      Serial.println("***** FLUSH *****");

      e2promReadAllWorks();
      Serial.println("Restarting in 1 seconds");
      delay(1000);
      ESP.restart();


    } else if (  findSubstring(data_decoded, "0x123456789" )) {
      Serial.println("Restarting in 1 seconds");
      delay(1000);
      ESP.restart();

    } else if (  findSubstring(data_decoded, "request:GetStatus::" ) && 
          strlen( e2prom_variables.device_xc ) < 10 && 
          strlen( e2prom_variables.tenant_xc ) < 10 ) { 
      Serial.println("Blank Device matched - :GetStatus::  >>>  ");
      char* result = exec_code_0x0001();
      if (result) {
        strncpy(tx_DataCache, result, TRANSFER_ARRAY_SIZE - 1);
        tx_DataCache[TRANSFER_ARRAY_SIZE - 1] = '\0';
        delete[] result; // or free(result); depending on how exec_code_0x0001 allocates
      } else {
        tx_DataCache[0] = '\0';
      }
    } else if (
          findSubstring(data_decoded, "request:GetStatus::" ) && 
          strlen( e2prom_variables.device_xc ) > 10 && 
          strlen( e2prom_variables.tenant_xc ) > 10 ) {
        //////////////////////////////////////////
        // DR ?(HC: HealthCheck): Device Response
        delete[] sendStr56;
        sendStr56 = new char[TRANSFER_ARRAY_SIZE]();

        delete[] tempCache;
        tempCache = new char[TRANSFER_ARRAY_SIZE](); // () initializes all elements to null

        std::string info = std::string("") + 
              "ver:" + "2" + "::" + 
              "code:" + "0x0102" + "::" + 
              "traffOrigin:" + "hwDevice" + "::" + 
              "dEncryption:" + "none" + "::" + 
              "dHash:" + "hwDevice01" + "::" + 
              "hwConfigState:" + "registeredDevice" "::" ;

        strcat(sendStr56, info.c_str());

        Serial.print("sendStr56:111111 ");
        Serial.println(sendStr56);

        // append_status_information( sendStr56 );
        // Prepend status information
        std::string combined = device_shackle_state() + sendStr56;
        strcpy(sendStr56, combined.c_str());

        Serial.print("sendStr56:22766666222 ");
        Serial.println(sendStr56);

        // append_secret_config_information( sendStr56 );
        std::string combined2 = device_tenant_xigcode() + sendStr56;
        strcpy(sendStr56, combined2.c_str());
        
        // append_firmware_information( sendStr56 );
        std::string combined3 = device_firmware_information() + sendStr56;
        strcpy(sendStr56, combined3.c_str());
        // append_bluetooth_session_sequence( sendStr56 );
        std::string combined4 = device_bluetooth_session_sequence() + sendStr56;
        strcpy(sendStr56, combined4.c_str());

        Serial.print("sendStr56:333zzz333 ");
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
          strcat(plain, "encKey:");
          strcat(plain, e2prom_variables.encryptionKey_Internal);
          strcat(plain, "::hashKey:");
          strcat(plain, e2prom_variables.hashKey_Internal);
          strcat(plain, "::timeStamp:");
          strcat(plain, software_parameters_variables.incoming_data_time_stamp);

          

          strcat(plain, "::");

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
        fullResponse += "publicKeyEnc:";
        if (encrypted) fullResponse += encrypted;
        fullResponse += "::";
        // Copy the result to tx_DataCache
        strncpy(tx_DataCache, fullResponse.c_str(), TRANSFER_ARRAY_SIZE - 1);
        tx_DataCache[TRANSFER_ARRAY_SIZE - 1] = '\0';

        if (plain) free(plain);
        if (encrypted) free(encrypted);

        

        Serial.print("tx_DataCache:777777 ");
        Serial.println(tx_DataCache);
        
    } else if ( findSubstring(data_decoded, "0x1102" )  ) {
        
      //  0x1102dFhDXzAwMDAxXzAwMDAxXzAwMDAxXzAwMDAxX3RlbmFudGFjY291bnRfdFhDZFhDXzIzOGI1Y19mNjk1NWNfZGY4YThhX2FjMzBhNmExZDgxX2hhcmR3YXJldHdpbl9kWENzSV9iTEVTU0VRX05hTl9iTEVTU0VRdFNfMjAyNC0wMS0xOVQwNToyODoxOS4xMDNaX3RTX3NJaFdBY3Rpb25fdW5sb2NrX2hXQWN0aW9u|413565c688bb4336c0e54d478daedd39f0aa7e321df8abafbbbed545a3e1bde
  Serial.println("0x1102>444    matched 444>>>   data: ");
  Serial.println( data_raw );

      // extracting masked data
  char* masked_data = extract_substring( 6 , data_raw );
      Serial.println("masked_data: ");
      Serial.println( masked_data );

      char* unmasked_data = new char[ TRANSFER_ARRAY_SIZE ](); 
      base64_char_decoding( masked_data,  unmasked_data );
      Serial.println("unmasked_data: ");
      Serial.println( unmasked_data );

      // Hardware XigCode validation
      const char* incomingTXC = find_values_between_substringsV5( unmasked_data, "tenantXC:" , "::" );
      // Serial.println("incomingTXC   >>_+_+_> ");
      // Serial.println(incomingTXC);

      if ( strcmp( incomingTXC, e2prom_variables.tenant_xc ) != 0 ){  
        Serial.print("  >>>  tenant mis-match  >>>  ");
        return;
      }

      // Device XigCode validation
      const char* incoming_DXC = find_values_between_substringsV5( unmasked_data, "deviceXC:" , "::" );
      // Serial.println("incoming_DXC   >>_+_+_> ");
      // Serial.println(incoming_DXC);

      if ( strcmp( incoming_DXC, e2prom_variables.device_xc ) != 0 ){  
        Serial.print("  >>>  tenant mis-match  >>>  ");
        return;
      }
      strcpy( software_parameters_variables.incoming_data_time_stamp , find_values_between_substringsV5( unmasked_data, "timeStamp:" , "::" ) );
      // Serial.println("software_parameters_variables.incoming_data_time_stamp: ");
      // Serial.println( software_parameters_variables.incoming_data_time_stamp );

      const char* incoming_action_instruction = find_values_between_substringsV5( unmasked_data, "hWAction:" , "::" );
      Serial.println("incoming_action_instruction: ");
      Serial.println( incoming_action_instruction );
      write_shackle_lock_status( incoming_action_instruction );

    // } else if ( ( 
    //               strlen( e2prom_variables.hardware_uuid ) == 0 || 
    //               strlen( e2prom_variables.board_model ) == 0 
    //             ) && 
    //               strcmp(data_decoded, "tI_ConditionalWipeAllLicensesAndReissueHWUUID_tI" ) == 0 
    //             ) {
    //   // Reset all settings if device does not have basics
    //   wipeAllAndReissueAllBasics();
    //   return;
      

    // } else if (  strcmp(data_decoded, "tI_WipeAllLicensesAndReissueHWUUID_tI" ) == 0 ) {
    //   // Reset all settings in any condition
    //   wipeAllAndReissueAllBasics();
    //   return;
      

    } else {
      Serial.println("ELSE matched !   >>> ");
    }

    // const char* broadcastOutputAValString = find_values_between_substringsV4( data_decoded, broadcast_global_variables.broadcastOutputA_SubStringStart , broadcast_global_variables.broadcastOutputA_SubStringEnd );
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
    

  if (data_raw) { delete[] data_raw; data_raw = nullptr; }
  if (meta) { delete[] meta; meta = nullptr; }
  if (hash) { delete[] hash; hash = nullptr; }
  if (data_decoded) { delete[] data_decoded; data_decoded = nullptr; }
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
        Serial.println("Start - Senting Data...");
        sendingChunkData( starter_block );


        // // Creating hash of data - if device is configred used global hash key, if device is configured use device specific hash key
        // // const int deviceXigCodeLengthCheck = strlen( e2prom_variables.device_xc );
        // // const int tenantXigCodeLengthCheck = strlen( e2prom_variables.tenant_xc );
        // char hash256ResultArray[ 65 ];
        // if ( strlen( e2prom_variables.device_xc ) > 10 && strlen( e2prom_variables.tenant_xc ) > 10 ){
        //   hashSHA256( tx_InFlightData, e2prom_variables.hashKey_Internal, hash256ResultArray );
        // } else {
        //   hashSHA256( tx_InFlightData, software_parameters_fixed.GLOBAL_SHARED_HASH_KEY, hash256ResultArray );
        // }

        // // Adding has to the end of sending string
        // strcat(tx_InFlightData, "|");  // Add double quotes
        // strcat(tx_InFlightData, hash256ResultArray );  // Add the String variable

        int tx_InFlightDataLength =  strlen( tx_InFlightData );
        // Data packets
        Serial.println("tx_InFlightData :::  ");
        Serial.println( tx_InFlightData );
        Serial.println("tx_InFlightDataLength :::  ");
        Serial.println( tx_InFlightDataLength );



        Serial.println("Mid - Sending Data...");
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
        Serial.println("Last - Senting Data...");
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

