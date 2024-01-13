// Original source - Example of Arduino IDE AES128_Example
#include "string.h"
#include "Crypto.h"
#include "AES.h"
#include "mbedtls/md.h"

#ifndef HASH_SHA_256_HPP
#define HASH_SHA_256_HPP

// Source: 
// https://techtutorialsx.com/2018/01/25/esp32-arduino-applying-the-hmac-sha-256-mechanism/

void hashSHA256( char *payload, const char* key, char* dataHash ) {

  byte hmacResult[32];
 
  mbedtls_md_context_t ctx;
  mbedtls_md_type_t md_type = MBEDTLS_MD_SHA256;
 
  // const size_t payloadLength = strlen(payload);
  const size_t payloadLength = strlen(payload);
  const size_t keyLength = strlen(key);            
 
  mbedtls_md_init(&ctx);
  mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(md_type), 1);
  mbedtls_md_hmac_starts(&ctx, (const unsigned char *) key, keyLength);
  mbedtls_md_hmac_update(&ctx, (const unsigned char *) payload, payloadLength);
  mbedtls_md_hmac_finish(&ctx, hmacResult);
  mbedtls_md_free(&ctx);
 
  // char dataHash[sizeof(hmacResult) * 2 + 1];  // Allocate space for digits and null terminator

  int resultIndex = 0;

  for (int i = 0; i < sizeof(hmacResult); i++) {
      char str[3];
      sprintf(str, "%02x", (int)hmacResult[i]);

      // Append str to the dataHash
      strncpy(dataHash + resultIndex, str, 2);  // Copy 2 characters from str
      resultIndex += 2;  // Move the index for the next append
  }

  // Add null terminator to mark the end of the string
  dataHash[resultIndex] = '\0';
}

#endif

// ////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////// Source example
// // https://techtutorialsx.com/2018/01/25/esp32-arduino-applying-the-hmac-sha-256-mechanism/
// #include "mbedtls/md.h"
 
// void setup(){
 
//   Serial.begin(115200);
 
//   char *key = "secretKey";
//   char *payload = "Hello HMAC SHA 256!";
//   byte hmacResult[32];
 
//   mbedtls_md_context_t ctx;
//   mbedtls_md_type_t md_type = MBEDTLS_MD_SHA256;
 
//   const size_t payloadLength = strlen(payload);
//   const size_t keyLength = strlen(key);            
 
//   mbedtls_md_init(&ctx);
//   mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(md_type), 1);
//   mbedtls_md_hmac_starts(&ctx, (const unsigned char *) key, keyLength);
//   mbedtls_md_hmac_update(&ctx, (const unsigned char *) payload, payloadLength);
//   mbedtls_md_hmac_finish(&ctx, hmacResult);
//   mbedtls_md_free(&ctx);
 
//   Serial.print("Hash: ");
 
//   for(int i= 0; i< sizeof(hmacResult); i++){
//       char str[3];
 
//       sprintf(str, "%02x", (int)hmacResult[i]);
//       Serial.print(str);
//   }
// }
 
// void loop(){}

// ////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////// Covering Hash output to Char

// char resultArray[sizeof(hmacResult) * 2 + 1];  // Allocate space for digits and null terminator

// //
// int resultIndex = 0;
// //
// for (int i = 0; i < sizeof(hmacResult); i++) {
//     char str[3];
//     sprintf(str, "%02x", (int)hmacResult[i]);

//     // Append str to the resultArray
//     strncpy(resultArray + resultIndex, str, 2);  // Copy 2 characters from str
//     resultIndex += 2;  // Move the index for the next append
// }

// // Add null terminator to mark the end of the string
// resultArray[resultIndex] = '\0';

