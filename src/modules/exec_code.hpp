#ifndef EXEC_CODE_HPP
#define EXEC_CODE_HPP

#include "Arduino.h"
#include <string>
#include "base64.h"
#include "modules/data_string_builder.hpp"
#include "modules/system_structs.hpp"
#include "modules/crypto_utils.h"
#include "modules/esp32_time_utils.hpp"

// Use macro for buffer size
#ifndef TRANSFER_ARRAY_SIZE
#define TRANSFER_ARRAY_SIZE 4096
#endif

extern char* sendStr56;
extern char* tempCache;


    // 0x - "payload|d-hash|g-hash|metaData"
    // 0xV00 - "metaData||payload||g-hash||d-hash"
    //          g-hash = ghash(metaData||payload)
    //          d-hash = dhash(metaData||payload||g-hash)

    // 0x-0	: global hash and enrypton keys used
    // 0x-1	: device hash and enrypton keys used

inline char* exec_code_v002_0x0001() {

    if (sendStr56) { delete[] sendStr56; sendStr56 = nullptr; }
    sendStr56 = new char[TRANSFER_ARRAY_SIZE]();
    sendStr56[0] = '\0';
    if (tempCache) { delete[] tempCache; tempCache = nullptr; }
    tempCache = new char[TRANSFER_ARRAY_SIZE]();
    tempCache[0] = '\0';

    
    // Meta data
    std::string meta_data_text = std::string("") ;
    meta_data_text += "hwConfigState:unregisteredDevice::";

    meta_data_text += "v:2::";
    meta_data_text += "code:v002_0x0001::";
    meta_data_text += "origin:hw::";
    meta_data_text += "gEncryption:g1RSA::";
    meta_data_text += "gHash:g1SHA256::";
    meta_data_text += "changeTracker:";
    meta_data_text += e2prom_variables.major_action_counter_tracker;
    meta_data_text += "::";
    meta_data_text += "timeStamp:";

    char timebuf[32] = {0};
    get_esp32_time_string(timebuf, sizeof(timebuf));
    meta_data_text += timebuf;
    meta_data_text += "::";

     
    // Meta data

    //// Clear text
    std::string clear_text = std::string("") ;
    clear_text += "hwConfigState:unregisteredDevice::";
    clear_text += device_tenant_xigcode();
    clear_text += device_shackle_state();
    clear_text += device_firmware_information();
    clear_text += device_bluetooth_session_sequence();
    //// Clear text

    //// Encrypted text
    std::string encrypted_text = device_secret_config_information();

    // Encrypt the concatenated encrypted_text using encrypt_with_public_key
    char encrypted_buf[1024] = {0};
    int enc_result = encrypt_with_public_key(encrypted_text.c_str(), encrypted_buf, sizeof(encrypted_buf));

    std::string encrypted_data = (enc_result == 0) ? std::string(encrypted_buf) : std::string("");
    //// Encrypted text

    strncpy(sendStr56, clear_text.c_str(), TRANSFER_ARRAY_SIZE - 1);
    sendStr56[TRANSFER_ARRAY_SIZE - 1] = '\0';

    std::string tempCacheStr = clear_text + "encryptData:" + encrypted_data + "::";
    strncpy(tempCache, tempCacheStr.c_str(), TRANSFER_ARRAY_SIZE - 1);

    String encoded = base64::encode(tempCache);
    strncpy(tempCache, encoded.c_str(), TRANSFER_ARRAY_SIZE - 1);

    // tempCache = metadata || Payload 
    std::string tempCacheWithMeta = meta_data_text + "||" + tempCache;
    strncpy(tempCache, tempCacheWithMeta.c_str(), TRANSFER_ARRAY_SIZE - 1);
    tempCache[TRANSFER_ARRAY_SIZE - 1] = '\0';

    
    // Data Global hash 
    // Creating hash of data - if device is configred used global hash key, if device is configured use device specific hash key
    char hash256ResultArray[ 65 ];
    hashSHA256( tempCache, software_parameters_fixed.GLOBAL_SHARED_HASH_KEY, hash256ResultArray );
    strcat(tempCache, "||");
    strcat(tempCache, hash256ResultArray );  // Add the String variable

    // Data Device hash - Place holder
    strcat(tempCache, "||||");



    tempCache[TRANSFER_ARRAY_SIZE - 1] = '\0';

    // Return a new buffer with the result
    char* result = new char[TRANSFER_ARRAY_SIZE]();
    strncpy(result, tempCache, TRANSFER_ARRAY_SIZE - 1);
    result[TRANSFER_ARRAY_SIZE - 1] = '\0';
    return result;
}


inline char* exec_code_v002_0x0102() {
    delete[] sendStr56;
    sendStr56 = new char[TRANSFER_ARRAY_SIZE]();

    delete[] tempCache;
    tempCache = new char[TRANSFER_ARRAY_SIZE]();

    std::string info = std::string("") +
          "ver:" + "2" + "::" +
          "code:" + "v002_0x_+_+_+_+_+_+_0102" + "::" +
          "hash:" + "d1SHA256" + "::" +
          "hwConfigState:" + "registeredDevice" "::" ;

    strcat(sendStr56, info.c_str());

    Serial.print("sendStr56:111111 ");
    Serial.println(sendStr56);

    std::string combined = device_shackle_state() + sendStr56;
    strcpy(sendStr56, combined.c_str());

    Serial.print("sendStr56:22766666222 ");
    Serial.println(sendStr56);

    std::string combined2 = device_tenant_xigcode() + sendStr56;
    strcpy(sendStr56, combined2.c_str());

    std::string combined3 = device_firmware_information() + sendStr56;
    strcpy(sendStr56, combined3.c_str());

    std::string combined4 = device_bluetooth_session_sequence() + sendStr56;
    strcpy(sendStr56, combined4.c_str());

    Serial.print("sendStr56:333zzz333 ");
    Serial.println(sendStr56);

    std::string fullResponse = std::string(sendStr56);

    Serial.print("sendStr56:444444 ");
    Serial.println(sendStr56);

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
      } else {
        Serial.print("Encryption failed! Error code: ");
        Serial.println(enc_result);
        Serial.print("Encrypted buffer (may be garbage): ");
        Serial.println(encrypted);
      }
    }

    Serial.print("sendStr56:555555 ");
    Serial.println(sendStr56);

    fullResponse += "publicKeyEnc:";
    if (encrypted) fullResponse += encrypted;
    fullResponse += "::";

    if (plain) free(plain);
    if (encrypted) free(encrypted);

    Serial.print("tx_DataCache:777777 ");
    Serial.println(fullResponse.c_str());

    char* result = new char[TRANSFER_ARRAY_SIZE]();
    strncpy(result, fullResponse.c_str(), TRANSFER_ARRAY_SIZE - 1);
    result[TRANSFER_ARRAY_SIZE - 1] = '\0';
    return result;
}


#endif