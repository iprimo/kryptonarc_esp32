#ifndef EXEC_CODE_HPP
#define EXEC_CODE_HPP

#include "Arduino.h"
#include <string>
#include "base64.h"
#include "modules/data_string_builder.hpp"
#include "modules/system_structs.hpp"
#include "modules/crypto_utils.h"

// Use macro for buffer size
#ifndef TRANSFER_ARRAY_SIZE
#define TRANSFER_ARRAY_SIZE 4096
#endif

extern char* sendStr56;
extern char* tempCache;

inline char* exec_code_0x0001() {

    // "payload|hash|metaData"

    if (sendStr56) { delete[] sendStr56; sendStr56 = nullptr; }
    sendStr56 = new char[TRANSFER_ARRAY_SIZE]();
    sendStr56[0] = '\0';
    if (tempCache) { delete[] tempCache; tempCache = nullptr; }
    tempCache = new char[TRANSFER_ARRAY_SIZE]();
    tempCache[0] = '\0';
    
    //// Clear text
    std::string clear_text = std::string("") ;
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

     // Creating hash of data - if device is configred used global hash key, if device is configured use device specific hash key
    char hash256ResultArray[ 65 ];
    hashSHA256( tempCache, software_parameters_fixed.GLOBAL_SHARED_HASH_KEY, hash256ResultArray );

    // Data hash 
    // Adding has to the end of sending string
    strcat(tempCache, "|");
    strcat(tempCache, hash256ResultArray );  // Add the String variable
    strcat(tempCache, "|");  // Add double quotes
    // Data hash 


    // Meta data
    strcat(tempCache, "v:2::");
    strcat(tempCache, "code:0x0001::");
    strcat(tempCache, "hwConfigState:unregisteredDevice::");
    strcat(tempCache, "encryption:g1::");
    strcat(tempCache, "hash:g1::");
    // Meta data

    Serial.print(" tempCache >>> ");
    Serial.println(tempCache);


    tempCache[TRANSFER_ARRAY_SIZE - 1] = '\0';

    // Return a new buffer with the result
    char* result = new char[TRANSFER_ARRAY_SIZE]();
    strncpy(result, tempCache, TRANSFER_ARRAY_SIZE - 1);
    result[TRANSFER_ARRAY_SIZE - 1] = '\0';
    return result;
}


#endif