#ifndef EXEC_CODE_HPP
#define EXEC_CODE_HPP

#include <string>
#include "base64.h"
#include "modules/data_string_builder.hpp"
#include "modules/system_structs.hpp"

// Use macro for buffer size
#ifndef TRANSFER_ARRAY_SIZE
#define TRANSFER_ARRAY_SIZE 4096
#endif

extern char* sendStr56;
extern char* tempCache;

inline char* exec_code_0x0001() {
    if (sendStr56) { delete[] sendStr56; sendStr56 = nullptr; }
    sendStr56 = new char[TRANSFER_ARRAY_SIZE]();
    sendStr56[0] = '\0';
    if (tempCache) { delete[] tempCache; tempCache = nullptr; }
    tempCache = new char[TRANSFER_ARRAY_SIZE]();
    tempCache[0] = '\0';

    std::string info = std::string("") +
        "ver:2::" +
        "code:0x0001::" +
        "hwConfigState:unregisteredDevice::" +
        "md5Hashing:none::" +
        "encryption:none::";
    strcat(sendStr56, info.c_str());

    std::string response = device_shackle_state() + sendStr56;
    strcpy(sendStr56, response.c_str());
    response = device_secret_config_information() + sendStr56;
    strcpy(sendStr56, response.c_str());
    response = device_tenant_xigcode() + sendStr56;
    strcpy(sendStr56, response.c_str());
    response = device_firmware_information() + sendStr56;
    strcpy(sendStr56, response.c_str());
    response = device_bluetooth_session_sequence() + sendStr56;
    strcpy(sendStr56, response.c_str());

    String encoded = base64::encode(sendStr56);
    strcat(tempCache, "0x0001");
    strcat(tempCache, encoded.c_str());

    // Return a new buffer with the result
    char* result = new char[TRANSFER_ARRAY_SIZE]();
    strncpy(result, tempCache, TRANSFER_ARRAY_SIZE - 1);
    result[TRANSFER_ARRAY_SIZE - 1] = '\0';
    return result;
}


inline char* exec_code_0x0102() {
    if (sendStr56) { delete[] sendStr56; sendStr56 = nullptr; }
    sendStr56 = new char[TRANSFER_ARRAY_SIZE]();
    sendStr56[0] = '\0';
    if (tempCache) { delete[] tempCache; tempCache = nullptr; }
    tempCache = new char[TRANSFER_ARRAY_SIZE]();
    tempCache[0] = '\0';

    std::string info = std::string("") +
        "ver:2::" +
        "code:0x0102::" +
        "traffOrigin:hwDevice::" +
        "devHashing:hwDevice01::" +
        "devEncryption:none::" +
        "hwConfigState:registeredDevice::";
    strcat(sendStr56, info.c_str());

    std::string response = device_shackle_state() + sendStr56;
    strcpy(sendStr56, response.c_str());
    response = device_secret_config_information() + sendStr56;
    strcpy(sendStr56, response.c_str());
    response = device_tenant_xigcode() + sendStr56;
    strcpy(sendStr56, response.c_str());
    response = device_firmware_information() + sendStr56;
    strcpy(sendStr56, response.c_str());
    response = device_bluetooth_session_sequence() + sendStr56;
    strcpy(sendStr56, response.c_str());

    // RSA Encryption block
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
    std::string fullResponse = std::string(sendStr56);
    fullResponse += "publicKeyEnc:";
    if (encrypted) fullResponse += encrypted;
    fullResponse += "::";

    // Return a new buffer with the result
    char* result = new char[TRANSFER_ARRAY_SIZE]();
    strncpy(result, fullResponse.c_str(), TRANSFER_ARRAY_SIZE - 1);
    result[TRANSFER_ARRAY_SIZE - 1] = '\0';

    if (plain) free(plain);
    if (encrypted) free(encrypted);
    return result;
}

#endif